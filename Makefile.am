
COPYRIGHT_LICENSE ?= LGPL3
COPYRIGHT_HOLDER ?= Ian Parker <ian@geekprojects.com>
COPYRIGHT_YEAR ?= 2018
COPYRIGHT_SOFTWARE ?= Frontier
COPYRIGHT_SOFTWARE_DESCRIPTION ?= A toolkit for creating simple OS-independent user interfaces
COPYRIGHT_OUTPUT_DIR ?= output
COPYRIGHT_WORD_WRAP ?= 100
COPYRIGHT_PATHS ?= src:include

SUBDIRS=src include data

if BUILD_TESTS
SUBDIRS+=tests
endif

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=libfrontier.pc

test:
	cd tests; $(MAKE) test

add-copyright:
	copyright-header \
	  --license $(COPYRIGHT_LICENSE)  \
	  --add-path $(COPYRIGHT_PATHS) \
	  --guess-extension \
	  --copyright-holder '$(COPYRIGHT_HOLDER)' \
	  --copyright-software '$(COPYRIGHT_SOFTWARE)' \
	  --copyright-software-description '$(COPYRIGHT_SOFTWARE_DESCRIPTION)' \
	  --copyright-year $(COPYRIGHT_YEAR) \
	  --word-wrap $(COPYRIGHT_WORD_WRAP) \
	  --output-dir $(COPYRIGHT_OUTPUT_DIR) \
	  --syntax tools/syntax.yml

