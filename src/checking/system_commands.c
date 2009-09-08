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
Etienne DUBLE 	-2.2:	Creation

*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "append_to_string.h"

extern char *ld_preload_value;

void unset_ld_preload()
{
	// save LD_PRELOAD if it was not done yet
	if (ld_preload_value == NULL)
	{
		asprintf(&ld_preload_value, "%s", getenv("LD_PRELOAD"));
	}

	unsetenv("LD_PRELOAD");
}

void set_ld_preload()
{
	setenv("LD_PRELOAD", ld_preload_value, 1);
}

void get_result_of_command(char **storage_string, char *command)
{
	FILE *fp;
	char c[2];

	// we temporarily unset LD_PRELOAD (we don't want the 
	// subprocess created by popen to be monitored by ipv6-care)
	unset_ld_preload();

	c[1] = '\0';

	// let's run the command and read its output
	fp = popen(command, "r");
	while (!feof(fp))
	{
		fread(c, 1, 1, fp);
		if ((c[0] != '\n') && (c[0] != '\r'))
		{
			append_to_string(storage_string, c);
		}
	}
	pclose(fp);

	// we restore LD_PRELOAD
	set_ld_preload();
}

void run_command(char *command)
{
	// we temporarily unset LD_PRELOAD (we don't want the 
	// subprocess created by system() to be monitored by ipv6-care)
	unset_ld_preload();

	// let's run the command
	system(command);
	
	// we restore LD_PRELOAD
	set_ld_preload();
}

