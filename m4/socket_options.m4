# AX_CHECK_SOCKET_OPTIONS()
# -----------------------------------------------
# Checks existence of some specific socket options
AC_DEFUN([AX_CHECK_SOCKET_OPTIONS],
[
AC_CACHE_CHECK([whether SO_BINDTODEVICE exists],
                [ax_cv_SO_BINDTODEVICE],
[AC_TRY_COMPILE([ 
#include <sys/socket.h>
], [ return SO_BINDTODEVICE; ], [ax_cv_SO_BINDTODEVICE=yes], [ax_cv_SO_BINDTODEVICE=no])]
)
if test x"$ax_cv_SO_BINDTODEVICE" = xyes; then
  AC_DEFINE([HAVE_SO_BINDTODEVICE], 1,
            [Define whether SO_BINDTODEVICE exists.])
fi

AC_CACHE_CHECK([whether SO_PRIORITY exists],
                [ax_cv_SO_PRIORITY],
[AC_TRY_COMPILE([ 
#include <sys/socket.h>
], [ return SO_PRIORITY; ], [ax_cv_SO_PRIORITY=yes], [ax_cv_SO_PRIORITY=no])]
)
if test x"$ax_cv_SO_PRIORITY" = xyes; then
  AC_DEFINE([HAVE_SO_PRIORITY], 1,
            [Define whether SO_PRIORITY exists.])
fi

])

