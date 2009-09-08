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

#include <sys/queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "created_sockets.h"

/*	List Example --------------------------------------------------

	LIST_HEAD(listhead, entry) head;
	struct listhead *headp;                 // List head.
	struct entry {
		...
		LIST_ENTRY(entry) entries;          // List. 
		...
	} *n1, *n2, *np;

	LIST_INIT(&head);                       // Initialize the list. 

	n1 = malloc(sizeof(struct entry));      // Insert at the head. 
	LIST_INSERT_HEAD(&head, n1, entries);

	n2 = malloc(sizeof(struct entry));      // Insert after. 
	LIST_INSERT_AFTER(n1, n2, entries);
	// Forward traversal. 
	for (np = head.lh_first; np != NULL; np = np->entries.le_next)
		np-> ...

	while (head.lh_first != NULL)           // Delete. 
		LIST_REMOVE(head.lh_first, entries);

	free(n1);
	free(n2);
*/

struct created_socket_entry {
	struct listening_socket_data data;
	int initial_socket;
	LIST_ENTRY(created_socket_entry) entries;
};

LIST_HEAD(listhead, created_socket_entry) head;

int list_initialised = 0;

void init_list_if_needed()
{
	if (list_initialised == 0)
	{
		LIST_INIT(&head);
		list_initialised = 1;
	}
}

void register_created_socket(int initial_socket, struct listening_socket_data *data)
{
	struct created_socket_entry *entry;

	init_list_if_needed();

	entry = malloc(sizeof(struct created_socket_entry));
	entry->data.socket = data->socket;
	entry->data.socktype = data->socktype;
	memcpy(&entry->data.sockaddr.sas, &data->sockaddr.sas, sizeof(entry->data.sockaddr.sas));
	entry->data.sa_len = data->sa_len;
	entry->initial_socket = initial_socket;

	LIST_INSERT_HEAD(&head, entry, entries);
}

struct listening_socket_data *find_created_socket_for_initial_socket(int initial_socket)
{
	struct created_socket_entry *entry;
	struct listening_socket_data *result;

	result = NULL;

	for (entry = head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (entry->initial_socket == initial_socket)
		{
			result = &entry->data;
		}
	}

	return result;
}

int find_initial_socket_for_created_socket(int created_socket)
{
	struct created_socket_entry *entry;
	int result;

	result = -1;

	for (entry = head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (entry->data.socket == created_socket)
		{
			result = entry->initial_socket;
		}
	}

	return result;
}

