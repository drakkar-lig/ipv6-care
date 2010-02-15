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
#include <netdb.h>
#include <errno.h>

#include "socket_info.h"

#define _MIN(a, b) ((a<b)?a:b)
#define _COMPARE(a, b) ((a<b)?1:((a==b)?0:-1))

void copy_sockaddr_to_psa(struct sockaddr *address, unsigned int address_len, struct polymorphic_sockaddr *psa)
{
	memcpy(&psa->sockaddr.sa, address, address_len);
	psa->sa_len = address_len;
}

void copy_psa_to_sockaddr(struct polymorphic_sockaddr *psa, struct sockaddr *address, unsigned int *address_len)
{
	memcpy(address, &psa->sockaddr.sa, _MIN(*address_len, psa->sa_len));
	*address_len = psa->sa_len;
}

int get_port_from_psa(struct polymorphic_sockaddr *psa)
{
	if (psa->sockaddr.sa.sa_family == AF_INET)
	{
		return psa->sockaddr.sa_in.sin_port;
	}
	else
	{
		return psa->sockaddr.sa_in6.sin6_port;
	}
}

void set_port_in_psa(struct polymorphic_sockaddr *psa, int port)
{
	if (psa->sockaddr.sa.sa_family == AF_INET)
	{
		psa->sockaddr.sa_in.sin_port = port;
	}
	else
	{
		psa->sockaddr.sa_in6.sin6_port = port;
	}
}

void copy_ipv4_addr_to_pa(struct in_addr *address, struct polymorphic_addr *pa)
{
	memcpy(&pa->addr.ipv4_addr, address, sizeof(pa->addr.ipv4_addr));
	pa->addr_len = sizeof(pa->addr.ipv4_addr);
	pa->family = AF_INET;
}

void copy_ipv6_addr_to_pa(struct in6_addr *address, struct polymorphic_addr *pa)
{
	memcpy(&pa->addr.ipv6_addr, address, sizeof(pa->addr.ipv6_addr));
	pa->addr_len = sizeof(pa->addr.ipv6_addr);
	pa->family = AF_INET6;
}

int compare_pa(struct polymorphic_addr *pa1, struct polymorphic_addr *pa2)
{
	if (pa1->family != pa2->family)
	{
		return _COMPARE(pa1->family, pa2->family);
	}
	else
	{
		if (pa1->family == AF_INET)
		{
			return _COMPARE(pa1->addr.ipv4_addr.s_addr, pa2->addr.ipv4_addr.s_addr);
		}
		else
		{
			return memcmp(pa1->addr.ipv6_addr.s6_addr, pa2->addr.ipv6_addr.s6_addr, sizeof(pa1->addr.ipv6_addr.s6_addr));
		}
	}
}

void copy_psa_to_pa(struct polymorphic_sockaddr *psa, struct polymorphic_addr *pa)
{
	if (psa->sockaddr.sa.sa_family == AF_INET)
	{
		copy_ipv4_addr_to_pa(&psa->sockaddr.sa_in.sin_addr, pa);
	}
	else
	{
		copy_ipv6_addr_to_pa(&psa->sockaddr.sa_in6.sin6_addr, pa);
	}
}

void copy_pa_and_port_to_psa(struct polymorphic_addr *pa, unsigned int port, struct polymorphic_sockaddr *psa)
{
	memset(psa, 0, sizeof(struct polymorphic_sockaddr));
	if (pa->family == AF_INET)
	{
		psa->sa_len = sizeof(psa->sockaddr.sa_in);
		psa->sockaddr.sa.sa_family = AF_INET;
		psa->sockaddr.sa_in.sin_port = port;
		memcpy(&psa->sockaddr.sa_in.sin_addr, &pa->addr.ipv4_addr, sizeof(psa->sockaddr.sa_in.sin_addr));
	}
	else // AF_INET6
	{
		psa->sa_len = sizeof(psa->sockaddr.sa_in6);
		psa->sockaddr.sa.sa_family = AF_INET6;
		psa->sockaddr.sa_in6.sin6_port = port;
		memcpy(&psa->sockaddr.sa_in6.sin6_addr, &pa->addr.ipv6_addr, sizeof(psa->sockaddr.sa_in6.sin6_addr));
	}
}

void copy_ipv4_addr_and_port_to_psa(struct in_addr *ipv4_addr, unsigned int port, struct polymorphic_sockaddr *psa)
{
	struct polymorphic_addr pa;
	copy_ipv4_addr_to_pa(ipv4_addr, &pa);
	copy_pa_and_port_to_psa(&pa, port, psa);
}

void copy_ipv6_addr_and_port_to_psa(struct in6_addr *ipv6_addr, unsigned int port, struct polymorphic_sockaddr *psa)
{
	struct polymorphic_addr pa;
	copy_ipv6_addr_to_pa(ipv6_addr, &pa);
	copy_pa_and_port_to_psa(&pa, port, psa);
}

#define GET_SIZE_NEEDED(type, name) 	((strlen(name) + 1) * sizeof(char) +		\
					2 * sizeof(char*) +				\
					sizeof(type) +					\
					2 * sizeof(type *))

#define FORMAT_LIST_OF_ADDRESSES(type, p_working_data, address, ret)			\
					{ 						\
						type *p1, **p2;				\
						p1 = (type *)p_working_data;		\
						memcpy(p1, address, sizeof(type));	\
						p_working_data += sizeof(type); 	\
						p2 = (type **)p_working_data;		\
						p2[0] = p1;				\
						p2[1] = NULL;				\
						ret->h_addr_list = (char **)p2;		\
					}
				

int convert_pa_and_name_to_hostent(struct polymorphic_addr *pa, char *name, char *buf, size_t buflen, struct hostent *ret)
{
	unsigned int size_needed;
	int result, family;
	char *p_working_data, **p_working_data_char_pp;

	result = 0;

	family = pa->family;
	if (family == AF_INET6)
	{
		size_needed = GET_SIZE_NEEDED(struct in6_addr, name);
	}
	else
	{
		size_needed = GET_SIZE_NEEDED(struct in_addr, name);
	}

	if (buflen < size_needed)
	{
		result = ERANGE;
	}
	else
	{
		p_working_data = buf;
		// official name of host
		strcpy(p_working_data, name);
		ret->h_name = p_working_data;
		p_working_data += strlen(p_working_data) +1; // pass length + \0
		// alias list
		p_working_data_char_pp = (char **)p_working_data;
		p_working_data_char_pp[0] = ret->h_name;
		p_working_data_char_pp[1] = NULL;
		ret->h_aliases = p_working_data_char_pp;
		p_working_data = (char *)&p_working_data_char_pp[2];
		// host address type
		ret->h_addrtype = family;
		// length of address
		ret->h_length = pa->addr_len;
		// list of addresses
		if (family == AF_INET6)
		{
			FORMAT_LIST_OF_ADDRESSES(struct in6_addr, p_working_data, &pa->addr.ipv6_addr, ret);
		}
		else
		{
			FORMAT_LIST_OF_ADDRESSES(struct in_addr, p_working_data, &pa->addr.ipv4_addr, ret);
		}
	}

	return result;
}

/*
convert_ipv6_addresses_in_hostent(char *buf, size_t buflen, struct hostent *ret)
{
	char *temp_buf;

	temp_buf = (char *)malloc(buflen);



	// copy back to buf
	memcpy(buf, temp_buf, buflen);

	free(temp_buf);
}
*/
