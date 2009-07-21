include $(top_srcdir)/Makefile.tmpl

CLEANFILES =
EXTRA_DIST = 
INCLUDES = $(pyclutter_common_includes)

CREATEDEFS = $(PYTHON) $(top_srcdir)/createdefs.py

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

# clutter python scripts
pyclutterdir = $(pkgpythondir)/clutter
pyclutter_PYTHON = __init__.py keysyms.py deprecation.py

# clutter headers
pkgincludedir = $(includedir)/pyclutter-$(PLATFORM_VERSION)/pyclutter
pkginclude_HEADERS = pyclutter.h

COGL_DEFS = cogl-base.defs
CLUTTER_DEFS = clutter-base.defs

COGL_TYPES_DEFS = cogl-base-types.defs
CLUTTER_TYPES_DEFS = clutter-base-types.defs

COGL_OVERRIDES =			\
	cogl.override			\
	cogl-texture.override   \
	cogl-material.override  \
	cogl-shader.override    \
	cogl-matrix.override

CLUTTER_OVERRIDES = 			\
	clutter.override		\
	clutter-actor.override 		\
	clutter-behaviour.override	\
	clutter-boxed.override 		\
	clutter-color.override		\
	clutter-event.override		\
	clutter-model.override		\
	clutter-script.override     \
	clutter-cairotexture.override \
	clutter-interval.override \
	clutter-animation.override

CLEANFILES += 			\
	cogl.c 			\
	clutter.c 		\
	cogl-types.defs 	\
	clutter-types.defs 	\
	cogl.defs 		\
	clutter.defs

EXTRA_DIST += 			\
	$(COGL_DEFS)		\
	$(COGL_TYPES_DEFS)	\
	$(COGL_OVERRIDES)	\
	$(CLUTTER_DEFS) 	\
	$(CLUTTER_TYPES_DEFS)	\
	$(CLUTTER_OVERRIDES)

cogl.defs: $(COGL_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(COGL_DEFS)

clutter.defs: $(CLUTTER_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTER_DEFS)

cogl-types.defs: $(COGL_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(COGL_TYPES_DEFS)

clutter-types.defs: $(CLUTTER_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTER_TYPES_DEFS)

cogl.c: cogl-types.defs cogl.defs $(COGL_OVERRIDES)
clutter.c: cogl-types.defs clutter-types.defs clutter.defs cogl.defs $(CLUTTER_OVERRIDES)

_clutter_la_CFLAGS  = $(PYCAIRO_CFLAGS) $(CLUTTER_CFLAGS)
_clutter_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex init_clutter
_clutter_la_LIBADD  = $(PYCAIRO_LIBS) $(PYGTK_LIBS) $(CLUTTER_LIBS)
_clutter_la_SOURCES = 		\
	cluttermodule.c		\
        pyclutter-private.h     \
	pyclutter.h		\
	pyclutter.c
nodist__clutter_la_SOURCES = clutter.c cogl.c

pyclutterexec_LTLIBRARIES = _clutter.la

# defs files
defsdir = $(pyclutter_defsdir)
defs_DATA = \
	$(COGL_DEFS)		\
	$(CLUTTER_DEFS) 	\
	$(COGL_TYPES_DEFS)	\
	$(CLUTTER_TYPES_DEFS) 	\
	cogl.defs		\
	clutter.defs		\
	cogl-types.defs		\
	clutter-types.defs

.defs.c:
	$(QUIET_GEN)( $(PYGOBJECT_CODEGEN) \
	   $(PYGOBJECT_CODEGEN_DEFINES) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGTK_DEFSDIR)/gdk-types.defs \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
	    --register cogl-types.defs \
	    --register clutter-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $< ) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c

# delete the old submodules, if any, to avoid collisions
install-data-local:
	(cd $(DESTDIR)$(pyclutterexecdir) && \
	 rm -f cluttercairo.so && \
	 rm -f cluttergst.so && \
	 rm -f cluttergtk.so)

# this is a hack - do not remove
# this rule is needed to prevent generating clutter-types.c because
# we have clutter-types.defs
#clutter-types.c:
#	@:

