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
June 29, 2009.
---------------------------------------------------------------------

Last modifications: 
Etienne DUBLE 	-3.0:	Creation

*/
#include "overwritten_functions.h"
#include "common_original_functions.h"
#include "hook_status.h"

// global variables
#define HOOK(func, proto, params) 						\
	typeof(overwritten_ ## func) *func ## _hook[2] = { 			\
		&original_ ## func,						\
		&overwritten_ ## func };
#include "list_of_hooks.h"
#undef HOOK

// per-thread variables
__thread enum hook_status hooks_status = hook_status_enabled;
