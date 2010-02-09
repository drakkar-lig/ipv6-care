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
#ifndef __CONNECTION_HANDLING_H__
#define __CONNECTION_HANDLING_H__

struct ipv4_mapping_data *get_mapping_data_if_host_is_ipv6_only(struct polymorphic_sockaddr *psa);
int try_connect_and_register_connection(int s, struct polymorphic_sockaddr *psa, 
					int *connect_call_result, int *connect_call_errno);
int try_connect_using_ipv6_addr_of_mapping(int s, struct polymorphic_sockaddr *ipv4_psa, struct ipv4_mapping_data *mapping_data,
					int *connect_call_result, int *connect_call_errno);
int try_connect_using_address_of_other_family(int s, struct polymorphic_sockaddr *psa, 
					int *connect_call_result, int *connect_call_errno);

#endif
