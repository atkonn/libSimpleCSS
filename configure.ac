#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(scss, 1.0.0, konn@users.sourceforge.jp)
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADER([include/config.h])

# Checks for programs.
AM_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([apr-1],  [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h])

dnl ==================================================
dnl
dnl apr-config
dnl
dnl ==================================================
AC_ARG_WITH(apr-config, [  --with-apr-config=ARG  Path of apr-config program file.])
if test "x$with_apr_config" = "xyes" ; then
    AC_MSG_ERROR([
Please specify the --with-apr-config option. And, please specify the place of the apr-config program.
])
fi

dnl ==================================================
dnl
dnl apu-config
dnl
dnl ==================================================
AC_ARG_WITH(apu-config, [  --with-apu-config=ARG  Path of apu-config program file.])
if test "x$with_apu_config" = "xyes" ; then
    AC_MSG_ERROR([
Please specify the --with-apu-config option. And, please specify the place of the apu-config program.
])
fi

AC_PATH_PROG(LIBTOOL, libtool, no,
    /usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin)
if test "x$LIBTOOL" = "xno"; then
    AC_MSG_ERROR([libtool not found.])
fi


if test "x$with_apr_config" = "x" ; then
  AC_PATH_PROG(APR_CONFIG, apr-config, no, /usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin)
  if test "x$APR_CONFIG" = "xno" ; then
    AC_PATH_PROG(APR_1_CONFIG, apr-1-config, no, /usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin)
    if test "x$APR_1_CONFIG" = "xno" ; then
      AC_MSG_ERROR([apr-config and apr-1-config not found.])
    else
      APR_CONFIG="$APR_1_CONFIG"
    fi
  fi
fi
if test "x$with_apr_config" != "x" ; then
  APR_CONFIG=$with_apr_config
fi
if test "x$with_apu_config" = "x" ; then
  AC_PATH_PROG(APU_CONFIG, apu-config, no, /usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin)
  if test "x$APU_CONFIG" = "xno" ; then
    AC_PATH_PROG(APU_1_CONFIG, apu-1-config, no, /usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin)
    if test "x$APU_1_CONFIG" = "xno" ; then
      AC_MSG_ERROR([apu-config and apu-1-config not found.])
    else
      APU_CONFIG="$APU_1_CONFIG"
    fi
  fi
fi
if test "x$with_apu_config" != "x" ; then
  APU_CONFIG=$with_apu_config
fi


if test "x$with_apu_config" != "x" ; then
  APU_CONFIG=$with_apu_config
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([memset strcasecmp strncasecmp])

CFLAGS="${CFLAGS} -DLIBICONV_PLUG "
LIBS="${LIBS} `${APR_CONFIG} --ldflags` `${APR_CONFIG} --libs` "
LIBS="${LIBS} `${APU_CONFIG} --ldflags` `${APU_CONFIG} --libs` "
CFLAGS="${CFLAGS} `${APR_CONFIG} --includes` `${APR_CONFIG} --cflags` `${APR_CONFIG} --cppflags`"
CFLAGS="${CFLAGS} `${APU_CONFIG} --includes`"


AC_SUBST(APR_CONFIG)
AC_SUBST(APU_CONFIG)
AC_SUBST(CFLAGS)
AC_SUBST(LIBS)

AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_OUTPUT
