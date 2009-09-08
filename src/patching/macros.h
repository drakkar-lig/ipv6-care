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
Etienne DUBLE 	- 3.0: 	Creation

*/
#ifndef __MACROS_H__
#define __MACROS_H__

#include "common_other_tools.h"
#include "common_macros.h"

#define RESULT_PTR(x)	x

/*
 * Please first look at the file overwritten_function.c to understand 
 * how __CALL_ORIGINAL_FUNCTION is used. 
 * 
 * __CALL_ORIGINAL_FUNCTION calls the original function (of the standard libc).
 */

#define stringified(x) #x

#define __CALL_ORIGINAL_FUNCTION(__func_name, 					\
		__func_args, __func_return_value_if_error, __result_ptr)	\
										\
	typeof(__func_name) *p_original_func;					\
										\
	p_original_func = (typeof(p_original_func))				\
		get_symbol((char *) stringified(__func_name)); 			\
	if (p_original_func != NULL) 						\
	{									\
		*__result_ptr = p_original_func __func_args;			\
	}									\
	else 									\
	{									\
		*__result_ptr = __func_return_value_if_error;			\
	}

#endif
