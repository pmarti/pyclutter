# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

pyclutterexec_LTLIBRARIES = cluttergtk.la

common_ldflags = -module -avoid-version

CLUTTERGTK_DEFS = cluttergtk.defs
CLEANFILES = cluttergtk.c
EXTRA_DIST = $(CLUTTERGTK_DEFS) cluttergtk.override
cluttergtk.c: $(CLUTTERGTK_DEFS) cluttergtk.override
cluttergtk_la_CFLAGS = $(CLUTTERGTK_CFLAGS)
cluttergtk_la_LDFLAGS = $(common_ldflags) -export-symbols-regex initcluttergtk
cluttergtk_la_LIBADD = $(PYGTK_LIBS) $(CLUTTERGTK_LIBS)
cluttergtk_la_SOURCES = cluttergtkmodule.c
nodist_cluttergtk_la_SOURCES = cluttergtk.c

defsdir = $(pkgdatadir)/$(PLATFORM_VERSION)/defs
defs_DATA = $(CLUTTERGTK_DEFS)

# code generator
.defs.c:
	@echo "***INFO*** Generating $*.c from $*.defs" \
	&& ( $(PYGTK_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGTK_DEFSDIR)/gtk-types.defs \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $<) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c
