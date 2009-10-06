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
Etienne DUBLE 	- 1.0: 	Creation
Etienne DUBLE 	- 1.1: 	Did the original call first in order to get the result
			available for the analysis
Etienne DUBLE 	- 2.2:	Reworked init_lib mechanism and implementation
Etienne DUBLE 	- 2.3:	Corrected the comment
Etienne DUBLE   - 2.4:  Thread management

*/
#ifndef __MACROS_H__
#define __MACROS_H__

#include "init_lib.h"
#include "log.h"
#include "common_other_tools.h"
#include "function_state.h"
#include "common_macros.h"

extern int max_function_depth_reported;

extern __thread int function_depth;
extern __thread int function_analysis_started;

/*
 * Please first look at the file overwritten_function.c to understand 
 * how __START_FUNCTION_CALL_ANALYSIS and __END_FUNCTION_CALL_ANALYSIS
 * are used. 
 * 
 * The main goal of the __START_FUNCTION_CALL_ANALYSIS macro is to chain
 * the original function (of the standard libc) to the current function 
 * (the one we are writting to perform the function call analysis).
 * The function_analysis_started variable is used to avoid a recursive 
 * analysis of another function B which would be called during the analysis 
 * phase of a function A. In this case the analysis of the inner function B 
 * is bypassed (consequently the original B function of the libc is called
 * directly).
 * __START_FUNCTION_CALL_ANALYSIS also initialise the logging process of this
 * function.
 * 
 * __END_FUNCTION_CALL_ANALYSIS ends the logging process of this function,
 * reset the function_analysis_started variable to 0, and returns some value
 * (this return value is actually not used due to the implementation of 
 * __START_FUNCTION_CALL_ANALYSIS, but it is required by the compiler.)
 */

#define __START_FUNCTION_CALL_ANALYSIS(__func_name, 				\
		__func_args, __func_return_value_if_error)			\
										\
	static enum function_state __state__ = initial_state;			\
	typeof(__func_name) *p_original_func;					\
	typeof(__func_name __func_args) __result__;				\
										\
	one_time_library_init(&__state__);					\
										\
	switch(__state__)							\
	{									\
		case initial_state:						\
			if ((function_analysis_started == 0) &&			\
			    (function_depth <= max_function_depth_reported)) {	\
				__state__ = analysis_state;			\
				__func_name __func_args;			\
			}							\
			__state__ = call_original_function_state; 		\
			return __func_name __func_args;                 	\
										\
		case call_original_function_state:				\
			p_original_func = (typeof(p_original_func))		\
				get_symbol((char *)__FUNCTION__); 		\
			if (p_original_func != NULL) 				\
			{							\
				function_depth += 1; 				\
				__result__ = p_original_func __func_args;	\
				function_depth -= 1;				\
				__state__ = initial_state;			\
				return __result__;				\
			}							\
			else 							\
			{							\
				__state__ = initial_state;			\
				return __func_return_value_if_error;		\
			}							\
										\
		case analysis_state:						\
			if (function_analysis_started == 1) {			\
				__state__ = call_original_function_state;	\
				return __func_name __func_args;			\
			}							\
			break;							\
	}									\
										\
	function_analysis_started = 1;						\
	register_info_start((char *)__FUNCTION__); 

#define __END_FUNCTION_CALL_ANALYSIS						\
	register_info_end(); 							\
	function_analysis_started = 0;						\
	return (typeof(__result__))0;
	
#define __START_FUNCTION_CALL_RETURNING_VOID_ANALYSIS(__func_name, 		\
		__func_args)							\
										\
	static enum function_state __state__ = initial_state;			\
	typeof(__func_name) *p_original_func;					\
										\
	one_time_library_init(&__state__);					\
										\
	switch(__state__)							\
	{									\
		case initial_state:						\
			if ((function_analysis_started == 0) &&			\
			    (function_depth <= max_function_depth_reported)) {	\
				__state__ = analysis_state;			\
				__func_name __func_args;			\
			}							\
			__state__ = call_original_function_state; 		\
			__func_name __func_args;                 		\
			return;							\
										\
		case call_original_function_state:				\
			p_original_func = (typeof(p_original_func))		\
				get_symbol((char *)__FUNCTION__); 		\
			if (p_original_func != NULL) 				\
			{							\
				function_depth += 1; 				\
				p_original_func __func_args;			\
				function_depth -= 1;				\
				__state__ = initial_state;			\
				return;						\
			}							\
			else 							\
			{							\
				__state__ = initial_state;			\
				return;						\
			}							\
										\
		case analysis_state:						\
			if (function_analysis_started == 1) {			\
				__state__ = call_original_function_state;	\
				__func_name __func_args;			\
				return;						\
			}							\
			break;							\
	}									\
										\
	function_analysis_started = 1;						\
	register_info_start((char *)__FUNCTION__); 

#define __END_FUNCTION_CALL_RETURNING_VOID_ANALYSIS				\
	register_info_end(); 							\
	function_analysis_started = 0;						\
	return;
	
#define __REGISTER_INFO_INT(name, value) 		register_info_int(name, value)
#define __REGISTER_INFO_CHARS(name, value) 		register_info_chars(name, (char *)value)
#endif
