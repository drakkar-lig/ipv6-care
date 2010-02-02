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
June 29, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation
Etienne DUBLE 	-3.0:	Bug connect() -> original_connect()

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#include "fd_tools.h"
#include "common_networking_tools.h"
#include "address_name_matches.h"
#include "common_original_functions.h"
#include "ipv6_to_ipv4_mappings.h"
#include "connection_handling.h"
#include "family.h"
#include "utils.h"
#include "addresses_and_names.h"

extern int h_errno;

// Start of the network-related functions overriden
// ------------------------------------------------

int accept(int socket, struct sockaddr *address,
              socklen_t *address_len)
{
	int new_socket_created, resulting_socket;

	resulting_socket = socket; // default

	if (test_if_fd_is_a_network_socket(socket) == 1)
	{
		new_socket_created = get_additional_listening_socket_if_needed(socket);

		if (new_socket_created != -1)
		{
			// wait on the two file descriptors
			resulting_socket = wait_on_two_sockets(socket, new_socket_created);
		}
	}

	return original_accept(resulting_socket, address, address_len);
}

int bind(int socket, const struct sockaddr *address,
              socklen_t address_len)
{
	int result;
	// TODO record_address(address);

	result = original_bind(socket, address, address_len);
	return result;
}

int close(int fd)
{
	int result;
	close_sockets_related_to_fd(fd);

	result = original_close(fd);
	return result;
}

int connect(int s, const struct sockaddr *address,
              socklen_t address_len)
{
	int result;
	struct polymorphic_sockaddr original_psa, other_psa;
	struct ipv4_mapping_data *mapping_data;

	copy_sockaddr_to_psa((struct sockaddr *)address, address_len, &original_psa);

	mapping_data = get_mapping_data_if_host_is_ipv6_only(&original_psa);

	if (mapping_data != NULL)
	{
		printf("found mapping.\n");
		// this is the case when a host had only an IPv6 address and, during the name resolution
		// phase, a mapping was set up. We will now try to connect to the original IPv6 address.
		result = try_connect_using_ipv6_addr_of_mapping(s, &original_psa, mapping_data);
	}
	else
	{
		// try to connect to the host specified
		result = try_connect_and_register_connection(s, &original_psa);

		if (		(result == -1)	&&
				IS_AF_INET_OR_INET6(address->sa_family) &&
				(get_equivalent_address(&original_psa, &other_psa) == 0))
		{	// try to connect to the host specified using an address of the other family
			result = try_connect_using_address_of_other_family(s, &other_psa);
		}
	}

	return result;
}

int getaddrinfo(const char *nodename,
		const char *servname,
		const struct addrinfo *hints,
		struct addrinfo **res)
{
	int result;
//	struct addrinfo *paddress;

	result = original_getaddrinfo(nodename, servname, hints, res);
/*	
	if (result == 0)
	{
		for(paddress = *res; paddress != NULL; paddress = paddress->ai_next)
		{
			record_sa_address_name_match(paddress->ai_addr, (char *)nodename);
		}
	}
*/	return result;
}

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type)
{
	struct hostent *result;

	result = original_gethostbyaddr(addr, len, type);
//	record_hostent(result);
	return result;
}

struct hostent *gethostbyname(const char *name)
{
	static struct hostent result;
	static int buflen = 0;
	static char *buf = NULL;
	int done = 0;
	struct hostent *function_result;
	int error, gethostbyname_r_result;

	while(done == 0)
	{
		buflen += 10;
		buflen *= 2;
		buf = realloc(buf, buflen);
		// call the modified gethostbyname_r function below
		gethostbyname_r_result = gethostbyname_r(name, &result, buf, buflen, &function_result, &error);
		if (gethostbyname_r_result == 0)
		{
			done = 1;
		}
		else
		{
			if (gethostbyname_r_result != ERANGE)
			{
				function_result = NULL;
				done = 1;
				h_errno = gethostbyname_r_result;
			}
		}
	}

//	record_hostent(result);
	return function_result;
}

int gethostbyname_r(const char *name,
		struct hostent *ret, char *buf, size_t buflen,
		struct hostent **result, int *h_errnop)
{
	int function_result, address_conversion_result;
	struct ipv4_mapping_data *mapping_data;
	struct polymorphic_sockaddr psa;
	struct polymorphic_addr pa;

	function_result = original_gethostbyname_r(name, ret, buf, buflen, result, h_errnop);
	if (function_result != 0)
	{
		if (	(h_errnop != NULL)&& 
			((*h_errnop == HOST_NOT_FOUND)||(*h_errnop == NO_ADDRESS)||(*h_errnop == NO_DATA)))
		{	// no IPv4 address was found, let's see if there is an IPv6 address

			if (get_address_in_given_family((char *)name, AF_INET6, &psa) == 0)
			{
				// create a mapping with this IPv6 addr
				mapping_data = get_ipv4_mapping_for_real_ipv6_addr(&psa.sockaddr.sa_in6.sin6_addr);

				// format it as a hostent
				copy_ipv4_addr_to_pa(&mapping_data->mapped_ipv4_addr, &pa);
				address_conversion_result = convert_pa_and_name_to_hostent(&pa, (char *)name, buf, buflen, ret, h_errnop);

				if (address_conversion_result == -1)
				{
					function_result = *h_errnop;
				}
				else
				{
					*result = ret;
					function_result = 0;
				}
			}
		}
	}
//	record_hostent(*result);
	return function_result;
}

int getnameinfo(const struct sockaddr *sa, socklen_t salen,
              char *node, socklen_t nodelen, char *service,
              socklen_t servicelen, unsigned int flags)
{
	int result;

	result = original_getnameinfo(sa, salen, node, nodelen, service, servicelen, flags);

/*	if ((node != NULL) && (nodelen != 0))
	{
		record_sa_address_name_match((struct sockaddr *)sa, node);
	}
*/	return result;
}

int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	return original_getpeername(sockfd, addr, addrlen);
}

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	return original_getsockname(sockfd, addr, addrlen);
}

in_addr_t inet_addr(const char *cp) 
{
	// TO DO:
	// Check getnameinfo NI_NUMERIC_HOST, if it is IPv6 then record a mapping 
	return original_inet_addr(cp);
}

int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
	struct pollfd *final_fds;
	int final_nfds, result;

	// indicate to manage_socket_accesses_on_pollfd_table that no allocation has been done yet
	final_fds = NULL;

	manage_socket_accesses_on_pollfd_table(nfds, &final_nfds, fds, &final_fds);

	result = original_poll(final_fds, final_nfds, timeout);

	remap_changes_to_initial_pollfd_table(nfds, final_nfds, fds, final_fds);

	// free memory
	final_fds = realloc(final_fds, 0);

	return result;
}

int ppoll(struct pollfd *fds, nfds_t nfds,
               const struct timespec *timeout, const sigset_t *sigmask)
{
	struct pollfd *final_fds;
	int final_nfds, result;

	// indicate to manage_socket_accesses_on_pollfd_table that no allocation has been done yet
	final_fds = NULL;

	manage_socket_accesses_on_pollfd_table(nfds, &final_nfds, fds, &final_fds);

	result = original_ppoll(final_fds, final_nfds, timeout, sigmask);

	remap_changes_to_initial_pollfd_table(nfds, final_nfds, fds, final_fds);

	// free memory
	final_fds = realloc(final_fds, 0);

	return result;
}

int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      const struct timespec *timeout, const sigset_t *sigmask)
{
	int result;
	fd_set final_readfds, final_writefds, final_errorfds;
	int modifiable_nfds;

	modifiable_nfds = nfds;

	manage_socket_accesses_on_fdset(&modifiable_nfds, readfds, &final_readfds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, writefds, &final_writefds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, errorfds, &final_errorfds);

	result = original_pselect(modifiable_nfds, &final_readfds, &final_writefds, &final_errorfds, timeout, sigmask);

	remap_changes_to_initial_fdset(modifiable_nfds, readfds, &final_readfds);
	remap_changes_to_initial_fdset(modifiable_nfds, writefds, &final_writefds);
	remap_changes_to_initial_fdset(modifiable_nfds, errorfds, &final_errorfds);
	return result;
}

ssize_t read(int fd, void *buf, size_t count)
{
	ssize_t result;
	int final_fd;

	final_fd = manage_socket_access_on_fd(eAccessType_Read, fd);

	result = original_read(final_fd, buf, count);
	return result;
}

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      struct timeval *timeout)
{
	int result;
	fd_set final_readfds, final_writefds, final_errorfds;
	int modifiable_nfds;
	
	modifiable_nfds = nfds;

	manage_socket_accesses_on_fdset(&modifiable_nfds, readfds, &final_readfds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, writefds, &final_writefds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, errorfds, &final_errorfds);

	result = original_select(modifiable_nfds, &final_readfds, &final_writefds, &final_errorfds, timeout);

	remap_changes_to_initial_fdset(modifiable_nfds, readfds, &final_readfds);
	remap_changes_to_initial_fdset(modifiable_nfds, writefds, &final_writefds);
	remap_changes_to_initial_fdset(modifiable_nfds, errorfds, &final_errorfds);
	return result;
}

ssize_t write(int fd, const void *buf, size_t count)
{
	ssize_t result;
	int final_fd;

	final_fd = manage_socket_access_on_fd(eAccessType_Write, fd);

	result = original_write(final_fd, buf, count);
	return result;
}

