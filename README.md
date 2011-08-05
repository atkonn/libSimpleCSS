libSimpleCSS
============

&copy; 2008,2009,2010,2011 Atsushi Konno 

libSimpleCSS is an open source ([Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0)) Simple like CSS Parser and selection engine for C Language used only APR, allowing you to parse the sloppy CSS using APR pool.
This have been used in [mod_chxj](http://sourceforge.jp/projects/modchxj/) since 2008.


Why?
----
I needed features below.

1. Using only APR library
2. The parser which can analyze the document like CSS without incident and changes.
3. Easy to use
4. Simple
5. Not strict with the grammar of CSS at all.
6. License is [Apache 2.0](http://www.apache.org/licenses/LICENSES-2.0) or compatible with BSD.
7. written in C
8. A source code completely stupid because it does not need worry to change it
9. A small source code.

but, I couldn't find it.


How to install
--------------
1. ./buildconf.sh
2. ./configure
3. make
4. make install


How to use
----------
see ``test/example-1.c''.
it is sample source.

