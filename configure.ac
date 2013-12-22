#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(asc, 0.1.0-pre, jainooson@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/asc.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
m4_pattern_allow([AC_CHECK_HEADER_STDBOOL])

# Checks for library functions.
AC_CHECK_FUNCS([strtol])
AC_FUNC_STRTOD

AC_ARG_WITH(
    [googletest],
    [AS_HELP_STRING([--with-googletest])],
    [AC_SUBST([GTEST], ["$with_googletest"])]
)

AM_CONDITIONAL([HAVE_GTEST], [test x$with_googletest != x] )

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
