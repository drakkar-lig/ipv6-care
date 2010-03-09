SUBDIRS = src/common src/checking src/patching man scripts

EXTRA_DIST = LICENSE README

ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = $(CFLAG_VISIBILITY) -Werror
AM_CPPFLAGS = -D_GNU_SOURCE -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 -imacros config.h
AM_LDFLAGS = -avoid-version -shared
MAKEFLAGS = --no-print-directory
export AM_CFLAGS AM_CPPFLAGS AM_LDFLAGS


