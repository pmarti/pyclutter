AUTOMAKE_OPTIONS = 1.7

PLATFORM_VERSION = 1.0

CLEANFILES =
EXTRA_DIST = 
INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

CREATEDEFS = $(PYTHON) $(top_srcdir)/createdefs.py

# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

# clutter python scripts
pyclutterdir = $(pkgpythondir)/clutter
pyclutter_PYTHON = __init__.py keysyms.py

# clutter headers
pkgincludedir = $(includedir)/pyclutter-$(PLATFORM_VERSION)/pyclutter
pkginclude_HEADERS = pyclutter.h

# linker flags
common_ldflags = -module -avoid-version

# clutter module
CLUTTER_DEFS = clutter-base.defs
CLUTTER_TYPES_DEFS = clutter-base-types.defs
CLUTTER_OVERRIDES = 			\
	clutter.override		\
	clutter-actor.override 		\
	clutter-behaviour.override	\
	clutter-boxed.override 		\
	clutter-color.override		\
	clutter-event.override		\
	clutter-model.override		\
	clutter-script.override

EXTRA_DIST += 			\
	$(CLUTTER_DEFS) 	\
	$(CLUTTER_TYPES_DEFS)	\
	$(CLUTTER_OVERRIDES)

clutter.defs: $(CLUTTER_DEFS)
	$(CREATEDEFS) $@ $(CLUTTER_DEFS)

clutter-types.defs: $(CLUTTER_TYPES_DEFS)
	$(CREATEDEFS) $@ $(CLUTTER_TYPES_DEFS)

CLEANFILES += clutter.defs clutter-types.defs

clutter.c: clutter-types.defs clutter.defs $(CLUTTER_OVERRIDES)
_clutter_la_CFLAGS = $(CLUTTER_CFLAGS)
_clutter_la_LDFLAGS = $(common_ldflags) -export-symbols-regex init_clutter
_clutter_la_LIBADD = $(PYGTK_LIBS) $(CLUTTER_LIBS)
_clutter_la_SOURCES = 		\
	pyclutter.c		\
	cluttermodule.c 
nodist__clutter_la_SOURCES = clutter.c

CLEANFILES += clutter.c

pyclutterexec_LTLIBRARIES = _clutter.la

# defs files
defsdir = $(pkgdatadir)/$(PLATFORM_VERSION)/defs
defs_DATA = \
	$(CLUTTER_TYPES_DEFS) 	\
	$(CLUTTER_DEFS) 	\
	clutter-types.defs	\
	clutter.defs

.defs.c:
	@echo "***INFO*** Generating $*.c from $*.defs" \
	&& ( $(PYGTK_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGTK_DEFSDIR)/gdk-types.defs \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
	    --register clutter-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $<) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c

