include $(top_srcdir)/Makefile.tmpl

# clutter python extension modules
pycluttercairoexecdir = $(pkgpyexecdir)/cluttercairo

INCLUDES = $(pyclutter_common_includes)

pycluttercairoexec_PYTHON = __init__.py
pycluttercairoexec_LTLIBRARIES = _cluttercairo.la

CLUTTERCAIRO_DEFS = cluttercairo.defs
CLEANFILES = cluttercairo.c
EXTRA_DIST = $(CLUTTERCAIRO_DEFS) cluttercairo.override
cluttercairo.c: $(CLUTTERCAIRO_DEFS) cluttercairo.override
_cluttercairo_la_CFLAGS = $(PYCAIRO_CFLAGS) $(CLUTTERCAIRO_CFLAGS)
_cluttercairo_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex init_cluttercairo
_cluttercairo_la_LIBADD = $(PYGTK_LIBS) $(PYCAIRO_LIBS) $(CLUTTERCAIRO_LIBS)
_cluttercairo_la_SOURCES = cluttercairomodule.c
nodist__cluttercairo_la_SOURCES = cluttercairo.c

defsdir = $(pyclutter_defsdir)
defs_DATA = $(CLUTTERCAIRO_DEFS)

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
