AC_INIT([ipv6_care],[3.1],[ipv6-care-support@urec.cnrs.fr])
AC_CONFIG_SRCDIR([src/checking/log.c])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC
AC_PROG_SED
AC_PROG_MAKE_SET
AC_CHECK_PROGS([ADDR2LINE], [addr2line], [:])
if test "$ADDR2LINE" = :; then
	AC_MSG_ERROR([This package needs addr2line (usually found in package binutils).])
fi

AC_DISABLE_STATIC
LT_INIT
gl_VISIBILITY
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])

dnl Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h sys/time.h unistd.h execinfo.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([ppoll dup2 gethostbyaddr gethostbyname inet_ntoa localtime_r memset mkdir select setenv socket strchr strcspn strerror strstr])

dnl Check for particular features
AX_CHECK_SYS_GETTID
AX_CHECK_GETNAMEINFO_PROTOTYPE
AX_CHECK_GETADDRINFO_CONSTANTS
AX_CHECK_SOCKET_OPTIONS

dnl Install bash-completion file?
dnl see http://www.google.com/codesearch/p?hl=fr#7JifyE86fvY/configure.ac&q=file:gvfs-bash-completion.sh&d=0
AC_ARG_ENABLE([bash-completion],
	AC_HELP_STRING([--enable-bash-completion], [build with bash-completion support]),
	msg_bash_completion=$enableval,
	msg_bash_completion=no)

if test "x$enable_bash_completion" != "xyes"; then
	msg_bash_completion=no
fi
AM_CONDITIONAL(ENABLE_BASHCOMP, test "$msg_bash_completion" = "yes")

AC_ARG_WITH([bash-completion-dir],
	AC_HELP_STRING([--with-bash-completion-dir=PATH],
		[choose directory for bash-completion file (default=SYSCONFDIR/bash_completion.d)]),
	with_bashcomp_dir=$withval,
	with_bashcomp_dir=$sysconfdir/bash_completion.d)
BASHCOMP_DIR=$with_bashcomp_dir
AC_SUBST(BASHCOMP_DIR)

dnl Pool of unused IPv4 addresses
AC_ARG_WITH([ipv4-pool],
	AC_HELP_STRING([--with-ipv4-pool=<start>-<end>],
		[specify the pool of private IPv4 addresses that IPv6 CARE should use (default=10.133.0.0-10.133.255.255). CAUTION: These addresses MUST NOT be used in your network!]),
	with_ipv4_pool=$withval,
	with_ipv4_pool=10.133.0.0-10.133.255.255)
IPV4_POOL_START=`echo $with_ipv4_pool | sed -e 's/-.*$//'`
AC_SUBST(IPV4_POOL_START)
IPV4_POOL_END=`echo $with_ipv4_pool | sed -e 's/^.*-//'`
AC_SUBST(IPV4_POOL_END)

AC_CONFIG_FILES([Makefile src/common/Makefile src/checking/Makefile \
		src/patching/Makefile scripts/ipv6_care:scripts/ipv6_care.in man/Makefile \
		scripts/Makefile src/self_test/Makefile src/self_test/libs/Makefile src/self_test/binaries/Makefile ])
AC_OUTPUT

