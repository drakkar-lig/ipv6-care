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
Etienne DUBLE 	-2.0:	Correct a bug if stack returned is not as expected
Etienne DUBLE   -2.0:	Improved stack trace if function not found
Etienne DUBLE 	-2.0:	Added warning about interpreted languages
Etienne DUBLE 	-2.2:	system() -> run_command() => Disable LD_PRELOAD in the subprocesses
Etienne DUBLE 	-2.2:	get_interpreter_name() -> save_interpreter_name()
Etienne DUBLE 	-2.4:	Provide diagnostic if system command fails
Etienne DUBLE   -3.0:   Avoid broken pipe errors (2>/dev/null for process before '|')

*/
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>

#include "append_to_string.h"
#include "interpreted_language.h"
#include "system_commands.h"

#define __MAX_STACK_TRACE		200
#define __PROCESS_STACKS_FILENAME 	"process_stacks"

extern int interpreted_language;
extern char *interpreter_name; 

// This function gets the name of the current executable
// in the case of an interpreted language, it will be the interpreter 
void save_interpreter_name()
{
	void *array[__MAX_STACK_TRACE];
	size_t size;
	char **strings;
	int index_first_character_after_name;

	// get the current back trace of the program
	size = backtrace (array, __MAX_STACK_TRACE);
	strings = backtrace_symbols (array, size);

	// last line will be the first program called
	index_first_character_after_name = strcspn(strings[size -1], " (");
	strings[size -1][index_first_character_after_name] = '\0';
	asprintf(&interpreter_name, "%s", basename(strings[size -1]));

	free (strings);
}

// This function writes the current process stack in a file in the given directory
void write_stack_file(char *directory)
{
	void *array[__MAX_STACK_TRACE];
	size_t size;
	char **strings;
	size_t i;
	char *command = NULL, *last_file = NULL, *index_hexa, *index_end_hexa;
	int index_first_character_after_name;

	// get the current backtrace of the program
	size = backtrace (array, __MAX_STACK_TRACE);
	strings = backtrace_symbols (array, size);

	// start creating a shell command
	asprintf(&command, "LD_PRELOAD=\"\"; { ");

	// loop for each function of the stack
	for (i = 0; i < size; i++)
	{
		if (strstr(strings[i], "libipv6_checker") != NULL)
		{
			continue;
		}

		// we do not take into account the functions within this 
		// ipv6 code checker library.
		// moreover we expect that the line is
		// <object_file_which_contains_function> [<hexa_location>] 
		index_first_character_after_name = strcspn(strings[i], " (");

		if (	(strstr(strings[i], "libipv6_care") != NULL) ||
			(index_first_character_after_name == (int)strlen(strings[i])) ||
			(strings[i][0] == '[') ||
			(strchr(strings[i], '[') == NULL))
		{	// in these cases we ignore this line
			continue;
		}

		// we separate the word corresponding to the object file
		strings[i][index_first_character_after_name] = '\0';

		// after this object file we have the position in this object file
		// as an hexadecimal number.
		// we want to use the addr2line command to know the name of the function
		// this point in the file corresponds to. 
		// in case the tested program was compiled with -g, we will also get
		// the source file name and line number.
		// since using addr2line can be expensive for execution time, 
		// we try to use it only one time for each different object file, by
		// appending all hexadecimal numbers we want to the same addr2line command.
		if ((last_file == NULL) || (strcmp(last_file, strings[i]) != 0))
		{
			if (last_file != NULL)
			{
				append_to_string(&command, "; ");
			}

			// in case the object file is not found in the given path we look for
			// it by using the 'whereis' command.
			append_to_string(&command, 	"location=\"%s\" ; echo obj \"$location\" ; "
							"if [ ! -f \"$location\" ] ; "
							"then "
								"set -- $(whereis -b \"$location\") ; "
								"location=\"$2\"; "
							"fi ; "
							"addr2line -f -C -e \"$location\"", strings[i]);
			last_file = strings[i];
		}
		
		// append the hexadecimal number to this current addr2line command.
		index_hexa = strchr(&strings[i][index_first_character_after_name]+1, '[') +1;
		index_end_hexa = strchr(index_hexa, ']');
		*index_end_hexa = '\0';
		
		append_to_string(&command, " %s", index_hexa);
	}

	// the end of the shell command. It:
	// - reformat the output
	// - detect if source localisation was found or not (and in this case add a comment)
	// - stops the stack after the function called 'main'.
	append_to_string(&command, "; } 2>/dev/null | {	 "
						"printf \"%%110s\n\" \"\" | tr ' ' '@'; "
						"echo \"One call was done at $(date +%%Hh%%Mmn%%Ss). Process function calls stack was:\"; "
						"echo ;"
						"printf \"%%-70s | %%s\n\" \"Function:\" \"Source file name and line number:\"; "
						"printf \"%%-70s | %%s\n\" \"Function:\" \"Source file name and line number:\" | tr '[:print:]' '-'; "
						"all_code_found=1; "
						"while read word1 word2; "
						"do "
							"if [ \"$word1\" = \"obj\" ] ; "
							"then "
								"current_obj=\"$word2\"; "
							"else "
								"func=\"$word1\"; read loc; "
								"if [ \"$loc\" = \"??:0\" ] ; "
								"then "
									"if [ \"$func\" = \"??\" ] ; "
									"then "
										"printf \"%%-70s | %%s\n\" \"(in $current_obj)\" '*'; "
									"else "
										"printf \"%%-70s | %%s\n\" \"$func\" '*'; "
									"fi; "
									"all_code_found=0; "
								"else "
									"printf \"%%-70s | %%s\n\" \"$func\" \"$loc\"; "
								"fi; "
								"if [ \"$func\" = \"main\" ] ; "
								"then "
									"break; "
								"fi; "
							"fi; "
						"done; "
						"if [ \"$all_code_found\" = \"0\" ]; "
						"then "
							"echo ;"
							"echo '*: code file and line number unavailable (source needs to be compiled with option -g)';"
						"fi; "
						"printf \"%%110s\n\" \"\" | tr ' ' '@'; "
						"interpreted_language=%d; "
						"if [ \"$interpreted_language\" = \"1\" ]; "
						"then "
							"printf \"" WARNING_INTERPRETED_LANGUAGE "\"; "
						"fi; "
						"echo; "
					  "} >> %s/%s", interpreted_language, directory, __PROCESS_STACKS_FILENAME);

	// execute the command
	run_command(command, "create the file called 'process_stacks'");
	free(command);

	free (strings);
}

