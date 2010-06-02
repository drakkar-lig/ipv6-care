# AX_CHECK_SYS_GETTID()
# -----------------------------------------------
# Defines HAVE_SYS_GETTID if syscall SYS_gettid exists
AC_DEFUN([AX_CHECK_SYS_GETTID],
[AC_CACHE_CHECK([whether syscall SYS_gettid exists],
                [ax_cv_sys_gettid_exists],
[AC_TRY_COMPILE([
#include <sys/syscall.h>
#include <unistd.h>
], [syscall(SYS_gettid);], [ax_cv_sys_gettid_exists=yes], [ax_cv_sys_gettid_exists=no])]
)
if test x"$ax_cv_sys_gettid_exists" = xyes; then
  AC_DEFINE([HAVE_SYS_GETTID], 1,
            [Define if syscall SYS_gettid exists.])
fi])

