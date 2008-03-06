# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS) -I$(top_srcdir)/clutter

pyclutterexec_LTLIBRARIES = tidy.la

common_ldflags = -module -avoid-version

TIDY_DEFS = tidy.defs
CLEANFILES = tidy.c
EXTRA_DIST = $(TIDY_DEFS) tidy-types.defs tidy.override
tidy.c: $(TIDY_DEFS) tidy.override
tidy_la_CFLAGS = $(TIDY_CFLAGS)
tidy_la_LDFLAGS = $(common_ldflags) -export-symbols-regex inittidy
tidy_la_LIBADD = $(PYGTK_LIBS) $(TIDY_LIBS)
tidy_la_SOURCES = tidymodule.c
nodist_tidy_la_SOURCES = tidy.c

defsdir = $(pkgdatadir)/$(PLATFORM_VERSION)/defs
defs_DATA = $(TIDY_DEFS)

# code generator
.defs.c:
	@echo "***INFO*** Generating $*.c from $*.defs" \
	&& ( $(PYGTK_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $<) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c

