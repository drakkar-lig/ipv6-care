# AX_CHECK_GETNAMEINFO_PROTOTYPE()
# -----------------------------------------------
# Check what is the form of the prototype of getnameinfo()
AC_DEFUN([AX_CHECK_GETNAMEINFO_PROTOTYPE],
[
AC_CACHE_CHECK([whether getnameinfo has a linux-like prototype],
                [ax_cv_linux_getnameinfo],
[AC_TRY_COMPILE([
#include <sys/socket.h>
#include <netdb.h>

int getnameinfo(const struct sockaddr *sa, socklen_t salen,
              char *node, socklen_t nodelen, char *service,
              socklen_t servicelen, unsigned int flags)
{
        return 0;
}
], [], [ax_cv_linux_getnameinfo=yes], [ax_cv_linux_getnameinfo=no])]
)
if test x"$ax_cv_linux_getnameinfo" = xyes; then
  AC_DEFINE([HAVE_LINUX_LIKE_GETNAMEINFO], 1,
            [Define if getnameinfo has a linux-like prototype.])
  AC_DEFINE([GETNAMEINFO_PROTOTYPE], [int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, socklen_t nodelen, char *service, socklen_t servicelen, unsigned int flags)],
            [Record the prototype of getnameinfo().])
fi

AC_CACHE_CHECK([whether getnameinfo has a freebsd-like prototype],
                [ax_cv_freebsd_getnameinfo],
[AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, size_t nodelen, char *service, size_t servicelen, int flags)
{
	return 0;
}
], [], [ax_cv_freebsd_getnameinfo=yes], [ax_cv_freebsd_getnameinfo=no])]
)
if test x"$ax_cv_freebsd_getnameinfo" = xyes; then
  AC_DEFINE([HAVE_FREEBSD_LIKE_GETNAMEINFO], 1,
            [Define if getnameinfo has a freebsd-like prototype.])
  AC_DEFINE([GETNAMEINFO_PROTOTYPE], [int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, size_t nodelen, char *service, size_t servicelen, int flags)],
            [Record the prototype of getnameinfo().])
fi

])

