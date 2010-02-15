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

extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;

enum list_of_constant_pa
{
	any_addr_6,
	any_addr_4,
	loopback_6,
	loopback_4,
	number_of_constant_pa
};

// this function manage addresses of type loopback or any_addr
int get_equivalent_constant_address(struct polymorphic_sockaddr *data, struct polymorphic_sockaddr *new_data)
{
	static __thread struct polymorphic_addr constant_pa[number_of_constant_pa];
	static __thread int init_done = 0;
	struct in_addr ipv4_addr;
	struct polymorphic_addr pa, *corresponding_pa;
	int index, result;

	result = -1;

	if (init_done == 0)
	{
		copy_ipv6_addr_to_pa((struct in6_addr*)&in6addr_any, &constant_pa[any_addr_6]);
		copy_ipv6_addr_to_pa((struct in6_addr*)&in6addr_loopback, &constant_pa[loopback_6]);
		ipv4_addr.s_addr = INADDR_ANY;
		copy_ipv4_addr_to_pa(&ipv4_addr, &constant_pa[any_addr_4]);
		ipv4_addr.s_addr = INADDR_LOOPBACK;
		copy_ipv4_addr_to_pa(&ipv4_addr, &constant_pa[loopback_4]);
		init_done = 1;
	}

	copy_psa_to_pa(data, &pa);

	corresponding_pa = NULL;

	for (index = 0; index < number_of_constant_pa; index++)
	{
		if (compare_pa(&constant_pa[index], &pa) == 0)
		{
			if (index%2 == 0)
			{
				corresponding_pa = &constant_pa[index+1];
			}
			else
			{
				corresponding_pa = &constant_pa[index-1];
			}
			break;
		}
	}

	if (corresponding_pa != NULL)
	{
		copy_pa_and_port_to_psa(corresponding_pa, get_port_from_psa(data), new_data);
		result = 0;
	}

	return result;
}

int get_equivalent_address(struct polymorphic_sockaddr *data, struct polymorphic_sockaddr *new_data)
{
	int result;
	char host[MAX_HOST_SIZE];
	struct addrinfo hints, *address_list, *first_address;

	result = 0;
	
	// if get_equivalent_constant_address return 0 then we are done and 
	// we do not need any name resolution
	if (get_equivalent_constant_address(data, new_data) != 0)
	{
		// get the hostname
		result = original_getnameinfo(&data->sockaddr.sa, data->sa_len, host, MAX_HOST_SIZE, NULL, 0, NI_NUMERICSERV);
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
			result = original_getaddrinfo(host, NULL, &hints, &address_list);
			if (result == 0)
			{
				first_address = address_list;
				// copy address and port to new_data
				copy_sockaddr_to_psa(first_address->ai_addr, first_address->ai_addrlen, new_data);
				set_port_in_psa(new_data, get_port_from_psa(data));
				// free the memory
				original_freeaddrinfo(address_list);
			}
		}
	}
	return result;
}

int get_address_in_given_family(char *name, int family, struct polymorphic_addr *pa)
{
	int result, getaddrinfo_result;
	struct addrinfo hints, *address_list, *paddress;
	struct polymorphic_sockaddr psa;

	// getaddrinfo parameters
	memset(&hints, 0, sizeof(hints));       // init
	hints.ai_family = family;
	hints.ai_socktype = SOCK_STREAM; // could also be SOCK_DGRAM, but needs to be initialized

	getaddrinfo_result = original_getaddrinfo(name, NULL, &hints, &address_list);
	paddress = address_list;
	if (getaddrinfo_result == 0)
	{
		copy_sockaddr_to_psa(paddress->ai_addr, paddress->ai_addrlen, &psa);
		copy_psa_to_pa(&psa, pa);

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

