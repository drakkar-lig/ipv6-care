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
Etienne DUBLE 	-2.2:	get_program_name() no longer used
Etienne DUBLE 	-2.4:	Moved to the common directory
Etienne DUBLE 	-2.4:	Added get_thread_id

*/
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdarg.h>

// This function tries to locate the original networking function of the libc
void *get_symbol(int num_args, char *symbol, ... /* optional symbol versions */)
{
	void *p_symbol = NULL;
	char *dlerr, *symbol_version;
	va_list ap;
	int i;

	// try the given symbol versions provided first, if any
	va_start(ap, symbol);
	for(i=1; i<num_args; i++)
	{
		symbol_version = va_arg(ap, char *);
		p_symbol = dlvsym(RTLD_NEXT,symbol,symbol_version);
		if (p_symbol != NULL)
		{
			break;
		}
	}
	va_end(ap);
	
	// try dlsym with no version specified
	if (p_symbol == NULL)
	{
		p_symbol = dlsym(RTLD_NEXT,symbol);
	}
	
        if (p_symbol == NULL)
        {
		dlerr= dlerror(); 
		if (!dlerr)
		{
			dlerr= "Unknown reason";
		}

                fprintf(stderr, "failed to find original function: %s!\n", dlerr);
		errno = ENOSYS;
        }
	return p_symbol;
}
/*
// This function retrieves the name of the current program
char *get_program_name()
{
	// faire popen avec
	// set -- $(ps -p $$ -o args=); echo $(basename $(expr $1 : "[^[:alpha:]]*\([[:alpha:]].*\)"))
	// ?
	return getenv("_");
}
*/

int get_thread_id()
{
	return syscall(SYS_gettid);
}

