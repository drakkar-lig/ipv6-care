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
Etienne DUBLE 	-2.2:	Added test_if_fd_is_a_socket
Etienne DUBLE 	-2.3:	Removed test_if_fd_is_a_socket
Etienne DUBLE 	-2.3:	Changed test_if_fd_sets_contain_sockets to test_if_fd_sets_contain_network_sockets

*/
#ifndef __FD_SET_TOOLS_H__
#define __FD_SET_TOOLS_H__
#include <sys/types.h>

int test_if_fd_sets_contain_network_sockets(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds);
void register_fd_sets_parameters(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds);
#endif
