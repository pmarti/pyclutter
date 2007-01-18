INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

defsdir = $(datadir)/pyclutter/1.0/defs
defs_DATA = cluttergst.defs

EXTRA_DIST = $(defs_DATA)

pkgpythondir = $(pyexecdir)/clutter
pkgpyexecdir = $(pyexecdir)/clutter/gst

pycluttergstdir = $(pkgpythondir)/gst
pycluttergst_PYTHON = __init__.py

common_ldflags = -module -avoid-version

pkgpyexec_LTLIBRARIES = _gst.la
_gst_la_CFLAGS = $(CLUTTERGST_CFLAGS)
_gst_la_LDFLAGS = $(common_ldflags) $(PYTHON_LDFLAGS) -export-symbols-regex init_gst
_gst_la_LIBADD = $(CLUTTERGST_LIBS) $(PYTHON_LIBS)
_gst_la_SOURCES = cluttergstmodule.c
nodist__gst_la_SOURCES = cluttergst.c

CLEANFILES = cluttergst.c
EXTRA_DIST += cluttergst.override
cluttergst.c: cluttergst.defs cluttergst.override

.defs.c:
	( cd $(srcdir) \
	  && $(PYGTK_CODEGEN) \
	     --register $(PYGST_DEFSDIR)/gst-types.defs \
	     --register $(top_srcdir)/clutter/clutter-types.defs \
	     --override $(srcdir)/$*.override \
	     --prefix py$* $*.defs ) > gen-$*.c \
	&& ( cmp -s gen-$*.c $*.c || cp -f gen-$*.c $*.c ) \
	&& rm -f gen-$*.c

