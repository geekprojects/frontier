noinst_LTLIBRARIES=libcocoa.la libcocoa_objc.la

libcocoa_la_SOURCES=engine.cpp window.cpp
libcocoa_la_CPPFLAGS=-I${top_srcdir}/include -Wno-deprecated-declarations
libcocoa_la_LIBADD=libcocoa_objc.la


libcocoa_objc_la_SOURCES=CocoaWindow.mm CocoaEngine.mm utils.mm
libcocoa_objc_la_CPPFLAGS=-I${top_srcdir}/include -Wno-deprecated-declarations
libcocoa_objc_la_LIBTOOLFLAGS=--tag=CXX

