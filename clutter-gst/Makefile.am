include $(top_srcdir)/Makefile.tmpl

# clutter python extension modules
pycluttergstexecdir = $(pkgpyexecdir)/cluttergst

INCLUDES = $(pyclutter_common_includes)

pycluttergstexec_PYTHON = __init__.py
pycluttergstexec_LTLIBRARIES = _cluttergst.la

CLUTTERGST_DEFS = cluttergst.defs
CLEANFILES = cluttergst.c
EXTRA_DIST = $(CLUTTERGST_DEFS) cluttergst.override
cluttergst.c: $(CLUTTERGST_DEFS) cluttergst.override
_cluttergst_la_CFLAGS = $(CLUTTERGST_CFLAGS)
_cluttergst_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex init_cluttergst
_cluttergst_la_LIBADD = $(PYGTK_LIBS) $(CLUTTERGST_LIBS)
_cluttergst_la_SOURCES = cluttergstmodule.c
nodist__cluttergst_la_SOURCES = cluttergst.c

defsdir = $(pyclutter_defsdir)
defs_DATA = $(CLUTTERGST_DEFS)

# code generator
.defs.c:
	@echo "***INFO*** Generating $*.c from $*.defs" \
	&& ( $(PYGOBJECT_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGST_DEFSDIR)/gst-types.defs \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $<) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c
