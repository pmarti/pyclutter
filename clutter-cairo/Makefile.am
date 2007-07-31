# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

pyclutterexec_LTLIBRARIES = cluttercairo.la

common_ldflags = -module -avoid-version

CLUTTERCAIRO_DEFS = cluttercairo.defs
CLEANFILES = cluttercairo.c
EXTRA_DIST = $(CLUTTERCAIRO_DEFS) cluttercairo.override
cluttercairo.c: $(CLUTTERCAIRO_DEFS) cluttercairo.override
cluttercairo_la_CFLAGS = $(PYCAIRO_CFLAGS) $(CLUTTERCAIRO_CFLAGS)
cluttercairo_la_LDFLAGS = $(common_ldflags) -export-symbols-regex initcluttercairo
cluttercairo_la_LIBADD = $(CLUTTERCAIRO_LIBS)
cluttercairo_la_SOURCES = cluttercairomodule.c
nodist_cluttercairo_la_SOURCES = cluttercairo.c

defsdir = $(pkgdatadir)/$(PLATFORM_VERSION)/defs
defs_DATA = $(CLUTTERGST_DEFS)

# code generator
.defs.c:
	( $(PYGTK_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $*.override \
	    --prefix py$(*F) $*.defs) > $(*D)/gen-$(*F).c \
	&& cp $(*D)/gen-$(*F).c $(*D)/$(*F).c \
	&& rm -f $(*D)/gen-$(*F).c
