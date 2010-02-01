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
July 29, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/
#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <netinet/in.h>

union u_sockaddr
{
	struct sockaddr_storage sas;
	struct sockaddr sa;
	struct sockaddr_in sa_in;
	struct sockaddr_in6 sa_in6;
};

struct polymorphic_sockaddr 
{
	union u_sockaddr sockaddr;
	unsigned int sa_len;
};

union u_addr
{
	struct in_addr ipv4_addr;
	struct in6_addr ipv6_addr;
};

struct polymorphic_addr 
{
	union u_addr addr;
	int addr_len;
	int family;
};

#endif 

