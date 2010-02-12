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

#include "common_original_functions.h"
#include "ipv6_to_ipv4_mappings.h"
#include "utils.h"

#ifndef IPV4_MAPPING_PREFIX
#define IPV4_MAPPING_PREFIX "10.133"
#endif

struct mapping_entry {
	struct mapping_data data;
	LIST_ENTRY(mapping_entry) entries;
};

LIST_HEAD(mapping_list_head_type, mapping_entry) mapping_list_head;

int mapping_list_initialised = 0;
int mapping_index = 0;

void init_mapping_list_if_needed()
{
	if (mapping_list_initialised == 0)
	{
		LIST_INIT(&mapping_list_head);
		mapping_list_initialised = 1;
	}
}

void fill_mapping_data_for_ipv6_addr(struct polymorphic_addr *real_ipv6_pa, struct mapping_data *data)
{
	int my_index = mapping_index++; // this is considered atomic (in a multi-threaded program)
	struct in_addr ipv4_addr;
	int length;

	my_index %= 256*256; // avoid overflows...

	// pa[real_ipv6_addr]
	memcpy(&data->pa[real_ipv6_addr], real_ipv6_pa, sizeof(*real_ipv6_pa));

	// ip_text_forms[mapped_ipv4]
	snprintf(data->ip_text_forms[mapped_ipv4], MAX_IPV4_STRING_LENGTH, 
			"%s.%d.%d", IPV4_MAPPING_PREFIX, my_index / 256, my_index % 256);
	// pa[mapped_ipv4_addr]
	original_inet_pton(AF_INET, data->ip_text_forms[mapped_ipv4], &ipv4_addr);
	copy_ipv4_addr_to_pa(&ipv4_addr, &data->pa[mapped_ipv4_addr]);

	// ip_text_forms[full_ipv6]
	original_inet_ntop(AF_INET6, &real_ipv6_pa->addr.ipv6_addr, data->ip_text_forms[full_ipv6], MAX_IPV6_STRING_LENGTH);

	// ip_text_forms[abbreviated_ipv6]
	if (strlen(data->ip_text_forms[full_ipv6]) > MAX_IPV4_STRING_LENGTH -1)
	{
		data->ip_text_forms[abbreviated_ipv6][0] = '.';
		data->ip_text_forms[abbreviated_ipv6][1] = '.';
		length = strlen(data->ip_text_forms[full_ipv6]);
		strcpy(&data->ip_text_forms[abbreviated_ipv6][2], &data->ip_text_forms[full_ipv6][length - MAX_IPV4_STRING_LENGTH +3]);
	}
	else
	{
		strcpy(data->ip_text_forms[abbreviated_ipv6], data->ip_text_forms[full_ipv6]);
	}
}

struct mapping_data *get_mapping_for_address(enum address_type_in_mapping type_of_address, struct polymorphic_addr *pa)
{
	struct mapping_entry *entry;
	struct mapping_data *result;

	init_mapping_list_if_needed();
	result = NULL;

	for (entry = mapping_list_head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		if (compare_pa(&entry->data.pa[type_of_address], pa) == 0)
		{
			result = &entry->data;
			break;
		}
	}

	if ((result == NULL)&&(type_of_address == real_ipv6_addr))
	{
		entry = malloc(sizeof(struct mapping_entry));

		fill_mapping_data_for_ipv6_addr(pa, &entry->data);

		LIST_INSERT_HEAD(&mapping_list_head, entry, entries);
		result = &entry->data;
	}

	return result;
}

struct mapping_data *get_mapping_for_text_form(char *text_form)
{
	struct mapping_entry *entry;
	struct mapping_data *result;

	init_mapping_list_if_needed();
	result = NULL;
	int text_form_index;

	for (entry = mapping_list_head.lh_first; entry != NULL; entry = entry->entries.le_next)
	{
		for (text_form_index = 0; text_form_index < number_of_mapped_ip_text_forms; text_form_index++)
		{
			if (strncmp(entry->data.ip_text_forms[text_form_index], text_form, MAX_IPV6_STRING_LENGTH) == 0)
			{
				result = &entry->data;
				break;
			}
		}
	}

	return result;
}

