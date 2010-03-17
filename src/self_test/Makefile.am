# when compiling the subdirectory 'binaries' we may have a warning message saying that 
# linking to a shared library is not portable. In our case the handling of 
# shared libraries is a prerequisite, so we can safely ignore this warning.
SUBDIRS = libs binaries

check:
	@. libs/libpreload.la;								\
	if LD_PRELOAD=libs/.libs/$$dlname binaries/test_preload > /dev/null 2>&1; 	\
	then									  	\
		echo "LD_PRELOAD mechanism ok";						\
	else										\
		make ld_preload_error;    						\
	fi

ld_preload_error:
	$(error "OS does not implement the LD_PRELOAD mechanism.")
