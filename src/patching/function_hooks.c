/*
Copyright (c) Centre National de la Recherche Scientifique (CNRS,
France). 2010. 
Copyright (c) Members of the EGEE Collaboration. 2008-2010. See 
http://www.eu-egee.org/partners/ for details on the copyright
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
Developed by Etienne DUBLE - CNRS LIG (http://www.liglab.fr)
etienne __dot__ duble __at__ imag __dot__ fr
---------------------------------------------------------------------
*/
//#include <stdio.h>


#include "common_macros.h"
#include "manage_hooks.h"
#include "hooks.h"

#define HOOK(name, prototype, parameters)					\
PUBLIC_FUNCTION prototype							\
{										\
	typeof((* name ## _hook[0])parameters) __result;			\
										\
	if (hooks_status == hook_status_enabled)				\
	{									\
		disable_all_hooks();						\
		/*printf("Function %s detected.\n", stringified(name));*/	\
		__result = (* name ## _hook[hook_status_enabled])parameters;	\
		/*printf("Function %s done.\n", stringified(name));*/		\
		enable_all_hooks();						\
	}									\
	else									\
	{									\
		/*printf("Function %s CALLED DIRECTLY.\n", stringified(name));*/\
		__result = (* name ## _hook[hook_status_disabled])parameters;	\
	}									\
	return __result;							\
}

#include "list_of_hooks.h"

#undef HOOK
