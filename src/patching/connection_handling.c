/*
Copyright (c) Members of the EGEE Collaboration. 2008. 
See http://www.eu-egee.org/partners/ for details on the copyright
holders.  

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at 

    http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
See the License for the specific language governing permissions and 
limitations under the License.

---------------------------------------------------------------------
Developed by Etienne DUBLE - CNRS UREC (http://www.urec.fr)
etienne __dot__ duble __at__ urec __dot__ cnrs __dot__ fr
Nov 25, 2008.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/

#include <string.h>
#include <errno.h>


#include "family.h"
#include "socket_info.h"
#include "common_original_functions.h"
#include "fd_tools.h"
#include "ipv6_to_ipv4_mappings.h"
#include "socket_info.h"
#include "created_sockets.h"

int reopen_socket_with_other_family(int s, int family)
{
	int type, protocol, result;

	result = 0;

	// record the type, protocol and fd of the existing socket
	type = get_socket_type(s);
	protocol = get_socket_protocol(s);
	
	// close the socket - this way the fd integer should be available for our new socket
	// and the calling program will not notice that the socket is not the same
	original_close(s);

	// create an IPv6 socket on the same file descriptor s

	if (create_socket_on_specified_free_fd(s, family, type, protocol) == -1)
	{	// failed ! recreate socket previously closed
		create_socket_on_specified_free_fd(s, OTHER_FAMILY(family), type, protocol);
	}

	return -1;
}

struct ipv4_mapping_data *get_mapping_data_if_host_is_ipv6_only(struct polymorphic_sockaddr *psa)
{
	struct ipv4_mapping_data *mapping_data;

	mapping_data = NULL;
	
	if (psa->sockaddr.sa.sa_family == AF_INET)
	{
		mapping_data = get_ipv4_mapping_for_mapped_ipv4_addr(&psa->sockaddr.sa_in.sin_addr);
	}

	return mapping_data;
}

int try_connect_and_register_connection(int s, struct polymorphic_sockaddr *psa)
{
	int result;

	// try to connect
	result = original_connect(s, &psa->sockaddr.sa, psa->sa_len);
	if (result == 0)
	{
		register_socket_state(s, socket_state_communicating);
		register_remote_socket_address(s, psa);
	}

	return result;
}

int try_connect_using_ipv6_addr_of_mapping(int s, struct polymorphic_sockaddr *ipv4_psa, struct ipv4_mapping_data *mapping_data)
{
	int result;
	struct polymorphic_sockaddr ipv6_psa;

	result = -1;

	if (reopen_socket_with_other_family(s, AF_INET6) == 0)
	{	// fill a sockaddr structure with the ipv6 address
		memset(&ipv6_psa.sockaddr.sa_in6, 0, sizeof(ipv6_psa.sockaddr.sa_in6));
		ipv6_psa.sockaddr.sa_in6.sin6_family = AF_INET6;
		ipv6_psa.sockaddr.sa_in6.sin6_port = ipv4_psa->sockaddr.sa_in.sin_port;
		memcpy(&ipv6_psa.sockaddr.sa_in6.sin6_addr, &mapping_data->real_ipv6_addr, sizeof(ipv6_psa.sockaddr.sa_in6.sin6_addr));

		// and get its length
		ipv6_psa.sa_len = sizeof(ipv6_psa.sockaddr.sa_in6);
	
		// try to connect
		result = try_connect_and_register_connection(s, &ipv6_psa);
		if (result == 0)
		{
			register_created_socket(INITIAL_SOCKET_WAS_CLOSED, s);
		}
		else
		{	// reopen socket as initially
			reopen_socket_with_other_family(s, AF_INET);
		}
	}
	else
	{	// could not recreate the socket as AF_INET6
		errno = EHOSTUNREACH;
	}

	return result;
}

int try_connect_using_address_of_other_family(int s, struct polymorphic_sockaddr *psa)
{
	int result;
	int save_errno;

	save_errno = errno;
	result = -1;

	if (reopen_socket_with_other_family(s, psa->sockaddr.sa.sa_family) == 0)
	{	
		// try to connect
		result = try_connect_and_register_connection(s, psa);
		if (result == 0)
		{
			register_created_socket(INITIAL_SOCKET_WAS_CLOSED, s);
		}
		else
		{	// reopen socket as initially
			reopen_socket_with_other_family(s, OTHER_FAMILY(psa->sockaddr.sa.sa_family));
		}
	}

	if (result == -1)
	{
		errno = save_errno;
	}

	return result;
}

