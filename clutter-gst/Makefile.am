# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

pyclutterexec_LTLIBRARIES = cluttergst.la

common_ldflags = -module -avoid-version

CLUTTERGST_DEFS = cluttergst.defs cluttergst.override
CLEANFILES = cluttergst.c
EXTRA_DIST = $(CLUTTERGST_DEFS) cluttergst.override
cluttergst.c: $(CLUTTERGST_DEFS) cluttergst.override
cluttergst_la_CFLAGS = $(CLUTTERGST_CFLAGS)
cluttergst_la_LDFLAGS = $(common_ldflags) -export-symbols-regex initcluttergst
cluttergst_la_LIBADD = $(PYGTK_LIBS) $(CLUTTERGST_LIBS)
cluttergst_la_SOURCES = cluttergstmodule.c
nodist_cluttergst_la_SOURCES = cluttergst.c

# code generator
.defs.c:
	( $(PYGTK_CODEGEN) \
	    -I $(top_srcdir)/clutter-gst \
	    --py_ssize_t-clean \
	    --register $(PYGST_DEFSDIR)/gst-types.defs \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $*.override \
	    --prefix py$(*F) $*.defs) > $(*D)/gen-$(*F).c \
	&& cp $(*D)/gen-$(*F).c $(*D)/$(*F).c \
	&& rm -f $(*D)/gen-$(*F).c
