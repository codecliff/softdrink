# ####################################################
# Author    : Rahul Singh 
# URL       : https://github.com/codecliff/softdrink
# License   : MIT 
# email     : codecliff@users.noreply.github.com
# Disclaimer: No warranties, stated or implied.   
# Description : 
#   This File is part of softdrink project
#   A personal attempt to create directory shortcuts 
#   for Gnome and Nautilus file browser 
#   (Acknowledgment: This project has heavily used LLMs 
#                    viz. Phind, Bard and ChatGPT )
# #####################################################

## Better keep this file read-only. 
## it picks version number from external file src/VERSION



AC_PREREQ([2.69])

m4_define([m4_PACKAGE_VERSION], m4_normalize(m4_include([src/VERSION])))
AC_INIT([softdrink], m4_PACKAGE_VERSION, [bugs@example.com])
#AC_INIT([softdrink], [0.2], [bugs@example.com])
AC_CONFIG_SRCDIR([src/softdrink.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE( [-Wall -Werror foreign] )

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# abort configure if nautilus not installed.
AC_CHECK_PROGS([GNOME], [gnome-shell])
AS_IF([test -z "$GNOME"], [AC_MSG_ERROR([Gnome not found on this system, aborting])])

AC_CHECK_PROGS([NAUTILUS], [nautilus])
AS_IF([test -z "$NAUTILUS"], [AC_MSG_ERROR([nautilus not found on this system, aborting ])])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove pathconf realpath strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
