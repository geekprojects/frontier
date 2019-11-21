AC_PREREQ(2.61)
AC_INIT([libfrontier], [0.1], [ian@geekprojects.com])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([include/frontier/frontier.h])
AC_CONFIG_HEADER([include/frontier/config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
AC_LANG([C++])
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

AC_ARG_ENABLE(opengl,
        [  --enable-opengl          Enable OpenGL library ],
        [enable_opengl="yes" ],
        [enable_opengl="no"])

i
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h])

CPPFLAGS="$CPPFLAGS -std=c++11"

AX_CXX_CHECK_LIB(antlr4-runtime, [antlr4::RuntimeMetaData::getRuntimeVersion()], [
    has_libantlr4=yes
    LIBS="$LIBS -lantlr4-runtime"
    CPPFLAGS="$CPPFLAGS -I/usr/local/include/antlr4-runtime -I/usr/include/antlr4-runtime"
])

if test "$has_libantlr4" != "yes"
then
    AC_MSG_ERROR([Antlr4 C++ runtime is required])
fi


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

if test "$enable_opengl" != "no"
then
    AC_MSG_NOTICE([Building OpenGL library])
    AC_DEFINE(FRONTIER_OPENGL, 1, [OpenGL Library])
fi
AM_CONDITIONAL([FRONTIER_OPENGL], test "$enable_opengl" = "yes")


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

AC_ARG_ENABLE(tests,
        [  --enable-tests            Enable Unit Tests ],
        [enable_tests="yes"],
        [enable_tests="no"])
if test "x$enable_tests" != "xno"
then
    AC_DEFINE(BUILD_TESTS, true, [tests])
    AM_CONDITIONAL([BUILD_TESTS], true, [tests])
else
    AC_DEFINE(BUILD_TESTS, false, [tests])
    AM_CONDITIONAL([BUILD_TESTS], false, [tests])
fi

CPPFLAGS="$CPPFLAGS -g -O0 -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer"
LDFLAGSS="$LDFLAGS -fsanitize=address"

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libfrontier/Makefile
                 src/libfrontier/widgets/Makefile
                 src/libfrontier/widgets/list/Makefile
                 src/libfrontier/windows/Makefile
                 src/libfrontier/engines/Makefile
                 src/libfrontier/engines/test/Makefile
                 src/libfrontier/engines/embedded/Makefile
                 src/libfrontier/engines/sdl/Makefile
                 src/libfrontier/engines/cocoa/Makefile
                 src/libfrontier/styles/Makefile
                 src/libfrontier-opengl/Makefile
                 src/demo/Makefile
                 data/Makefile
                 data/fonts/Makefile
                 tests/Makefile
                 include/Makefile
                 include/frontier/Makefile
                 include/frontier/widgets/Makefile
                 include/frontier/windows/Makefile
                 libfrontier.pc
])

AC_OUTPUT

