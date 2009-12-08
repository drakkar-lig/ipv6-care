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
Etienne DUBLE 	-2.5:	Creation

*/
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>

#include "macros.h"
#include "common_networking_tools.h"

void register_info_chars(char *name, char *value);

// These functions are useful for the management of [p]poll() arguments
// ----------------------------------------------------------
int test_if_pollfd_table_contain_network_sockets(struct pollfd *fds, nfds_t nfds)
{
	unsigned int n;
	int result = 0; // false by default

	for (n=0; n<nfds; n++)
	{
		if (test_if_fd_is_a_network_socket(fds[n].fd) == 1)
		{
			result = 1; // true
			break;
		}
	}

	return result;
}

void register_pollfd_table_parameters(struct pollfd *fds, nfds_t nfds)
{
	char fd[32];
	unsigned int n;

	for (n=0; n<nfds; n++)
	{
		if (test_if_fd_is_a_network_socket(fds[n].fd) == 1)
		{
			snprintf(fd, sizeof(fd) -1, "%d", fds[n].fd);
			__REGISTER_INFO_CHARS("fd", fd);
		}
	}
}

