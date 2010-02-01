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
Etienne DUBLE 	-2.1:	get_ip_string -> get_ip_string_and_port
Etienne DUBLE 	-2.3:	Added test_if_fd_is_a_network_socket

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include "get_string.h"

#define MAX_PORT_LENGTH 16

// this function gets a printable string representing an IP address, given a struct sockaddr pointer.
void get_ip_string_and_port(struct sockaddr *paddress, char *ip, int ip_length, int *port)
{
	char *percent;
	char port_string[MAX_PORT_LENGTH];

        // retrieve the ip and port number
        getnameinfo(paddress, sizeof(struct sockaddr_storage), ip, ip_length, port_string, 
			MAX_PORT_LENGTH, NI_NUMERICHOST|NI_NUMERICSERV);
	*port = atoi(port_string);

	// we do not need the scope of the IP
	// moreover it seems that we get an erroneous scope value when trying to display the scope 
	// of the IPv6 address of a DNS socket (created internally when we call gethostbyname for example).
	percent = strchr(ip, '%');
	if (percent != NULL)
	{
		*percent = '\0';
	}
}

// the get_family_string function return a printable word corresponding to the family given as an integer
struct st_assoc_name_value tb_families[] =
{	
	POSSIBILITY(AF_UNSPEC)
	POSSIBILITY(AF_INET)
	POSSIBILITY(AF_INET6)
};

char *get_family_string(int family)
{
	return get_string(tb_families, sizeof(tb_families)/sizeof(struct st_assoc_name_value), family);
}

// the get_sock_type_string function return a printable word corresponding to the socket type given as an integer
struct st_assoc_name_value tb_socktypes[] =
{	
	POSSIBILITY(SOCK_STREAM)
	POSSIBILITY(SOCK_DGRAM)
	POSSIBILITY(SOCK_SEQPACKET)
};

char *get_sock_type_string(int type)
{
	return get_string(tb_socktypes, sizeof(tb_socktypes)/sizeof(struct st_assoc_name_value), type);
}


