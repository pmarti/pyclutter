include $(top_srcdir)/Makefile.tmpl

# clutter python extension modules
pycluttergtkexecdir = $(pkgpyexecdir)/cluttergtk

INCLUDES = $(pyclutter_common_includes)

pycluttergtkexec_PYTHON = __init__.py
pycluttergtkexec_LTLIBRARIES = _cluttergtk.la

CLUTTERGTK_DEFS = cluttergtk.defs
CLEANFILES = cluttergtk.c
EXTRA_DIST = $(CLUTTERGTK_DEFS) cluttergtk.override
cluttergtk.c: $(CLUTTERGTK_DEFS) cluttergtk.override
_cluttergtk_la_CFLAGS = $(CLUTTERGTK_CFLAGS)
_cluttergtk_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex init_cluttergtk
_cluttergtk_la_LIBADD = $(PYGTK_LIBS) $(CLUTTERGTK_LIBS)
_cluttergtk_la_SOURCES = cluttergtkmodule.c
nodist__cluttergtk_la_SOURCES = cluttergtk.c

defsdir = $(pyclutter_defsdir)
defs_DATA = $(CLUTTERGTK_DEFS)

# code generator
.defs.c:
	@echo "***INFO*** Generating $*.c from $*.defs" \
	&& ( $(PYGOBJECT_CODEGEN) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGTK_DEFSDIR)/gtk-types.defs \
	    --register $(top_srcdir)/clutter/clutter-base-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $<) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c
