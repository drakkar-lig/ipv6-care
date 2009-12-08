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
#ifndef __FD_TOOLS_H__
#define __FD_TOOLS_H__

#define _GNU_SOURCE
#include <sys/select.h>
#include <poll.h>

#include "created_sockets.h"

enum list_of_fd_access_types {
	eAccessType_Read,
	eAccessType_Write,
	eAccessType_Error,
	eAccessType_Accept,
	eAccessType_Connect
};

int get_equivalent_address(struct sockaddr *sa, unsigned int sa_size, struct sockaddr *new_sa, unsigned int *new_sa_size);
int create_socket_on_specified_free_fd(int fd, int family, int socktype, int protocol);
int get_additional_listening_socket_if_needed(int initial_socket);
int wait_on_two_sockets(int socket1, int socket2);
int manage_socket_access_on_fd(enum list_of_fd_access_types access_type, int fd);
void close_sockets_related_to_fd(int fd);
void manage_socket_accesses_on_fdset(int *nfds, fd_set *fds, fd_set *final_fds);
void manage_socket_accesses_on_pollfd_table(int nfds, int *final_nfds, struct pollfd *fds, struct pollfd **final_fds);
void remap_changes_to_initial_fdset(int nfds, fd_set *initial_fds, fd_set *final_fds);
void remap_changes_to_initial_pollfd_table(int nfds, int final_nfds, struct pollfd *initial_fds, struct pollfd *final_fds);

#endif
