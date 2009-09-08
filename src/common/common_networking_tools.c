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
Sep 1, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/
#include <stdio.h>
#include <sys/socket.h>

// These functions are useful for networking operations
// ----------------------------------------------------

// this function returns 1 if the family of the socket is AF_INET or AF_INET6, 
// 0 otherwise, and -1 if an error occurs (fd is not a socket, etc.)
int test_if_fd_is_a_network_socket(int fd)
{
	struct sockaddr_storage sas;
	unsigned int size = sizeof(sas);
	struct sockaddr *sa = (struct sockaddr *)&sas;

	if(getsockname(fd, sa, &size) == -1)
	{
		return -1;
	}
	else
	{
		if ((sa->sa_family == AF_INET)||(sa->sa_family == AF_INET6))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

