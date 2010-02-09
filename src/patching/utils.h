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
#ifndef __UTILS_H__
#define __UTILS_H__

#include "socket_info.h"
void copy_sockaddr_to_psa(struct sockaddr *address, unsigned int address_len, struct polymorphic_sockaddr *psa);
void copy_psa_to_sockaddr(struct polymorphic_sockaddr *psa, struct sockaddr *address, unsigned int *address_len);
void copy_ipv4_addr_to_pa(struct in_addr *address, struct polymorphic_addr *pa);
void copy_ipv6_addr_to_pa(struct in6_addr *address, struct polymorphic_addr *pa);
void copy_pa_and_port_to_psa(struct polymorphic_addr *pa, unsigned int port, struct polymorphic_sockaddr *psa);
void copy_ipv4_addr_port_to_psa(struct in_addr *ipv4_addr, unsigned int port, struct polymorphic_sockaddr *psa);
void copy_ipv6_addr_port_to_psa(struct in6_addr *ipv6_addr, unsigned int port, struct polymorphic_sockaddr *psa);
int convert_pa_and_name_to_hostent(struct polymorphic_addr *pa, char *name, char *buf, size_t buflen, struct hostent *ret);
#endif
