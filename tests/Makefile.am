
SUBDIRS=

check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = googletest/googletest/src/gtest-all.cc googletest/googlemock/src/gmock-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/tests/googletest/googletest/include -I$(top_srcdir)/tests/googletest/googletest -I$(top_srcdir)/tests/googletest/googlemock -I$(top_srcdir)/tests/googletest/googlemock/include
libgtest_la_LDFLAGS = -pthread

noinst_PROGRAMS=frontier_test

frontier_test_SOURCES=main.cpp testCommon.cpp testFrontierApp.cpp testFontManager.cpp
frontier_test_LDADD=../src/libfrontier/libfrontier.la libgtest.la
frontier_test_LDFLAGS=-framework Cocoa -framework AppKit -fsanitize=address
frontier_test_CPPFLAGS=-I${top_srcdir}/include -I${top_srcdir}/src/libfrontier -I$(top_srcdir)/tests//googletest/googletest/include

test: all
	cd ..; tests/frontier_test

