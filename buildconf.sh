#!/bin/sh
# autogen.sh - generates configure using the autotools
# $Id$
#export WANT_AUTOCONF=2.5
#libtoolize --force --copy
rm -f ./aclocal.m4
rm -f ./Makefile
rm -f ./Makefile.in
rm -f ./configure
rm -f ./config.guess
rm -f ./config.log
rm -f ./config.sub
rm -f ./config.status
rm -f ./install-sh
#rm -f ./libtool
#rm -f ./ltmain.sh
rm -f ./missing
rm -f ./mkinstalldirs
aclocal 
autoheader
automake -a -c 
#automake 
autoconf
rm -rf autom4te.cache

