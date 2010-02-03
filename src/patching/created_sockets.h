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
#ifndef __CREATED_SOCKETS_H__
#define __CREATED_SOCKETS_H__

#define INITIAL_SOCKET_WAS_CLOSED -2
#define COMM_SOCKET_OF_A_CREATED_SOCKET -3

void register_created_socket(int initial_socket, int created_socket);
int get_initial_socket_for_created_socket(int created_socket);
int get_created_socket_for_initial_socket(int initial_socket);
#endif
