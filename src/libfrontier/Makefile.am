
SUBDIRS=widgets fonts engines

lib_LTLIBRARIES=libfrontier.la

libfrontier_la_SOURCES=app.cpp window.cpp theme.cpp engine.cpp menu.cpp utils.cpp contextmenu.cpp object.cpp
libfrontier_la_LIBADD=widgets/libwidgets.la fonts/libfonts.la engines/libengines.la
libfrontier_la_CPPFLAGS=-I${top_srcdir}/include -DFONTSDIR=${pkgdatadir}/fonts
libfrontier_la_LDFLAGS=-lutil

