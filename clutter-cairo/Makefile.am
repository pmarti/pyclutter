# python scripts & extension modules
pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

# clutter python extension modules
pyclutterexecdir = $(pkgpyexecdir)/clutter

pyclutterexec_LTLIBRARIES = cluttercairo.la

common_ldflags = -module -avoid-version

CLUTTERCAIRO_DEFS = cluttercairo.defs cluttercairo.override
CLEANFILES = cluttercairo.c
EXTRA_DIST = $(CLUTTERCAIRO_DEFS) cluttercairo.override
cluttercairo.c: $(CLUTTERCAIRO_DEFS) cluttercairo.override
cluttercairo_la_CFLAGS = $(CLUTTERCAIRO_CFLAGS)
cluttercairo_la_LDFLAGS = $(common_ldflags) -export-symbols-regex initcluttercairo
cluttercairo_la_LIBADD = $(CLUTTERCAIRO_LIBS)
cluttercairo_la_SOURCES = cluttercairomodule.c
nodist_cluttercairo_la_SOURCES = cluttercairo.c
