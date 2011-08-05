libscss_la_SOURCES = main.c \
  ignore_sp.c \
  starts_with.c  \
  dump_nodes.c \
  sac.c \
  trim.c \
  create_node.c \
  doc.c \
  strip_quote.c \
  iconv.c

libscss_la_CFLAGS = -O2 -prefer-pic -I. -I../include -I./serf
AM_CFLAGS = @CFLAGS@ -O2 -prefer-pic -I. -I../include 

lib_LTLIBRARIES = libscss.la


clean:
	rm -fr .libs
	rm -f *.o *.lo *.la
