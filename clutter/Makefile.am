AUTOMAKE_OPTIONS = 1.7

CLEANFILES =

CLUTTER_DEFS = clutter.defs
CLUTTER_OVERRIDES = clutter.override

EXTRA_DIST =		\
	clutter.defs	\
	clutter.override

clutter-pyglue.c: clutter.defs $(CLUTTER_OVERRIDES)
	$(PYGTK_CODEGEN)				\
        --register $(PYGTK_DEFSDIR)/gdk-types.defs	\
        --register $(PYGTK_DEFSDIR)/gtk-types.defs	\
        --register $(PYGTK_DEFSDIR)/pango-types.defs	\
	--override $(top_srcdir)/clutter/$(CLUTTER_OVERRIDES)	\
	--prefix clutter				\
        clutter.defs > gen-$@ &&			\
	(cmp -s $@ gen-$@ || cp gen-$@ $@) &&		\
	rm -f gen-$@

pkgpythondir = $(pyexecdir)
pyclutterdir = $(pkgpythondir)/clutter
pyclutter_LTLIBRARIES = _clutter.la
pyclutter_PYTHON = __init__.py

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pyclutter.pc

EXTRA_DIST += pyclutter.pc.in

INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS) $(CLUTTER_CFLAGS)

_clutter_la_SOURCES = cluttermodule.c
_clutter_la_LIBADD  = $(PYGTK_LIBS) $(CLUTTER_LIBS)
_clutter_la_LDFLAGS = -module -avoid-version -export-symbols-regex init_clutter
nodist__clutter_la_SOURCES = clutter-pyglue.c
CLEANFILES += clutter-pyglue.c
