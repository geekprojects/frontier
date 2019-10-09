
noinst_PROGRAMS=demo

demo_SOURCES=main.cpp
demo_LDADD=../libfrontier/libfrontier.la
demo_LDFLAGS=-framework Cocoa -framework AppKit -fsanitize=address
demo_CPPFLAGS=-I${top_srcdir}/include

app:
	rm -rf Demo.app
	mkdir -p Demo.app/Contents
	mkdir -p Demo.app/Contents/MacOS
	mkdir -p Demo.app/Contents/Frameworks
	mkdir -p Demo.app/Contents/Resources
	cp .libs/demo Demo.app/Contents/MacOS
	echo "APPL????" > Demo.app/Contents/PkgInfo
	cp osx/Info.plist Demo.app/Contents
	bash osx/relocate.sh Demo.app/Contents/MacOS/Demo Demo.app

