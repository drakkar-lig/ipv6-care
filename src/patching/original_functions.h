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
#ifndef __ORIGINAL_FUNCTIONS_H__
#define __ORIGINAL_FUNCTIONS_H__
#include <sys/select.h>

int original_accept(int socket, struct sockaddr *address,
              socklen_t *address_len);
int original_bind(int socket, const struct sockaddr *address,
              socklen_t address_len);
int original_close(int fd);
int original_connect(int socket, const struct sockaddr *address,
              socklen_t address_len);
int original_getaddrinfo(const char *nodename,
		const char *servname,
		const struct addrinfo *hints,
		struct addrinfo **res);
struct hostent *original_gethostbyaddr(const void *addr, socklen_t len, int type);
struct hostent *original_gethostbyname(const char *name);
int original_gethostbyname_r(const char *name,
		struct hostent *ret, char *buf, size_t buflen,
		struct hostent **result, int *h_errnop);
int original_getnameinfo(const struct sockaddr *sa, socklen_t salen,
		char *node, socklen_t nodelen, char *service,
		socklen_t servicelen, unsigned int flags);
int original_poll(struct pollfd *fds, nfds_t nfds, int timeout);
int original_ppoll(struct pollfd *fds, nfds_t nfds,
               const struct timespec *timeout, const sigset_t *sigmask);
int original_pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
	      const struct timespec *timeout, const sigset_t *sigmask);
ssize_t original_read(int fd, void *buf, size_t count);
int original_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
	      struct timeval *timeout);
ssize_t original_write(int fd, const void *buf, size_t count);

#endif
