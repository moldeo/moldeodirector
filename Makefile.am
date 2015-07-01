ACLOCAL_AMFLAGS=-I m4
SUBDIRS = data moldeodirector

EXTRA_DIST = AUTHORS ChangeLog NEWS README

datadir = ${prefix}/share/moldeo/data
modulesdir = ${libdir}/moldeo
docdir = ${prefix}/share/doc/moldeodirector
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

dist_doc_DATA = README

AM_CPPFLAGS = -DDATADIR=\"$(datadir)\" -DMODULESDIR=\"$(modulesdir)\"

