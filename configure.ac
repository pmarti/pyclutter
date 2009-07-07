AC_PREREQ(2.53)

# clutter package version number, (as distinct from shared library version)
# An odd micro number indicates in-progress development, (eg. from svn)
# An even micro number indicates a released version.
m4_define(pyclutter_version_major, 0)
m4_define(pyclutter_version_minor, 9)
m4_define(pyclutter_version_micro, 1)
m4_define(pyclutter_version, pyclutter_version_major.pyclutter_version_minor.pyclutter_version_micro)

m4_define(clutter_required_version,      0.9.6)
m4_define(cluttergtk_required_version,   0.9.2)
m4_define(cluttergst_required_version,   0.9.0)
m4_define(pycairo_required_version,      1.0.2) dnl or 1.1.7
m4_define(pygtk_required_version,        2.8.0)

AC_INIT([pyclutter], [pyclutter_version],
        [http://bugzilla.o-hand.com/enter_bug.cgi?product=Clutter])

AC_DEFINE(PYCLUTTER_MAJOR_VERSION,
          [pyclutter_version_major], [pyclutter major version])
AC_SUBST(PYCLUTTER_MAJOR_VERSION, [pyclutter_version_major])
AC_DEFINE(PYCLUTTER_MINOR_VERSION,
          [pyclutter_version_minor], [pyclutter minor version])
AC_SUBST(PYCLUTTER_MINOR_VERSION, [pyclutter_version_minor])
AC_DEFINE(PYCLUTTER_MICRO_VERSION, [pyclutter_version_micro],
          [pyclutter micro version])
AC_SUBST(PYCLUTTER_MICRO_VERSION, [pyclutter_version_micro])
AC_DEFINE(PYCLUTTER_VERSION, [pyclutter_version], [pyclutter version])
AC_SUBST(PYCLUTTER_VERSION, [pyclutter_version])

AC_CONFIG_SRCDIR([clutter/cluttermodule.c])
AM_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE([1.9])

dnl put the ACLOCAL flags in the makefile
ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# uncomment in 0.7
#AM_PATH_PYTHON(2.5.0,,[AC_MSG_ERROR([could not find Python 2.5.0])])
AM_PATH_PYTHON(2.4.0,,[AC_MSG_ERROR([could not find Python 2.4.0])])
AM_CHECK_PYTHON_HEADERS(,[AC_MSG_ERROR([could not find Python headers])])

PLATFORM=`$PYTHON -c "from distutils import util; print util.get_platform()"`
AC_SUBST(PLATFORM)

dnl get rid of the -export-dynamic stuff from the configure flags ...
export_dynamic=`(./libtool --config; echo eval echo \\$export_dynamic_flag_spec) | sh`

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

dnl check for pygtk
PKG_CHECK_MODULES(PYGTK, pygtk-2.0 >= pygtk_required_version)
AC_SUBST(PYGTK_CFLAGS)
AC_PATH_PROG(PYGTK_CODEGEN, pygtk-codegen-2.0, no)
if test "x$PYGTK_CODEGEN" = "xno"; then
  AC_MSG_ERROR([could not find pygtk-codegen-2.0 script])
fi

PYGTK_CODEGEN_DEFINES=

dnl check for pycairo
PKG_CHECK_MODULES(PYCAIRO, [pycairo >= pycairo_required_version],
                           [have_pycairo=yes],
                           [have_pycairo=no])
if test "x$have_pycairo" = "xyes"; then
  AC_DEFINE([HAVE_PYCAIRO], [1], [Define to 1 if pycairo is available])
  AC_SUBST(PYCAIRO_CFLAGS)
  AC_SUBST(PYCAIRO_LIBS)
  PYGTK_CODEGEN_DEFINES="$PYGTK_CODEGEN_DEFINES -DHAVE_PYCAIRO"
fi

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

AC_MSG_CHECKING(for gst-python defs)
PYGST_DEFSDIR=`$PKG_CONFIG --variable=defsdir gst-python-0.10`
AC_SUBST(PYGST_DEFSDIR)
AC_MSG_RESULT($PYGST_DEFSDIR)

dnl check for clutter
PKG_CHECK_MODULES(CLUTTER, clutter-0.9 >= clutter_required_version)
AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)
if test -n "$export_dynamic"; then
  CLUTTER_LIBS=`echo $CLUTTER_LIBS | sed -e "s/$export_dynamic//"`
fi

dnl check for sub modules

if test "x$PYGST_DEFSDIR" = "x"; then
  AC_MSG_WARN([No PyGStreamer definitions found, disabling clutter-gst])
  build_cluttergst=no
else
  build_cluttergst=yes
fi

AC_ARG_WITH(cluttergst,
            AC_HELP_STRING([--with-cluttergst=@<:@yes/no@:>@],
                           [Build clutter.cluttergst submodule]),
            build_cluttergst=$with_cluttergst)

if test "x$build_cluttergst" = "xyes"; then
  PKG_CHECK_MODULES(CLUTTERGST,
                    clutter-gst-0.9 >= cluttergst_required_version,
                    build_cluttergst=yes,
                    build_cluttergst=no)
  AC_SUBST(CLUTTERGST_CFLAGS)
  AC_SUBST(CLUTTERGST_LIBS)
  if test -n "$export_dynamic"; then
    CLUTTERGST_LIBS=`echo $CLUTTERGST_LIBS | sed -e "s/$export_dynamic//"`
  fi
fi

AM_CONDITIONAL(BUILD_CLUTTERGST, [test "x$build_cluttergst" = "xyes"])

build_cluttergtk=yes
AC_ARG_WITH(cluttergtk,
            AC_HELP_STRING([--with-cluttergtk=@<:@yes/no@:>@],
                           [Build clutter.cluttergtk submodule]),
            build_cluttergtk=$with_cluttergtk)

if test "x$build_cluttergtk" = "xyes"; then
  PKG_CHECK_MODULES(CLUTTERGTK,
                    clutter-gtk-0.9 >= cluttergtk_required_version,
                    build_cluttergtk=yes,
                    build_cluttergtk=no)
  AC_SUBST(CLUTTERGTK_CFLAGS)
  AC_SUBST(CLUTTERGTK_LIBS)
  if test -n "$export_dynamic"; then
    CLUTTERGTK_LIBS=`echo $CLUTTERGTK_LIBS | sed -e "s/$export_dynamic//"`
  fi
fi

AM_CONDITIONAL(BUILD_CLUTTERGTK, [test "x$build_cluttergtk" = "xyes"])


dnl Building documentation
m4_define([docs_default],
          m4_if(m4_eval(pyclutter_version_minor % 2), [0], [yes], [no]))

AC_ARG_ENABLE(docs,
              AC_HELP_STRING([--enable-docs], [Enable documentation building]),
              enable_docs=docs_default,
              enable_docs="no")

if test "x$enable_docs" = "xyes"; then
  dnl Check for xsltproc
  AC_PATH_PROG([XSLTPROC], [xsltproc])
  if test -z "$XSLTPROC"; then
    enable_docs=no
  else
    PYGOBJECT_DATADIR=`$PKG_CONFIG --variable=datadir pygobject-2.0`
    PYGOBJECT_PYGDOCS=`$PKG_CONFIG --variable=pygdocs pygobject-2.0`
    PYGOBJECT_FIXXREF=`$PKG_CONFIG --variable=fixxref pygobject-2.0`

    AC_SUBST(PYGOBJECT_DATADIR)
    AC_SUBST(PYGOBJECT_PYGDOCS)
    AC_SUBST(PYGOBJECT_FIXXREF)
  fi
fi

AM_CONDITIONAL(ENABLE_DOCS, [test "x$enable_docs" = "xyes"])

dnl add required cflags ...
JH_ADD_CFLAG([-Wall])
#JH_ADD_CFLAG([-std=c9x])
JH_ADD_CFLAG([-fno-strict-aliasing])

AC_CONFIG_FILES([
        Makefile
        pyclutter.pc
        docs/Makefile
        docs/reference/entities.docbook
        examples/Makefile
        clutter/Makefile
        clutter-gst/Makefile
        clutter-gtk/Makefile
])

AC_OUTPUT

echo "* PyClutter:
        build cluttergst:     $build_cluttergst
        build cluttergtk:     $build_cluttergtk
        enable documentation: $enable_docs
"
