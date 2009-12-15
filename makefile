#!/usr/bin/make -f
#
# Copyright (c) Members of the EGEE Collaboration. 2008. 
# See http://www.eu-egee.org/partners/ for details on the copyright
# holders.  
# 
# Licensed under the Apache License, Version 2.0 (the "License"); 
# you may not use this file except in compliance with the License. 
# You may obtain a copy of the License at 
# 
#     http://www.apache.org/licenses/LICENSE-2.0 
# 
# Unless required by applicable law or agreed to in writing, software 
# distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
# See the License for the specific language governing permissions and 
# limitations under the License.
# 
# ---------------------------------------------------------------------
# Developed by Etienne DUBLE - CNRS UREC (http://www.urec.fr)
# etienne __dot__ duble __at__ urec __dot__ cnrs __dot__ fr
# Nov 25, 2008.
# ---------------------------------------------------------------------
# 
# Last modifications: 
# Etienne DUBLE 	-1.0:	Creation
# Etienne DUBLE 	-1.1:	Added dependency to *.h and clean rule
# Etienne DUBLE 	-2.0:	Added binary_package and source_package rules
# Etienne DUBLE 	-2.0:	Added install/uninstall rules
# Etienne DUBLE 	-2.1:	Added README and LICENSE files
# Etienne DUBLE 	-2.3:	Added bash completion
# Etienne DUBLE 	-3.0:	Introduced patching mode - reorganised the source tree - automatic dependencies
# Etienne DUBLE 	-2.5:	Added man page
# 

VERSION=3.0-alpha2

PACKAGE_NAME="ipv6_care-$(VERSION)"
ARCHITECTURE=$(shell uname -m)
OPTIONS=-g -Wall -W

list_objects=$(shell ls src/$(1)/*.c 2>/dev/null | sed -e "s/\.c/\.o/g" | sed -e "s/src/out/g") 

ALL_ANALYSIS_OBJECTS=$(call list_objects,checking)
ALL_PATCHING_OBJECTS=$(call list_objects,patching)
ALL_COMMON_OBJECTS=$(call list_objects,common)

all: out_dir_structure out/libipv6_care_checking.so out/libipv6_care_patching.so

out_dir_structure:
	@mkdir -p out/checking out/patching out/common 

out/%.o: src/%.c 
	gcc $(OPTIONS) -fPIC -MMD -c -Isrc/common -o $@ src/$*.c

out/libipv6_care_checking.so: $(ALL_ANALYSIS_OBJECTS) $(ALL_COMMON_OBJECTS)
	gcc $(OPTIONS) -shared -Wl,-soname,libipv6_care_checking.so -o $@ $^ -ldl

out/libipv6_care_patching.so: $(ALL_PATCHING_OBJECTS) $(ALL_COMMON_OBJECTS)
	gcc $(OPTIONS) -shared -Wl,-soname,libipv6_care_patching.so -o $@ $^ -ldl

clean:
	rm -rf out 

install:
	@cp -f scripts/ipv6_care /usr/bin/
	@cp -f scripts/IPv6_CARE_*.sh /usr/bin/
	@cp -f out/libipv6_care_checking.so /usr/lib/
	@cp -f out/libipv6_care_patching.so /usr/lib/
	@cp -f man/ipv6_care.8.gz /usr/share/man/man8/
	@if [ -d /etc/bash_completion.d ] ; \
	 then 	cp scripts/complete.sh /etc/bash_completion.d/ipv6_care ; \
	 	echo "bash completion will only be updated when you start a new bash session." ; \
	 fi
	@echo "install done."

uninstall:
	rm -f /usr/bin/ipv6_care
	rm -f /usr/bin/IPv6_CARE_*.sh
	rm -f /usr/lib/libipv6_care_checking.so
	rm -f /usr/lib/libipv6_care_patching.so
	rm -f /usr/share/man/man8/ipv6_care.8.gz
	rm -f /etc/bash_completion.d/ipv6_care

define package_creation
	rm -rf $@ /tmp/$*
	for file in $^ ; 	\
	do 			\
		mkdir -p $$(dirname /tmp/$*/$$file)	; \
		cp $$file /tmp/$*/$$file		; \
	done
	cd /tmp ; tar cfz $@ $* ; cd - >/dev/null
	rm -rf /tmp/$*
	echo $@ was created.
endef

binary_package: /tmp/$(PACKAGE_NAME)-bin-$(ARCHITECTURE).tar.gz

/tmp/%-$(ARCHITECTURE).tar.gz: out/libipv6_care_checking.so out/libipv6_care_patching.so scripts/ipv6_care scripts/IPv6_CARE_*.sh makefile scripts/complete.sh README LICENSE
	@$(package_creation)

source_package: /tmp/$(PACKAGE_NAME)-src.tar.gz

/tmp/%.tar.gz: src/*/*.c src/*/*.h scripts/ipv6_care scripts/IPv6_CARE_*.sh makefile scripts/complete.sh README LICENSE
	@$(package_creation)

-include out/*/*.d

