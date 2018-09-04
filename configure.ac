
AC_PREREQ(2.61)
AC_INIT([libfrontier], [0.1], [ian@geekprojects.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([include/frontier/frontier.h])
AC_CONFIG_HEADER([include/config.h])

AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB
PKG_PROG_PKG_CONFIG

# XXX If MacOS
AC_PROG_OBJCXX

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h])

PKG_CHECK_MODULES(libgeek, libgeek >= 1)
CPPFLAGS="$CPPFLAGS $libgeek_CFLAGS"
LIBS="$LIBS $libgeek_LIBS"

PKG_CHECK_MODULES(Freetype, freetype2 >= 18)
CPPFLAGS="$CPPFLAGS $Freetype_CFLAGS"
LIBS="$LIBS $Freetype_LIBS"

PKG_CHECK_MODULES(SDL, sdl2 >= 2.0)
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

PKG_CHECK_MODULES(SIGCPLUSPLUS, sigc++-2.0 >= 2.10)
CPPFLAGS="$CPPFLAGS $SIGCPLUSPLUS_CFLAGS"
LIBS="$LIBS $SIGCPLUSPLUS_LIBS"

CPPFLAGS="$CPPFLAGS -Wall -Werror"

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT8_T
AC_TYPE_UINT8_T
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT64_T
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([memset strdup gettimeofday sqrt])
AC_FUNC_MALLOC
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libfrontier/Makefile
                 src/libfrontier/widgets/Makefile
                 src/libfrontier/fonts/Makefile
                 src/libfrontier/engines/Makefile
                 src/libfrontier/engines/sdl/Makefile
                 src/libfrontier/engines/cocoa/Makefile
                 src/demo/Makefile
                 include/Makefile
                 include/frontier/Makefile
                 libfrontier.pc
])

AC_OUTPUT

