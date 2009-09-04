AC_PREREQ(2.53)

# clutter package version number, (as distinct from shared library version)
# An odd micro number indicates in-progress development, (eg. from svn)
# An even micro number indicates a released version.
m4_define(pyclutter_version_major, 1)
m4_define(pyclutter_version_minor, 0)
m4_define(pyclutter_version_micro, 1)
m4_define(pyclutter_version, pyclutter_version_major.pyclutter_version_minor.pyclutter_version_micro)

m4_define(clutter_required_version,      1.0.0)
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
AC_CONFIG_MACRO_DIR([build/autotools])
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
AM_PATH_PYTHON(2.5.0,,[AC_MSG_ERROR([could not find Python 2.5.0])])
#AM_PATH_PYTHON(2.4.0,,[AC_MSG_ERROR([could not find Python 2.4.0])])
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
PKG_CHECK_MODULES(PYGTK, [pygtk-2.0 >= pygtk_required_version])
AC_SUBST(PYGTK_CFLAGS)
AC_PATH_PROGS(PYGOBJECT_CODEGEN, [pygobject-codegen-2.0 pygtk-codegen-2.0], [no])
AS_IF([test "x$PYGOBJECT_CODEGEN" = "xno"],
      [
        AC_MSG_ERROR([could not find pygobject-codegen-2.0 script])
      ]
)

PYGOBJECT_CODEGEN_DEFINES=

dnl check for pycairo
PKG_CHECK_MODULES(PYCAIRO, [pycairo >= pycairo_required_version])
AC_SUBST(PYCAIRO_CFLAGS)
AC_SUBST(PYCAIRO_LIBS)

AC_MSG_CHECKING([for pygtk defs])
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

dnl check for clutter
PKG_CHECK_MODULES(CLUTTER, clutter-1.0 >= clutter_required_version)
AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)
AS_IF([test -n "$export_dynamic"],
      [
        CLUTTER_LIBS=`echo $CLUTTER_LIBS | sed -e "s/$export_dynamic//"`
      ]
)

dnl Building X11 extension
build_clutterx11=yes
AC_ARG_WITH([clutterx11],
            [AC_HELP_STRING([--with-clutterx11=@<:@yes/no@:>@],
                            [Build clutter.x11 submodule])],
            [build_clutterx11=$with_clutterx11])

AS_IF([test "x$build_clutterx11" = "xyes"],
      [
        PKG_CHECK_MODULES([CLUTTERX11],
                          [clutter-x11-1.0 >= clutter_required_version],
                          [build_clutterx11=yes],
                          [build_clutterx11=no])
        AC_SUBST(CLUTTERX11_CFLAGS)
        AC_SUBST(CLUTTERX11_LIBS)
        AC_DEFINE([HAVE_CLUTTERX11], [1], [Define to 1 if clutter-x11 is available])

        AS_IF([test -n "$export_dynamic"],
              [
                CLUTTERX11_LIBS=`echo $CLUTTERX11_LIBS | sed -e "s/$export_dynamic//"`
              ]
        )
      ]
)

AM_CONDITIONAL([BUILD_CLUTTERX11], [test "x$build_clutterx11" = "xyes"])


dnl Building GLX extension
build_clutterglx=yes
AC_ARG_WITH([clutterglx],
            [AC_HELP_STRING([--with-clutterglx=@<:@yes/no@:>@],
                            [Build clutter.glx submodule])],
            [build_clutterglx=$with_clutterglx])

AS_IF([test "x$build_clutterglx" = "xyes"],
      [
        AC_MSG_CHECKING([for Clutter GLX support])
		clutter_backend=`$PKG_CONFIG --variable=backend clutter-x11-1.0`
		AS_IF([test "x$clutter_backend" != "xglx"], [build_clutterglx=no])
		AC_MSG_RESULT([$build_clutterglx])
      ]
)

AM_CONDITIONAL([BUILD_CLUTTERGLX], [test "x$build_clutterglx" = "xyes"])


dnl Building documentation
m4_define([docs_default], [m4_if(m4_eval(pyclutter_version_minor % 2), [0], [yes], [no])])

AC_ARG_ENABLE([docs],
              [AC_HELP_STRING([--enable-docs], [Enable documentation building])],
              [],
              [enable_docs=docs_default])

AS_IF([test "x$enable_docs" = "xyes"],
      [
        dnl Check for xsltproc
        AC_PATH_PROG([XSLTPROC], [xsltproc], [], [enable_docs=no])

        PYGOBJECT_DATADIR=`$PKG_CONFIG --variable=datadir pygobject-2.0`
        PYGOBJECT_PYGDOCS=`$PKG_CONFIG --variable=pygdocs pygobject-2.0`
        PYGOBJECT_FIXXREF=`$PKG_CONFIG --variable=fixxref pygobject-2.0`

        AC_SUBST(PYGOBJECT_DATADIR)
        AC_SUBST(PYGOBJECT_PYGDOCS)
        AC_SUBST(PYGOBJECT_FIXXREF)
      ]
)

AM_CONDITIONAL(ENABLE_DOCS, [test "x$enable_docs" = "xyes"])

dnl add required cflags ...
JH_ADD_CFLAG([-Wall])
#JH_ADD_CFLAG([-std=c9x])
JH_ADD_CFLAG([-fno-strict-aliasing])

SHAVE_INIT([build/autotools], [enable])

AC_CONFIG_FILES([
        Makefile
	build/Makefile
	build/autotools/Makefile
	build/autotools/shave-libtool
	build/autotools/shave
        pyclutter.pc
        docs/Makefile
        docs/reference/entities.docbook
        examples/Makefile
        clutter/Makefile
])

AC_OUTPUT

echo "* PyClutter:
    enable documentation: $enable_docs
    build x11 submodule:  $build_clutterx11
    build glx submodule:  $build_clutterglx
"
