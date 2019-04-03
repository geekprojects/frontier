
SUBDIRS=test embedded
if FRONTIER_ENGINE_SDL
SUBDIRS+=sdl
endif

if FRONTIER_ENGINE_COCOA
SUBDIRS+=cocoa
endif

noinst_LTLIBRARIES=libengines.la

libengines_la_SOURCES=
libengines_la_CPPFLAGS=-I${top_srcdir}/include

libengines_la_LIBADD=test/libtest.la embedded/libembedded.la
if FRONTIER_ENGINE_SDL
libengines_la_LIBADD+=sdl/libsdl.la
endif

if FRONTIER_ENGINE_COCOA
libengines_la_LIBADD+=cocoa/libcocoa.la
endif

