## Process this with automake to create Makefile.in

AUTOMAKE_OPTIONS = foreign

pkglib_LTLIBRARIES = libconsoles.la

INCLUDES = -I. -I../../include -I$(srcdir)/../../include
libconsoles_la_SOURCES = stdio.cxx fileio.cxx socketio.cxx components.cxx
libconsoles_la_LDFLAGS = -module -no-undefined
libconsoles_la_LIBADD = $(socket_libs)

pkgdata_DATA = sid-io-stdio.txt sid-io-fileio.txt sid-io-socket.txt hw-visual-tty.tk

DEJAGNUTESTS=stdio.exp consdocs.exp consmonkey.exp stdioval.exp stdioinv.exp socketval.exp socketinv.exp
check-local:
	(cd ../testsuite ; $(MAKE) check RUNTESTFLAGS="$(RUNTESTFLAGS) $(DEJAGNUTESTS)" )

html_stylesheet=$(srcdir)/../component_html.xsl
include $(srcdir)/../../config/Makefile.docs
