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

*/
#include "get_string.h"

// the get_string function is a generic function used to translate an integer constant value in a printable 
// string. 
// this is used to properly print the address families and the socket types.
char *get_string(struct st_assoc_name_value *tb_possibilities, int nb_possibilities, int value)
{
	int possibility;

	for (possibility = 0; possibility<nb_possibilities; possibility++)
	{
		if (tb_possibilities[possibility].value == value)
		{
			break;
		}
	}
	
	if (possibility<nb_possibilities)
	{
		return tb_possibilities[possibility].name;
	}
	else
	{
		return "unknown";
	}
}

