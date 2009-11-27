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
Etienne DUBLE 	-1.0:	Creation
Etienne DUBLE 	-2.1:	get_ip_string -> get_ip_string_and_port
Etienne DUBLE 	-2.3:	Added test_if_fd_is_a_network_socket
Etienne DUBLE 	-2.4:	Removed test_if_fd_is_a_network_socket

*/
#ifndef __NETWORKING_TOOLS_H__
#define __NETWORKING_TOOLS_H__

#include <sys/socket.h>
void get_ip_string_and_port(struct sockaddr *paddress, char *ip, int ip_length, int *port);
char *get_family_string(int family);
char *get_sock_type_string(int type);

#endif