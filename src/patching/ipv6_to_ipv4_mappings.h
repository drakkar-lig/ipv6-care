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
December 17, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/
#ifndef __IPV6_TO_IPV4_MAPPINGS_H__
#define __IPV6_TO_IPV4_MAPPINGS_H__

#include "address.h"

#define MAX_IPV4_STRING_LENGTH 16	// ex: 155.133.253.142 + \0 -> 16 chars
#define MAX_IPV6_STRING_LENGTH 40	// ex: 2001:2001:2001:2001:2001:2001:2001:2001 + \0 -> 40 chars

enum mapped_ip_text_forms
{
	abbreviated_ipv6,
	full_ipv6,
	mapped_ipv4,
	number_of_mapped_ip_text_forms
};

enum address_type_in_mapping
{
	real_ipv6_addr, 
	mapped_ipv4_addr,
	number_of_address_types_in_mapping
};

struct mapping_data {
	struct polymorphic_addr pa[number_of_address_types_in_mapping];
	char ip_text_forms[number_of_mapped_ip_text_forms][MAX_IPV6_STRING_LENGTH];
};

struct mapping_data *get_mapping_for_address(enum address_type_in_mapping type_of_address, struct polymorphic_addr *pa);
struct mapping_data *get_mapping_for_text_form(char *text_form);
#endif
