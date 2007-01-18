INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)

defsdir = $(datadir)/pyclutter/1.0/defs
defs_DATA = cluttergst.defs

EXTRA_DIST = $(defs_DATA)

pkgpythondir = $(pyexecdir)/clutter
pkgpyexecdir = $(pyexecdir)/clutter

common_ldflags = -module -avoid-version

pkgpyexec_LTLIBRARIES = cluttergst.la
cluttergst_la_CFLAGS = $(CLUTTERGST_CFLAGS)
cluttergst_la_LDFLAGS = $(common_ldflags) $(PYTHON_LDFLAGS) -export-symbols-regex initcluttergst
cluttergst_la_LIBADD = $(CLUTTERGST_LIBS) $(PYTHON_LIBS)
cluttergst_la_SOURCES = cluttergstmodule.c
nodist_cluttergst_la_SOURCES = cluttergst.c

CLEANFILES = cluttergst.c
EXTRA_DIST += gst.override
gst.c: cluttergst.defs cluttergst.override

.defs.c:
	( cd $(srcdir) \
	  && $(PYGTK_CODEGEN) \
	     --register $(PYGST_DEFSDIR)/gst-types.defs \
	     --register $(top_srcdir)/clutter/clutter-types.defs \
	     --override $(srcdir)/$*.override \
	     --prefix py$* $*.defs ) > gen-$*.c \
	&& ( cmp -s gen-$*.c $*.c || cp -f gen-$*.c $*.c ) \
	&& rm -f gen-$*.c

