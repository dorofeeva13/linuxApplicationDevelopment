AC_PREREQ([2.69])
AC_INIT(guess_number, 0.0, dorofeeva97@bk.ru)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AM_INIT_AUTOMAKE

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

define(CMNT, [\/\* COMMENT:: AC_PACKAGE_NAME, VERSION:: AC_PACKAGE_VERSION, DATE:: `date` \*\/])

sed -i "1s/.*COMMENT::.*VERSION::.*DATE.*/CMNT/; t; 1s/^/CMNT\n/" *.c
sed -i "1s/.*COMMENT::.*VERSION::.*DATE.*/CMNT/; t; 1s/^/CMNT\n/" *.h