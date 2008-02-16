SUBDIRS = clutter examples 

if BUILD_CLUTTERGST
SUBDIRS += clutter-gst
endif

if BUILD_CLUTTERGTK
SUBDIRS += clutter-gtk
endif

if BUILD_CLUTTERCAIRO
SUBDIRS += clutter-cairo
endif

if BUILD_TIDY
SUBDIRS += tidy
endif

if ENABLE_DOCS
SUBDIRS += docs
endif

pyclutter-$(PYCLUTTER_MAJOR_VERSION).$(PYCLUTTER_MINOR_VERSION).pc: pyclutter.pc
	@cp -f $< $(@F)

pkgfiles = pyclutter-$(PYCLUTTER_MAJOR_VERSION).$(PYCLUTTER_MINOR_VERSION).pc
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pkgfiles)

DIST_SUBDIRS = \
	docs \
	clutter \
	examples \
	clutter-gst \
	clutter-gtk \
	clutter-cairo \
	tidy

EXTRA_DIST = createdefs.py py-compile

CLEANFILES = $(pkgfiles)

# Extra clean files so that maintainer-clean removes *everything*
MAINTAINERCLEANFILES = \
	aclocal.m4 \
	compile \
	config.guess \
	config.sub \
        configure \
	depcomp \
	install-sh \
	ltmain.sh \
	Makefile.in \
	missing \
	config.h.in

