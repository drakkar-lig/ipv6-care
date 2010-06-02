include $(srcdir)/Makefile.src_info
include $(top_srcdir)/Makefile.flags
lib_LTLIBRARIES = libipv6_care_patching.la
libipv6_care_patching_la_LIBADD = ../common/libipv6_care_common.la
libipv6_care_patching_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/common \
			-DIPV4_POOL_START=$(IPV4_POOL_START) -DIPV4_POOL_END=$(IPV4_POOL_END)

