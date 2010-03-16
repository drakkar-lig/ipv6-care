# when compiling the subdirectory 'binaries' we may have a warning message saying that 
# linking to a shared library is not portable. In our case the handling of 
# shared libraries is a prerequisite, so we can safely ignore this warning.
# To make it clear for the one who compiles the package, we removed 'binaries' from
# the SUBDIRS variable, and compile it manually (see 'check' below), disabling
# error output in order to hide this warning.
SUBDIRS = libs

check:
	@cd binaries; $(MAKE) check 2>&1 >/dev/null; cd ..
	@. libs/libpreload.la;								\
	if LD_PRELOAD=libs/.libs/$$dlname binaries/test_preload > /dev/null 2>&1; 	\
	then									  	\
		echo "LD_PRELOAD mechanism ok";						\
	else										\
		make ld_preload_error;    						\
	fi

ld_preload_error:
	$(error "OS does not implement the LD_PRELOAD mechanism.")
