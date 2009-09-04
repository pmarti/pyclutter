include $(top_srcdir)/Makefile.tmpl

NULL =

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
CLUTTERX11_DEFS = clutterx11-base.defs
CLUTTERGLX_DEFS = clutterglx-base.defs

COGL_TYPES_DEFS = cogl-base-types.defs
CLUTTER_TYPES_DEFS = clutter-base-types.defs
CLUTTERX11_TYPES_DEFS = clutterx11-base-types.defs
CLUTTERGLX_TYPES_DEFS = clutterglx-base-types.defs

COGL_OVERRIDES =		\
	cogl.override		\
	cogl-material.override  \
	cogl-matrix.override    \
	cogl-offscreen.override	\
	cogl-shader.override    \
	cogl-texture.override   \
	$(NULL)

CLUTTER_OVERRIDES = 			\
	clutter.override		\
	clutter-actor.override 		\
	clutter-alpha.override		\
	clutter-animation.override	\
	clutter-behaviour.override	\
	clutter-boxed.override 		\
	clutter-cairotexture.override 	\
	clutter-color.override		\
	clutter-container.override	\
	clutter-event.override		\
	clutter-interval.override 	\
	clutter-model.override		\
	clutter-path.override		\
	clutter-script.override     	\
	$(NULL)

CLUTTERX11_OVERRIDES = \
	clutterx11.override

CLUTTERGLX_OVERRIDES = \
	clutterglx.override

CLEANFILES += 			\
	cogl.c 			\
	clutter.c 		\
	cogl-types.defs 	\
	clutter-types.defs 	\
	cogl.defs 		\
	clutter.defs 	\
	clutterx11.c 			\
	clutterx11.defs 	\
	clutterx11-types.defs 	\
	clutterglx.c 			\
	clutterglx.defs 	\
	clutterglx-types.defs

EXTRA_DIST += 			\
	$(COGL_DEFS)		\
	$(COGL_TYPES_DEFS)	\
	$(COGL_OVERRIDES)	\
	$(CLUTTER_DEFS) 	\
	$(CLUTTER_TYPES_DEFS)	\
	$(CLUTTER_OVERRIDES) \
	$(CLUTTERX11_DEFS) \
	$(CLUTTERX11_TYPES_DEFS) \
	$(CLUTTERX11_OVERRIDES) \
	$(CLUTTERGLX_DEFS) \
	$(CLUTTERGLX_TYPES_DEFS) \
	$(CLUTTERGLX_OVERRIDES)

cogl.defs: $(COGL_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(COGL_DEFS)

clutter.defs: $(CLUTTER_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTER_DEFS)

cogl-types.defs: $(COGL_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(COGL_TYPES_DEFS)

clutter-types.defs: $(CLUTTER_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTER_TYPES_DEFS)

clutterx11.defs: $(CLUTTERX11_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTERX11_DEFS)

clutterx11-types.defs: $(CLUTTERX11_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTERX11_TYPES_DEFS)

clutterglx.defs: $(CLUTTERGLX_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTERGLX_DEFS)

clutterglx-types.defs: $(CLUTTERGLX_TYPES_DEFS) Makefile
	$(QUIET_GEN)$(CREATEDEFS) $@ $(CLUTTERGLX_TYPES_DEFS)

cogl.c: cogl-types.defs cogl.defs $(COGL_OVERRIDES)
clutter.c: cogl-types.defs clutter-types.defs clutter.defs cogl.defs $(CLUTTER_OVERRIDES)
clutterx11.c: clutterx11-types.defs clutterx11.defs $(CLUTTERX11_OVERRIDES)
clutterglx.c: clutterglx-types.defs clutterglx.defs $(CLUTTERGLX_OVERRIDES)

_clutter_la_CFLAGS  = $(PYCAIRO_CFLAGS) $(CLUTTER_CFLAGS)
_clutter_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex init_clutter
_clutter_la_LIBADD  = $(PYCAIRO_LIBS) $(PYGOBJECT_LIBS) $(CLUTTER_LIBS)
_clutter_la_SOURCES = 		\
	cluttermodule.c		\
	pyclutter-private.h     \
	pyclutter.h		\
	pyclutter.c
nodist__clutter_la_SOURCES = clutter.c cogl.c

x11_la_CFLAGS = $(PYCAIRO_CFLAGS) $(CLUTTER_CFLAGS) $(CLUTTERX11_CFLAGS)
x11_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex initx11
x11_la_LIBADD = $(PYCAIRO_LIBS) $(PYGOBJECT_LIBS) $(CLUTTER_LIBS) $(CLUTTERX11_LIBS)
x11_la_SOURCES = clutterx11module.c
nodist_x11_la_SOURCES = clutterx11.c

glx_la_CFLAGS = $(PYCAIRO_CFLAGS) $(CLUTTER_CFLAGS) $(CLUTTERGLX_CFLAGS)
glx_la_LDFLAGS = $(pyclutter_common_ldflags) -export-symbols-regex initglx
glx_la_LIBADD = $(PYCAIRO_LIBS) $(PYGOBJECT_LIBS) $(CLUTTER_LIBS) $(CLUTTERGLX_LIBS)
glx_la_SOURCES = clutterglxmodule.c
nodist_glx_la_SOURCES = clutterglx.c

pyclutterexec_LTLIBRARIES = _clutter.la

# defs files
defsdir = $(pyclutter_defsdir)
defs_DATA = \
	$(COGL_DEFS)		\
	$(CLUTTER_DEFS) 	\
	$(COGL_TYPES_DEFS)	\
	$(CLUTTER_TYPES_DEFS) 	\
	$(CLUTTERX11_DEFS) 	\
	$(CLUTTERX11_TYPES_DEFS) 	\
	cogl.defs		\
	clutter.defs		\
	cogl-types.defs		\
	clutter-types.defs 	\
	clutterx11.defs 	\
	clutterx11-types.defs


if BUILD_CLUTTERX11
 defs_DATA += \
	$(CLUTTERX11_DEFS) 	\
	$(CLUTTERX11_TYPES_DEFS) 	\
	clutterx11.defs 	\
	clutterx11-types.defs

 pyclutterexec_LTLIBRARIES += x11.la
endif

if BUILD_CLUTTERGLX
 defs_DATA += \
	$(CLUTTERGLX_DEFS) 	\
	$(CLUTTERGLX_TYPES_DEFS) 	\
	clutterglx.defs 	\
	clutterglx-types.defs

 pyclutterexec_LTLIBRARIES += glx.la
endif

.defs.c:
	$(QUIET_GEN)( $(PYGOBJECT_CODEGEN) \
	   $(PYGOBJECT_CODEGEN_DEFINES) \
	    -I $(srcdir) \
	    --py_ssize_t-clean \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
	    --register cogl-types.defs \
	    --register clutter-types.defs \
	    --override $(srcdir)/$*.override \
	    --prefix py$* $< ) > gen-$*.c \
	&& cp -f gen-$*.c $*.c \
	&& rm -f gen-$*.c

# delete the old submodules, if any, to avoid collisions
install-data-local:
	(test -d $(DESTDIR)$(pyclutterexecdir) && \
	 cd $(DESTDIR)$(pyclutterexecdir) && \
	 rm -f cluttercairo.so && \
	 rm -f cluttergst.so && \
	 rm -f cluttergtk.so)

# this is a hack - do not remove
# this rule is needed to prevent generating clutter-types.c because
# we have clutter-types.defs
#clutter-types.c:
#	@:

