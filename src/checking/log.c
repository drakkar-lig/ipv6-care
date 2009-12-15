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
Etienne DUBLE 	-2.0:	Added warning about interpreted languages
Etienne DUBLE 	-2.1:	Suppress compilation warning on recent compilers
Etienne DUBLE 	-2.3:	remove " with []" when no arguments are logged
Etienne DUBLE 	-2.4:	check if the log file could be opened
Etienne DUBLE 	-2.5:	Management of messages to stdout when running daemons
Etienne DUBLE 	-2.5:	Removed variable log_all, log_needed

*/
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "append_to_string.h"
#include "filesystem.h"
#include "interpreted_language.h"
#include "common_colors.h"
#include "common_fd_tools.h"

extern int interpreted_language;
extern int verbose_level;

extern __thread int function_depth;
extern __thread char *log_file_content;
extern __thread char *log_function_line;
extern __thread int index_last_line;
extern __thread int log_this_function;

#define ONLINE_LOG_PREFIX GREEN "IPV6 CARE detected:" BLUE
#define ONLINE_LOG_SUFFIX ENDCOLOR

void log_if_needed()
{
	FILE* file;

	if (log_file_content != NULL)
	{
		file = open_log_file();
		if (file != NULL)
		{
			fprintf(file, "%s", log_file_content);
			if (interpreted_language == 1)
			{
				fprintf(file, "%s", WARNING_INTERPRETED_LANGUAGE);
			}
			fclose(file);
		}
	}
}

void register_info_start(char *function_name)
{
	int depth;

	for (depth=0; depth<function_depth; depth++)
	{
		append_to_string(&log_function_line, "  ");
	}

	append_to_string(&log_function_line, function_name);
	append_to_string(&log_function_line, "() with [");

	log_this_function = 1;
}

void register_info_end()
{
	int current_line_size;

	if (log_this_function == 1)
	{	// if this function must be logged
		
		current_line_size = strlen(log_function_line);	
		if (log_function_line[current_line_size-1] == '[') 
		{	// no arguments, remove the " with ["
			log_function_line[current_line_size-7] = '\0';
		}
		else
		{
			append_to_string(&log_function_line, " ]");
		}

		current_line_size = strlen(log_function_line);	

		// if verbose_level greater than 0 the function calls are not only
		// registered in the log file but also displayed 
		// in the standard output of the program
		if (verbose_level > 0)
		{
			PRINTF(ONLINE_LOG_PREFIX " %s" ONLINE_LOG_SUFFIX "\n", log_function_line);
		}

		if ((index_last_line != -1) && (memcmp(log_file_content + index_last_line, log_function_line, current_line_size) == 0))
		{	
			// The current line is the same as the previous one: we remove it and append "repeated several times" instead
			log_file_content[index_last_line + current_line_size] = '\0';
			append_to_string(&log_file_content, " repeated several times\n");
		}
		else
		{	// Otherwise we pass to the next one
			index_last_line = 0;
			if (log_file_content != NULL)
			{
				index_last_line = strlen(log_file_content);
			}
			append_to_string(&log_file_content, "%s\n", log_function_line);
		}

		log_if_needed();
	}

	free(log_function_line);
	log_function_line = NULL;
}

void register_info_int(char *name, int value)
{
	append_to_string(&log_function_line, " %s=%d", name, value);
}

void register_info_chars(char *name, char *value)
{
	append_to_string(&log_function_line, " %s=%s", name, value);
}

void do_not_log_this_function()
{
	log_this_function = 0;
}

