#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Hasher program], [0.00], [khaibulaev.mn@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(
    [rhash],
    [rhash_library_init, rhash_file, rhash_msg, rhash_get_digest_size, rhash_print_bytes],
    [],
    [AC_MSG_ERROR([rhash not found])]
)

AC_ARG_WITH(
    [readline],
    [AS_HELP_STRING([--without-readline], [do not use readline])],
    [],
    AC_CHECK_LIB([readline], [readline], [], [AC_MSG_ERROR([readline not found])])
)

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h string.h rhash.h ctype.h errno.h])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
