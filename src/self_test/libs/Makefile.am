# building to customdir allows to build libraries as shared libraries
# even if they are temporary ones... (otherwise libtool builds only static ones)
customdir = $(PWD)
custom_LTLIBRARIES = libpreload.la libstd.la
libstd_la_SOURCES = std.c
libstd_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/common
libpreload_la_SOURCES = preloaded.c
libpreload_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/common
