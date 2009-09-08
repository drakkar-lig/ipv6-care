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
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include "fd_tools.h"
#include "original_functions.h"

#define MAX_HOST_SIZE	128
#define MAX_SERV_SIZE	128
#define MAX_FREE_FILE_DESCRIPTORS	256

#define OTHER_FAMILY(af) ((af == AF_INET6)?AF_INET:AF_INET6)

int get_equivalent_address(struct sockaddr *sa, unsigned int sa_size, struct sockaddr *new_sa, unsigned int *new_sa_size)
{
	int result;
	char host[MAX_HOST_SIZE], service[MAX_SERV_SIZE];
	struct addrinfo hints, *address_list, *first_address;

	// get the hostname
	result = getnameinfo(sa, sa_size, host, MAX_HOST_SIZE, service, MAX_SERV_SIZE, NI_NUMERICSERV);
	if (result == 0)
	{
		// get its IP of the other family
		if (strcmp(host, "::") == 0)
		{
			strcpy(host, "0.0.0.0");
		}
		else
		{
			if (strcmp(host, "0.0.0.0") == 0)
			{
				strcpy(host, "::");
			}
		}
		
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = OTHER_FAMILY(sa->sa_family);
		result = getaddrinfo(host, service, &hints, &address_list);
		if (result == 0)
		{
			first_address = address_list;
			// copy data to pointer arguments
			memcpy(new_sa, first_address->ai_addr, first_address->ai_addrlen);
			*new_sa_size = first_address->ai_addrlen;
			// free the memory
			freeaddrinfo(address_list);
		}
	}
	return result;
}

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
	int result, new_socket, num_dummy_sockets, fd_index;
	int dummy_sockets[MAX_FREE_FILE_DESCRIPTORS];

	num_dummy_sockets = 0;
	result = -1;
	while (num_dummy_sockets < MAX_FREE_FILE_DESCRIPTORS)
	{
		// create the socket
		new_socket = socket(family, socktype, 0);
		if (new_socket == -1)
		{	// if error stop
			break;
		}
		else
		{	// if ok check if the file descriptor is the correct one
			if (new_socket == fd)
			{
				result = 0;
				break;
			}
			else
			{	// this socket will just keep the fd unavailable
				dummy_sockets[num_dummy_sockets] = new_socket;
				num_dummy_sockets++;
			}
		}
	}

	// these dummy sockets are not useful anymore
	for (fd_index = 0; fd_index < num_dummy_sockets; fd_index++)
	{
		original_close(dummy_sockets[fd_index]);
	}

	return result;
}

void get_listening_socket_info(int socket, struct listening_socket_data *data)
{
	unsigned int socktype_size;

	data->socket = socket;
	// retrieve the type of this socket
	socktype_size = sizeof(data->socktype);
	getsockopt(socket, SOL_SOCKET, SO_TYPE, (char *)&data->socktype, &socktype_size);
	// retrieve the address where this socket is bound
	data->sa_len = sizeof(data->sockaddr.sas);
	getsockname(socket, &data->sockaddr.sa, &data->sa_len);
}

int get_additional_listening_socket_if_needed(int initial_socket)
{
	int on = 1, additional_listening_socket_needed, v6only_option;
	struct listening_socket_data initial_socket_data, new_socket_data, *found_socket_data;
	unsigned int v6only_option_size;
	
	new_socket_data.socket = -1;
	found_socket_data = find_created_socket_for_initial_socket(initial_socket);

	if (found_socket_data != NULL)
	{	// such a socket has already been created previously
		return found_socket_data->socket;
	}
	else
	{
		get_listening_socket_info(initial_socket, &initial_socket_data);

		additional_listening_socket_needed = 1;
		if (initial_socket_data.sockaddr.sa.sa_family == AF_INET6) // the existing socket is an IPv6 socket
		{
			// retrieve the IPV6_V6ONLY option in order to know if IPv4 clients are also accepted
			v6only_option_size = sizeof(v6only_option);
			getsockopt(initial_socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&v6only_option, &v6only_option_size);
			if (v6only_option == 0)
			{	// this IPv6 socket also accepts IPv4 connections, so no need to continue
				additional_listening_socket_needed = 0;
			}
		}

		if (additional_listening_socket_needed == 1)
		{
			memcpy(&new_socket_data, &initial_socket_data, sizeof(new_socket_data));
			new_socket_data.socket = -1;

			// TO DO: 0 pour le protocol ce n est pas genial, il vaut mieux enregistrer
			// au moment de l appel socket ses caracteristiques (et tous les setsockopt() listen() bind()... 
			// pendant qu on y est) - meme problem pour le 10 dans le listen plus loin
			if (get_equivalent_address(	&initial_socket_data.sockaddr.sa, initial_socket_data.sa_len, 
							&new_socket_data.sockaddr.sa, &new_socket_data.sa_len) == 0)
			{
				new_socket_data.socket = socket(new_socket_data.sockaddr.sa.sa_family, new_socket_data.socktype, 0);
				if (new_socket_data.socket != -1)
				{
					// set SO_REUSEADDR option
					setsockopt(new_socket_data.socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
					
					// in case of an IPv6 socket, being an additional socket (i.e. there is already another socket 
					// listening for IPv4 clients) we must set IPV6_V6ONLY to 1 
					if (new_socket_data.sockaddr.sa.sa_family == AF_INET6)
					{
						setsockopt(new_socket_data.socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&on, sizeof(on));
					}
					if (bind(new_socket_data.socket, &new_socket_data.sockaddr.sa, new_socket_data.sa_len) == -1)
					{
						close(new_socket_data.socket);
						new_socket_data.socket = -1;
					}
				}
				if (new_socket_data.socket != -1)
				{
					if (listen(new_socket_data.socket, 10) == -1)
					{
						close(new_socket_data.socket);
						new_socket_data.socket = -1;
					}
					else
					{
						register_created_socket(initial_socket, &new_socket_data);
					}
				}
			}
		}
	}
	return new_socket_data.socket;
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
	struct listening_socket_data *found_socket_data;
	
	found_socket_data = find_created_socket_for_initial_socket(fd);
	if (found_socket_data != NULL)
	{
		close(found_socket_data->socket);
	}
}

void manage_socket_accesses_on_fdset(enum list_of_fd_access_types access_type, int *nfds, fd_set *initial_fds, fd_set *final_fds)
{
	int fd, new_socket_created;
	int is_a_listening_socket;
	unsigned int opt_len;
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

				opt_len = sizeof(is_a_listening_socket);
				if (getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &is_a_listening_socket, &opt_len) == 0)
				{
					if (is_a_listening_socket == 1)
					{
						new_socket_created = get_additional_listening_socket_if_needed(fd);
						if (new_socket_created != -1)
						{	// a new socket was created, add it in the final_fds
							FD_SET(new_socket_created, final_fds);

							// update nfds if needed
							if (new_socket_created >= *nfds)
							{
								*nfds = new_socket_created +1;
							}
						}
					}
				}
			}
		}
	}
}

void remap_changes_to_initial_fdset(enum list_of_fd_access_types access_type, int nfds, fd_set *initial_fds, fd_set *final_fds)
{
	int fd, initial_socket;

	if (initial_fds != NULL)
	{ 
		FD_ZERO(initial_fds);

		for (fd = 0; fd < nfds; fd++)
		{
			if (FD_ISSET(fd, final_fds))
			{
				initial_socket = find_initial_socket_for_created_socket(fd);
				if (initial_socket == -1)
				{	// fd was not created by IPv6 CARE, just set it back in initial_fds
					FD_SET(fd, initial_fds);
				}
				else
				{	// fd was created by IPv6 CARE, set its initial_socket in initial_fds
					FD_SET(initial_socket, initial_fds);
				}
			}
		}
	}
}

