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
June 29, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

#include "fd_tools.h"
#include "address_name_matches.h"
#include "original_functions.h"

#define OTHER_FAMILY(af) ((af == AF_INET6)?AF_INET:AF_INET6)
#define IS_AF_INET_OR_INET6(af) ((af == AF_INET)||(af == AF_INET6))

// Start of the network-related functions overriden
// ------------------------------------------------

int accept(int socket, struct sockaddr *address,
              socklen_t *address_len)
{
	int new_socket_created, resulting_socket;

	resulting_socket = socket; // default

	if IS_AF_INET_OR_INET6(address->sa_family)
	{
		new_socket_created = get_additional_listening_socket_if_needed(socket);

		if (new_socket_created != -1)
		{
			// wait on the two file descriptors
			resulting_socket = wait_on_two_sockets(socket, new_socket_created);
		}
	}

	return original_accept(resulting_socket, address, address_len);
}

int bind(int socket, const struct sockaddr *address,
              socklen_t address_len)
{
	int result;
	// TODO record_address(address);

	result = original_bind(socket, address, address_len);
	return result;
}

int close(int fd)
{
	int result;
	close_sockets_related_to_fd(fd);

	result = original_close(fd);
	return result;
}

int connect(int s, const struct sockaddr *address,
              socklen_t address_len)
{
	int result, socktype;
	unsigned int socktype_size;
	struct sockaddr_storage new_ss;
	struct sockaddr *new_sa = (struct sockaddr *)&new_ss;
	unsigned int new_sa_size = sizeof(new_ss);

	result = original_connect(s, address, address_len);

	if (		(result == -1)	&&
			IS_AF_INET_OR_INET6(address->sa_family)	&&
			(get_equivalent_address((struct sockaddr *)address, address_len, new_sa, &new_sa_size) == 0))
	{
		// retrieve the type of this socket
		socktype_size = sizeof(socktype);
		getsockopt(s, SOL_SOCKET, SO_TYPE, (char *)&socktype, &socktype_size);
		
		// close the socket - this way the fd integer should be available for our new socket
		// and the calling program will not notice that the socket is not the same
		close(s);

		// create a socket on the same file descriptor s
		// The socket family will be IPv4 if s was IPv6, and IPv6 if s was IPv4
		result = create_socket_on_specified_free_fd(s, OTHER_FAMILY(address->sa_family), socktype, 0);

		// if ok try to connect
		if (result == 0)
		{
			result = connect(s, new_sa, new_sa_size);
		}
	}

	return result;
}

int getaddrinfo(const char *nodename,
		const char *servname,
		const struct addrinfo *hints,
		struct addrinfo **res)
{
	int result;
//	struct addrinfo *paddress;

	result = original_getaddrinfo(nodename, servname, hints, res);
/*	
	if (result == 0)
	{
		for(paddress = *res; paddress != NULL; paddress = paddress->ai_next)
		{
			record_sa_address_name_match(paddress->ai_addr, (char *)nodename);
		}
	}
*/	return result;
}

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type)
{
	struct hostent *result;

	result = original_gethostbyaddr(addr, len, type);
//	record_hostent(result);
	return result;
}

struct hostent *gethostbyname(const char *name)
{
	struct hostent *result;

	result = original_gethostbyname(name);
//	record_hostent(result);
	return result;
}

int gethostbyname_r(const char *name,
		struct hostent *ret, char *buf, size_t buflen,
		struct hostent **result, int *h_errnop)
{
	int function_result;

	function_result = original_gethostbyname_r(name, ret, buf, buflen, result, h_errnop);
//	record_hostent(*result);
	return function_result;
}

int getnameinfo(const struct sockaddr *sa, socklen_t salen,
              char *node, socklen_t nodelen, char *service,
              socklen_t servicelen, unsigned int flags)
{
	int result;

	result = original_getnameinfo(sa, salen, node, nodelen, service, servicelen, flags);

/*	if ((node != NULL) && (nodelen != 0))
	{
		record_sa_address_name_match((struct sockaddr *)sa, node);
	}
*/	return result;
}

int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      const struct timespec *timeout, const sigset_t *sigmask)
{
	int result;
	fd_set final_readfds, final_writefds, final_errorfds;
	int modifiable_nfds;

	modifiable_nfds = nfds;

	manage_socket_accesses_on_fdset(&modifiable_nfds, readfds, &final_readfds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, writefds, &final_writefds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, errorfds, &final_errorfds);

	result = original_pselect(modifiable_nfds, &final_readfds, &final_writefds, &final_errorfds, timeout, sigmask);

	remap_changes_to_initial_fdset(modifiable_nfds, readfds, &final_readfds);
	remap_changes_to_initial_fdset(modifiable_nfds, writefds, &final_writefds);
	remap_changes_to_initial_fdset(modifiable_nfds, errorfds, &final_errorfds);
	return result;
}

ssize_t read(int fd, void *buf, size_t count)
{
	ssize_t result;
	int final_fd;

	final_fd = manage_socket_access_on_fd(eAccessType_Read, fd);

	result = original_read(final_fd, buf, count);
	return result;
}

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      struct timeval *timeout)
{
	int result;
	fd_set final_readfds, final_writefds, final_errorfds;
	int modifiable_nfds;
	
	modifiable_nfds = nfds;

	manage_socket_accesses_on_fdset(&modifiable_nfds, readfds, &final_readfds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, writefds, &final_writefds);
	manage_socket_accesses_on_fdset(&modifiable_nfds, errorfds, &final_errorfds);

	result = original_select(modifiable_nfds, &final_readfds, &final_writefds, &final_errorfds, timeout);

	remap_changes_to_initial_fdset(modifiable_nfds, readfds, &final_readfds);
	remap_changes_to_initial_fdset(modifiable_nfds, writefds, &final_writefds);
	remap_changes_to_initial_fdset(modifiable_nfds, errorfds, &final_errorfds);
	return result;
}

ssize_t write(int fd, const void *buf, size_t count)
{
	ssize_t result;
	int final_fd;

	final_fd = manage_socket_access_on_fd(eAccessType_Write, fd);

	result = original_write(final_fd, buf, count);
	return result;
}

