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
Etienne DUBLE 	-2.5:	Creation
Etienne DUBLE 	-2.5:	Improved robustness

*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

extern FILE *tty_fd;

#define MAX_TTY_NAME_SIZE 128

// This function saves the fd corresponding to stdout.
// It is useful for daemons which usually close their 
// tty file descriptors, therefore IPv6 CARE cannot
// write messages to the user anymore.

void save_tty_fd()
{
	char tty_name[MAX_TTY_NAME_SIZE];
	int done_ok = 0;

	if (isatty(1))
	{
		if (ttyname_r(1, tty_name, MAX_TTY_NAME_SIZE) == 0)
		{
			tty_fd = fopen(tty_name, "w+");
			if (tty_fd != NULL)
			{
				done_ok = 1;
			}
		} 
	}

	if (done_ok == 0)
	{
		tty_fd = stdout;
	}
}


