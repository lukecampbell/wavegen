#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([riff2], [1.0], [luke.s.campbell@gmail.com])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/riff2.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_PREFIX_DEFAULT([/usr])
# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC([],[])
AC_CHECK_HEADERS([string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_C_BIGENDIAN([AC_DEFINE([RIFF_BIG_ENDIAN],1,[Big Endian])],[AC_DEFINE([RIFF_LITTLE_ENDIAN],1,[Little Endian])])
# Checks for library functions.


AC_OUTPUT
