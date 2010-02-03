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
December 17, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/

#include <sys/queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "ipv6_to_ipv4_mappings.h"

#ifndef IPV4_MAPPING_PREFIX
#define IPV4_MAPPING_PREFIX "10.133"
#endif

struct ipv4_mapping_entry {
	struct ipv4_mapping_data data;
	LIST_ENTRY(ipv4_mapping_entry) entries;
};

LIST_HEAD(ipv4_mapping_list_head_type, ipv4_mapping_entry) ipv4_mapping_list_head;

int ipv4_mapping_list_initialised = 0;
int ipv4_mapping_index = 0;

void init_ipv4_mapping_list_if_needed()
{
	if (ipv4_mapping_list_initialised == 0)
	{
		LIST_INIT(&ipv4_mapping_list_head);
		ipv4_mapping_list_initialised = 1;
	}
}

void compute_mapped_ipv4_addr(struct in6_addr *real_ipv6_addr __attribute__ ((unused)), struct in_addr *mapped_ipv4_addr)
{
	char ipv4_string[MAX_IPV4_STRING_LENGTH]; 
	int my_index = ipv4_mapping_index++; // this is considered atomic (in a multi-threaded program)
	// TO DO: check that we do not overflow (ipv4_mapping_index might be too high)
	snprintf(ipv4_string, MAX_IPV4_STRING_LENGTH, "%s.%d.%d", IPV4_MAPPING_PREFIX, my_index / 256, my_index % 256);
	inet_pton(AF_INET, ipv4_string, mapped_ipv4_addr);
}

void compute_mapped_text_form(struct in6_addr *real_ipv6_addr, char *mapped_text_form)
{
	char ipv6_string[MAX_IPV6_STRING_LENGTH];
	inet_ntop(AF_INET6, real_ipv6_addr, ipv6_string, MAX_IPV6_STRING_LENGTH);
	if (strlen(ipv6_string) > MAX_IPV4_STRING_LENGTH -1)
	{
		mapped_text_form[0] = '.';
		mapped_text_form[1] = '.';
		strcpy(&mapped_text_form[2], &ipv6_string[strlen(ipv6_string) - MAX_IPV4_STRING_LENGTH +3]);
	}
	else
	{
		strcpy(mapped_text_form, ipv6_string);
	}
}

struct ipv4_mapping_data *get_ipv4_mapping_for_real_ipv6_addr(struct in6_addr *real_ipv6_addr)
{
	struct ipv4_mapping_entry *entry;
	struct ipv4_mapping_data *result;

	init_ipv4_mapping_list_if_needed();
	result = NULL;

	for (entry = ipv4_mapping_list_head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (memcmp(&entry->data.real_ipv6_addr, real_ipv6_addr, sizeof(*real_ipv6_addr)) == 0)
		{
			result = &entry->data;
			break;
		}
	}

	if (result == NULL)
	{
		entry = malloc(sizeof(struct ipv4_mapping_entry));

		memcpy(&entry->data.real_ipv6_addr, real_ipv6_addr, sizeof(*real_ipv6_addr));
		compute_mapped_ipv4_addr(&entry->data.real_ipv6_addr, &entry->data.mapped_ipv4_addr);
		compute_mapped_text_form(&entry->data.real_ipv6_addr, entry->data.mapped_text_form);

		LIST_INSERT_HEAD(&ipv4_mapping_list_head, entry, entries);
		result = &entry->data;
	}
	return result;
}

struct ipv4_mapping_data *get_ipv4_mapping_for_mapped_ipv4_addr(struct in_addr *mapped_ipv4_addr)
{
	struct ipv4_mapping_entry *entry;
	struct ipv4_mapping_data *result;

	init_ipv4_mapping_list_if_needed();
	result = NULL;

	for (entry = ipv4_mapping_list_head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (memcmp(&entry->data.mapped_ipv4_addr, mapped_ipv4_addr, sizeof(*mapped_ipv4_addr)) == 0)
		{
			result = &entry->data;
			break;
		}
	}

	return result;
}

struct ipv4_mapping_data *get_ipv4_mapping_for_mapped_text_form(char *mapped_text_form)
{
	struct ipv4_mapping_entry *entry;
	struct ipv4_mapping_data *result;

	init_ipv4_mapping_list_if_needed();
	result = NULL;

	for (entry = ipv4_mapping_list_head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (strncmp(entry->data.mapped_text_form, mapped_text_form, MAX_IPV4_STRING_LENGTH) == 0)
		{
			result = &entry->data;
			break;
		}
	}

	return result;
}

