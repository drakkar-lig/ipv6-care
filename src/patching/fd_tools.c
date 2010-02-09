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
Etienne DUBLE 	-3.0:	Added test_if_fd_is_a_network_socket(initial_socket)

*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "fd_tools.h"
#include "common_original_functions.h"
#include "common_networking_tools.h"
#include "created_sockets.h"
#include "family.h"
#include "addresses_and_names.h"

#define MAX_FREE_FILE_DESCRIPTORS	256

#define debug_print(...)

/*
	Consider the following scenario:

	// this is what the code of the program does
	... 				// initial state: fd == 0 -> stdin, fd == 1 -> stdout, fd == 2 -> stderr
	1- file = open(...); 		// => file = 3	
	2- s = socket(...IPv4...);	// => s = 4	
	3- close(file);			// => 3 is now free
	4- connect(s, ...) ... 		// this connect() call will call the IPv6 CARE handler:
		// this part is handled by IPv6 CARE 
		5- result = original_connect(s, ...);	// call of connect() of the libc
		   ... if this first connection attempt fails, IPv6 CARE will want to reopen s as an IPv6 socket:
		7- close(s);				// => 4 is now free 
		8- s = socket(...IPv6...);		// => s = 3, not 4!!! (because of line 3) 
		9- original_connect(s, ...);		// try to connect with the IPv6 socket
		
	In this case the calling program would be confused by the behavior of IPv6 CARE
	because the socket's fd would not be the same. 
	
	A correct code in order to reopen the socket on fd 4 would be, instead of line 7 and 8:
		close(s);               	// => 4 is now free 
		dummy_s = socket(...IPv6...); 	// => dummy_s = 3
		s = socket(...IPv6...); 	// => s = 4, ok
		close(dummy_s);	
	
	That's basically what the following code does. 
*/
int create_socket_on_specified_free_fd(int fd, int family, int socktype, int protocol)
{
	int result, new_socket;

	result = -1;

	debug_print(1, "Trying to create socket on fd = %d.\n", fd);

	// create the socket
	new_socket = socket(family, socktype, protocol);

	if (new_socket != -1)
	{	// if ok check if the file descriptor is the correct one
		if (new_socket == fd)
		{
			result = 0; // ok
			debug_print(1, "socket creation ok!\n");
		}
		else
		{
			// if not create a copy of the file descriptor
			// with the expected integer ...
			if (dup2(new_socket, fd) != -1)
			{	
				result = 0; // ok
				debug_print(1, "socket creation ok!\n");
			}

			// ... and close the original file descriptor
			original_close(new_socket);
		}
	}
	return result;
}

int get_additional_listening_socket_if_needed(int initial_socket)
{
	int on = 1, additional_listening_socket_needed;
	int created_socket;
	struct polymorphic_sockaddr *initial_socket_psa, created_socket_psa; 
	int type, protocol, backlog, v6only_option; 
	
	created_socket = -1;

	if (test_if_fd_is_a_network_socket(initial_socket) == 1)
	{
		created_socket = get_created_socket_for_initial_socket(initial_socket);

		if (created_socket != -1)
		{	// such a socket has already been created previously
			return created_socket;
		}
		else
		{
			initial_socket_psa = get_listening_socket_address(initial_socket);

			additional_listening_socket_needed = 1;
			if (initial_socket_psa->sockaddr.sa.sa_family == AF_INET6) // the existing socket is an IPv6 socket
			{
				// retrieve the IPV6_V6ONLY option in order to know if IPv4 clients are also accepted
				if (get_listening_socket_v6only_option(initial_socket) == 0)
				{	// this IPv6 socket also accepts IPv4 connections, so no need to continue
					additional_listening_socket_needed = 0;
				}
			}

			if (additional_listening_socket_needed == 1)
			{
				if (get_equivalent_address(initial_socket_psa, &created_socket_psa) == 0)
				{
					type = get_socket_type(initial_socket);
					protocol = get_socket_protocol(initial_socket);
					created_socket = socket(created_socket_psa.sockaddr.sa.sa_family, type, protocol);

					if (created_socket != -1)
					{
						// TO DO: remapper les setsokopt de la socket initiale
						// set SO_REUSEADDR option
						setsockopt(created_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
						
						// in case of an IPv6 socket, being an additional socket (i.e. there is already another socket 
						// listening for IPv4 clients) we must set IPV6_V6ONLY to 1 
						v6only_option = 0;
						if (created_socket_psa.sockaddr.sa.sa_family == AF_INET6)
						{
							setsockopt(created_socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&on, sizeof(on));
							v6only_option = 1;
						}
						if (bind(created_socket, &created_socket_psa.sockaddr.sa, created_socket_psa.sa_len) == -1)
						{
							close(created_socket);
							created_socket = -1;
						}
					}
					if (created_socket != -1)
					{
						backlog = get_listening_socket_backlog(initial_socket);
						if (listen(created_socket, backlog) == -1)
						{
							close(created_socket);
							created_socket = -1;
						}
						else
						{
							// register all the data about the socket we created
							register_created_socket(initial_socket, created_socket);
							register_socket_type(created_socket, type);
							register_socket_state(created_socket, socket_state_listening);
							register_socket_protocol(created_socket, protocol);
							register_listening_socket_address(created_socket, &created_socket_psa);
							register_listening_socket_backlog(created_socket, backlog);
							register_listening_socket_v6only_option(created_socket, v6only_option);
						}
					}
				}
			}
		}
	}
	return created_socket;
}

int wait_on_two_sockets(int socket1, int socket2)
{
	fd_set socket_list_mask;
	int nbfds;

	// prepare 'select' parameter
	FD_ZERO(&socket_list_mask);
	FD_SET(socket1, &socket_list_mask);
	FD_SET(socket2, &socket_list_mask);

	// wait on server sockets
	nbfds = original_select((socket1>socket2)?(socket1+1):(socket2+1), &socket_list_mask, NULL, NULL, NULL);

	// get the server socket which woke up the 'select'
	if (FD_ISSET(socket1, &socket_list_mask))
	{
		return socket1;
	}
	else
	{
		return socket2;
	}
}


int manage_socket_access_on_fd(enum list_of_fd_access_types access_type, int fd)
{
	switch(access_type)
	{
		case eAccessType_Accept:
			break;
		default:
			// TO DO: OTHERS
			break;
	}
	return fd;
}

void close_sockets_related_to_fd(int fd)
{
	int created_socket;
	
	created_socket = get_created_socket_for_initial_socket(fd);
	if (created_socket != -1)
	{
		close(created_socket);
	}
}

void manage_socket_accesses_on_fdset(int *nfds, fd_set *initial_fds, fd_set *final_fds)
{
	int fd, created_socket;
	int initial_nfds;

	initial_nfds = *nfds;

	FD_ZERO(final_fds);

	if (initial_fds != NULL)
	{
		for (fd = 0; fd < initial_nfds; fd++)
		{
			if (FD_ISSET(fd, initial_fds))
			{
				FD_SET(fd, final_fds);

				if (get_socket_state(fd) == socket_state_listening)
				{
					created_socket = get_additional_listening_socket_if_needed(fd);
					if (created_socket != -1)
					{	// a new socket was created, add it in the final_fds
						FD_SET(created_socket, final_fds);

						debug_print(1, "Created additional socket in order to wait on both IPv4 and IPv6 events.\n");

						// update nfds if needed
						if (created_socket >= *nfds)
						{
							*nfds = created_socket +1;
						}
					}
				}
			}
		}
	}
}

void remap_changes_to_initial_fdset(int nfds, fd_set *initial_fds, fd_set *final_fds)
{
	int fd, initial_socket;
	fd_set resulting_initial_fds;

	// It seems doing a FD_ZERO on the provided initial_fds is a bit too intrusive.
	// It caused problems with ssh, there might be a programming bug in it which comes
	// to light when we try to FD_ZERO(initial_fds).
	// So we do it in a less intrusive way:
	// 1) We update a local fd_set called resulting_initial_fds
	// 2) We report values to initial_fds by changing only the values which are different

	if (initial_fds != NULL)
	{ 
		FD_ZERO(&resulting_initial_fds);

		// 1)

		for (fd = 0; fd < nfds; fd++)
		{
			if (FD_ISSET(fd, final_fds))
			{
				initial_socket = get_initial_socket_for_created_socket(fd);
				if (initial_socket < 0)
				{	// fd has no corresponding initial_socket
					FD_SET(fd, &resulting_initial_fds);
				}
				else
				{	// fd was created by IPv6 CARE, set its initial_socket in initial_fds
					FD_SET(initial_socket, &resulting_initial_fds);
				}
			}
		}

		// 2)

		for (fd = 0; fd < nfds; fd++)
		{
			if (FD_ISSET(fd, &resulting_initial_fds) && !FD_ISSET(fd, initial_fds))
			{
				FD_SET(fd, initial_fds);
			}

			if (!FD_ISSET(fd, &resulting_initial_fds) && FD_ISSET(fd, initial_fds))
			{
				FD_CLR(fd, initial_fds);
			}
		}
	}
}

void manage_socket_accesses_on_pollfd_table(int nfds, int *final_nfds, struct pollfd *fds, struct pollfd **final_fds)
{
	int allocated, new_nfds, fd, index;
	int created_socket;

	allocated = nfds+2;
	*final_fds = realloc(*final_fds, allocated*sizeof(struct pollfd));
	memcpy(*final_fds, fds, nfds*sizeof(struct pollfd));
	new_nfds = nfds;

	for (index = 0; index < nfds; index++)
	{
		fd = fds[index].fd;
		if (get_socket_state(fd) == socket_state_listening)
		{
			created_socket = get_additional_listening_socket_if_needed(fd);
			if (created_socket != -1)
			{	// a new socket was created, add it in the final_fds
				debug_print(1, "Created additional socket in order to wait on both IPv4 and IPv6 events.\n");

				// enlarge the table if needed
				if (new_nfds == allocated)
				{
					allocated = 2*allocated;
					*final_fds = realloc(*final_fds, allocated*sizeof(struct pollfd));
				}

				// copy the info and set the fd as the new socket
				memcpy(&(*final_fds)[new_nfds], &fds[index], sizeof(struct pollfd));
				(*final_fds)[new_nfds].fd = created_socket;
				new_nfds ++;
			}
		}
	}

	*final_nfds = new_nfds;
}

void remap_changes_to_initial_pollfd_table(int nfds, int final_nfds, struct pollfd *initial_fds, struct pollfd *final_fds)
{
	int index, index2, fd, initial_socket;

	// start by copying back the nfds first elements
	memcpy(initial_fds, final_fds, nfds*sizeof(struct pollfd));

	// now manage the added elements
	for (index = nfds; index < final_nfds; index++)
	{
		if (final_fds[index].revents > 0) // if something happened there
		{
			fd = final_fds[index].fd;
			initial_socket = get_initial_socket_for_created_socket(fd);
			if (initial_socket >= 0)
			{	// fd was created by IPv6 CARE, set the flags on the initial socket

				// first, find where is this initial socket in the table
				for (index2 = 0; index2 < nfds; index2++)
				{
					if (final_fds[index2].fd == initial_socket)
					{
						// then, OR its flags
						initial_fds[index2].revents |= final_fds[index].revents;
						break;
					}
				}
			}
		}
	}
}

