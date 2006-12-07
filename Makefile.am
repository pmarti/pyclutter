SUBDIRS = clutter examples 

if HAVE_CLUTTER_GTK
SUBDIRS += clutter-gtk
endif

if HAVE_CLUTTER_GST
SUBDIRS += clutter-gst
endif

if ENABLE_DOC
SUBDIRS += docs
endif

DIST_SUBDIRS = docs clutter clutter-gtk clutter-gst examples
EXTRA_DIST = createdefs.py py-compile

# Extra clean files so that maintainer-clean removes *everything*
MAINTAINERCLEANFILES = aclocal.m4 compile config.guess config.sub \
                       configure depcomp install-sh ltmain.sh     \
                       Makefile.in missing config.h.in
