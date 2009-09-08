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
#include <unistd.h>

#include "macros.h"
#include "fd_tools.h"

/*
 * Each of the following functions has to be in the following format:
 * -----------------------------------------------------------------------
 * 
 * <return_type> original_<function>(<args>)
 * {
 *	 <return_type> result;
 *
 *       __CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(<function>),
 *					ARGS(<function_args>),
 *					RETURN_VALUE_IF_FAILURE(<value>),
 *					RESULT_PTR(&result));
 *	 return result;
 * }
 *
 */


// Start of the network-related functions
// --------------------------------------

int original_accept(int socket, struct sockaddr *address,
              socklen_t *address_len)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(accept),
					ARGS(socket, address, address_len),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

int original_bind(int socket, const struct sockaddr *address,
              socklen_t address_len)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(bind),
					ARGS(socket, address, address_len),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

int original_close(int fd)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(close),
					ARGS(fd),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

int original_connect(int socket, const struct sockaddr *address,
              socklen_t address_len)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(connect),
					ARGS(socket, address, address_len),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

int original_getaddrinfo(const char *nodename,
		const char *servname,
		const struct addrinfo *hints,
		struct addrinfo **res)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(getaddrinfo),
					ARGS(nodename, servname, hints, res),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

struct hostent *original_gethostbyaddr(const void *addr, socklen_t len, int type)
{
	struct hostent *result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(gethostbyaddr),
					ARGS(addr, len, type),
					RETURN_VALUE_IF_FAILURE(NULL),
					RESULT_PTR(&result));
	return result;
}

struct hostent *original_gethostbyname(const char *name)
{
	struct hostent *result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(gethostbyname),
					ARGS(name),
					RETURN_VALUE_IF_FAILURE(NULL),
					RESULT_PTR(&result));
	return result;
}

int original_gethostbyname_r(const char *name,
		struct hostent *ret, char *buf, size_t buflen,
		struct hostent **result, int *h_errnop)
{
	int function_result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(gethostbyname_r),
					ARGS(name, ret, buf, buflen, result, h_errnop),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&function_result));
	return function_result;
}

int original_getnameinfo(const struct sockaddr *sa, socklen_t salen,
              char *node, socklen_t nodelen, char *service,
              socklen_t servicelen, unsigned int flags)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(getnameinfo),
					ARGS(sa, salen, node, nodelen, service, servicelen, flags),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));

	return result;
}

int original_pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      const struct timespec *timeout, const sigset_t *sigmask)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(pselect),
					ARGS(nfds, readfds, writefds, errorfds, timeout, sigmask),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));

	return result;
}

ssize_t original_read(int fd, void *buf, size_t count)
{
	ssize_t result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(read),
					ARGS(fd, buf, count),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

int original_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
      struct timeval *timeout)
{
	int result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(select),
					ARGS(nfds, readfds, writefds, errorfds, timeout),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));

	return result;
}

ssize_t original_write(int fd, const void *buf, size_t count)
{
	ssize_t result;

	__CALL_ORIGINAL_FUNCTION(	FUNCTION_NAME(write),
					ARGS(fd, buf, count),
					RETURN_VALUE_IF_FAILURE(-1),
					RESULT_PTR(&result));
	return result;
}

