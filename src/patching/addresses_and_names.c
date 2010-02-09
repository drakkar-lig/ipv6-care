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
Etienne DUBLE 	-3.0:	Added test_if_fd_is_a_network_socket(initial_socket)

*/
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "common_original_functions.h"
#include "socket_info.h"
#include "family.h"
#include "utils.h"
#define MAX_HOST_SIZE	128
#define MAX_SERV_SIZE	128

int get_equivalent_address(struct polymorphic_sockaddr *data, struct polymorphic_sockaddr *new_data)
{
	int result;
	char host[MAX_HOST_SIZE], service[MAX_SERV_SIZE];
	struct addrinfo hints, *address_list, *first_address;

	// get the hostname
	result = original_getnameinfo(&data->sockaddr.sa, data->sa_len, host, MAX_HOST_SIZE, service, MAX_SERV_SIZE, NI_NUMERICSERV);
	if (result == 0)
	{
		// get its IP of the other family
		if (strcmp(host, "::") == 0)
		{
			strcpy(host, "0.0.0.0");
		}
		else
		{
			if (strcmp(host, "0.0.0.0") == 0)
			{
				strcpy(host, "::");
			}
		}
		
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = OTHER_FAMILY(data->sockaddr.sa.sa_family);
		hints.ai_socktype = SOCK_STREAM; // could also be SOCK_DGRAM, but needs to be initialized
		result = original_getaddrinfo(host, service, &hints, &address_list);
		if (result == 0)
		{
			first_address = address_list;
			// copy data to pointer arguments
			memcpy(&new_data->sockaddr.sa, first_address->ai_addr, first_address->ai_addrlen);
			new_data->sa_len = first_address->ai_addrlen;
			// free the memory
			original_freeaddrinfo(address_list);
		}
	}
	return result;
}

int get_address_in_given_family(char *name, int family, struct polymorphic_sockaddr *psa)
{
	int result, getaddrinfo_result;
	struct addrinfo hints, *address_list, *paddress;

	// getaddrinfo parameters
	memset(&hints, 0, sizeof(hints));       // init
	hints.ai_family = family;
	hints.ai_socktype = SOCK_STREAM; // could also be SOCK_DGRAM, but needs to be initialized

	getaddrinfo_result = original_getaddrinfo(name, NULL, &hints, &address_list);
	paddress = address_list;
	if (getaddrinfo_result == 0)
	{
		copy_sockaddr_to_psa(paddress->ai_addr, paddress->ai_addrlen, psa);

		// free the list
		original_freeaddrinfo(address_list);

		result = 0;
	}
	else
	{
		result = -1;
	}

	return result;
}

