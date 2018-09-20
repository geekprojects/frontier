
AC_PREREQ(2.61)
AC_INIT([libfrontier], [0.1], [ian@geekprojects.com])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([include/frontier/frontier.h])
AC_CONFIG_HEADER([include/frontier/config.h])

AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB
AC_PROG_OBJCXX
PKG_PROG_PKG_CONFIG

case $target_os in
     *linux*)   arch=linux;;
     *netbsd*)  arch=netbsd;;
     *bsd*)     arch=bsd;;
     *darwin*)  arch=darwin;;
     *)         arch=unknown;;
esac

engine_enabled="no"
AC_ARG_ENABLE(sdl,
        [  --enable-sdl            Enable SDL Engine ],
        [enable_sdl="yes"
         engine_enabled="yes"],
        [enable_sdl="no"])
AC_ARG_ENABLE(cocoa,
        [  --enable-cocoa          Enable Cocoa Engine ],
        [enable_cocoa="yes"
         engine_enabled="yes"],
        [enable_cocoa="no"])

if test "$enable_sdl" != "no" -a "$enable_cocoa" != "no"
then
    AC_MSG_ERROR([You can only enable one engine])
fi

# If no engine specified then work out a default
if test "$engine_enabled" = "no"
then
    if test "$arch" = darwin
    then
        enable_cocoa="yes"
    else
        enable_sdl="yes"
    fi
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h])

PKG_CHECK_MODULES(libgeek, libgeek >= 1)
CPPFLAGS="$CPPFLAGS $libgeek_CFLAGS"
LIBS="$LIBS $libgeek_LIBS"

PKG_CHECK_MODULES(Freetype, freetype2 >= 17)
CPPFLAGS="$CPPFLAGS $Freetype_CFLAGS"
LIBS="$LIBS $Freetype_LIBS"

PKG_CHECK_MODULES(SIGCPLUSPLUS, sigc++-2.0 >= 2.2)
CPPFLAGS="$CPPFLAGS $SIGCPLUSPLUS_CFLAGS"
LIBS="$LIBS $SIGCPLUSPLUS_LIBS"

if test "$enable_cocoa" != "no"
then
    AC_MSG_NOTICE([Using Cocoa Engine])
    AC_DEFINE(FRONTIER_ENGINE_COCOA, 1, [Cocoa Engine])
    LIBS="$LIBS -framework AppKit"
fi

if test "$enable_sdl" != "no"
then
    AC_MSG_NOTICE([Using SDL Engine])
    PKG_CHECK_MODULES(SDL, sdl2 >= 2.0)
    CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
    LIBS="$LIBS $SDL_LIBS"
    AC_DEFINE(FRONTIER_ENGINE_SDL, 1, [SDL Engine])
fi

AM_CONDITIONAL([FRONTIER_ENGINE_COCOA], test "$enable_cocoa" = "yes")
AM_CONDITIONAL([FRONTIER_ENGINE_SDL], test "$enable_sdl" = "yes")

CPPFLAGS="$CPPFLAGS -Wall -Werror -Werror=sign-compare"

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

