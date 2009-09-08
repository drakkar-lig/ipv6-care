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
Etienne DUBLE 	-2.3:	Removed test_if_fd_is_a_socket and use test_if_fd_is_a_network_socket
Etienne DUBLE 	-2.3:	Changed test_if_fd_sets_contain_sockets to test_if_fd_sets_contain_network_sockets
Etienne DUBLE 	-3.0:	networking_tools.h -> common_networking_tools.h

*/
#include <stdio.h>
#include <sys/socket.h>

#include "macros.h"
#include "common_networking_tools.h"

void register_info_chars(char *name, char *value);

// These functions are useful for the management of fd-sets 
// in 'select' and 'pselect'
// ----------------------------------------------------------
int test_if_fd_sets_contain_network_sockets(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds)
{
	int n;
	int result = 0; // false by default

	for (n=0; n<nfds; n++)
	{
		if ((readfds != 0)&&(FD_ISSET(n, readfds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				result = 1; // true
				break;
			}
		}

		if ((writefds != 0)&&(FD_ISSET(n, writefds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				result = 1; // true
				break;
			}
		}
		if ((errorfds != 0)&&(FD_ISSET(n, errorfds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				result = 1; // true
				break;
			}
		}
	}

	return result;
}

void register_fd_sets_parameters(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds)
{
	char info_name[32];
	int n;

	for (n=0; n<nfds; n++)
	{
		if ((readfds != 0)&&(FD_ISSET(n, readfds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				snprintf(info_name, sizeof(info_name) -1, "readfds[%d]", n);
				__REGISTER_INFO_CHARS(info_name, "1");
			}
		}

		if ((writefds != 0)&&(FD_ISSET(n, writefds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				snprintf(info_name, sizeof(info_name) -1, "writefds[%d]", n);
				__REGISTER_INFO_CHARS(info_name, "1");
			}
		}
		if ((errorfds != 0)&&(FD_ISSET(n, errorfds) != 0))
		{
			if (test_if_fd_is_a_network_socket(n))
			{
				snprintf(info_name, sizeof(info_name) -1, "errorfds[%d]", n);
				__REGISTER_INFO_CHARS(info_name, "1");
			}
		}
	}
}

