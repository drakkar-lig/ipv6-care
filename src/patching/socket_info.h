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
#ifndef __SOCKET_INFO_H__
#define __SOCKET_INFO_H__

#include "address.h"

struct socket_data_listening
{
	int backlog;
	struct polymorphic_sockaddr address;
	int v6only_option;
};

struct socket_data_communicating
{
	struct polymorphic_sockaddr local_address;
	struct polymorphic_sockaddr remote_address;
};

union u_socket_data_per_state
{
	struct socket_data_listening listening;
	struct socket_data_communicating communicating;
};

enum socket_state
{
	socket_state_created,
	socket_state_listening,
	socket_state_communicating
};

struct socket_data
{
	int fd;
	int type;
	int protocol;
	enum socket_state state;
	union u_socket_data_per_state data_per_state;
	int flag_data_registered;
};

int get_socket_type(int fd);
void register_socket_type(int fd, int type);
enum socket_state get_socket_state(int fd);
void register_socket_state(int fd, enum socket_state state);
int get_socket_protocol(int fd);
void register_socket_protocol(int fd, int protocol);
struct polymorphic_sockaddr *get_listening_socket_address(int fd);
void register_listening_socket_address(int fd, struct polymorphic_sockaddr *sa);
int get_listening_socket_backlog(int fd);
void register_listening_socket_backlog(int fd, int backlog);
int get_listening_socket_v6only_option(int fd);
void register_listening_socket_v6only_option(int fd, int v6only_option);
struct polymorphic_sockaddr *get_local_socket_address(int fd);
void register_local_socket_address(int fd, struct polymorphic_sockaddr *sa);
struct polymorphic_sockaddr *get_remote_socket_address(int fd);
void register_remote_socket_address(int fd, struct polymorphic_sockaddr *sa);

#endif
