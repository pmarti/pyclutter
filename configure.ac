AC_PREREQ(2.53)

# clutter package version number, (as distinct from shared library version)
# An odd micro number indicates in-progress development, (eg. from CVS)
# An even micro number indicates a released version.
m4_define(pyclutter_version_major, 0)
m4_define(pyclutter_version_minor, 1)
m4_define(pyclutter_version_micro, 2)
m4_define(pyclutter_version, pyclutter_version_major.pyclutter_version_minor.pyclutter_version_micro)

m4_define(clutter_required_version, 0.1.1)
m4_define(pygtk_required_version,   2.8.0)

AC_INIT([pyclutter], pyclutter_version, 
        [http://bugzilla.o-hand.com/enter_bug.cgi?product=Clutter])

AC_DEFINE(PYCLUTTER_MAJOR_VERSION, [pyclutter_version_major], [pyclutter major version])
AC_SUBST(PYCLUTTER_MAJOR_VERSION, [pyclutter_version_major])
AC_DEFINE(PYCLUTTER_MINOR_VERSION, [pyclutter_version_minor], [pyclutter minor version])
AC_SUBST(PYCLUTTER_MINOR_VERSION, [pyclutter_version_minor])
AC_DEFINE(PYCLUTTER_MICRO_VERSION, [pyclutter_version_micro], [pyclutter micro version])
AC_SUBST(PYCLUTTER_MICRO_VERSION, [pyclutter_version_micro])

AC_CONFIG_SRCDIR([clutter/cluttermodule.c])
AM_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE([1.8])

dnl put the ACLOCAL flags in the makefile
ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AM_PATH_PYTHON(2.3.5)
AM_CHECK_PYTHON_HEADERS(,[AC_MSG_ERROR(could not find Python headers)])

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
if test "x$PYGTK_CODEGEN" = xno; then
  AC_MSG_ERROR(could not find pygtk-codegen-2.0 script)
fi

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

PKG_CHECK_MODULES(CLUTTER, clutter-0.1 >= clutter_required_version)
AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)
if test -n "$export_dynamic"; then
  CLUTTER_LIBS=`echo $CLUTTER_LIBS | sed -e "s/$export_dynamic//"`
fi

dnl add required cflags ...
JH_ADD_CFLAG([-Wall])
JH_ADD_CFLAG([-std=c9x])
JH_ADD_CFLAG([-fno-strict-aliasing])

AC_OUTPUT([
Makefile
examples/Makefile
clutter/Makefile
clutter/pyclutter.pc
])
