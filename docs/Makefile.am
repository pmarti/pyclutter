NULL =

BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(PYCLUTTER_MAJOR_VERSION).$(PYCLUTTER_MINOR_VERSION)
FULL_VERSION = $(REF_VERSION).$(PYCLUTTER_MICRO_VERSION)

HTML_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/ref-html-style.xsl
PDF_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/pdf-style.xsl

XMLFILES = 					\
    reference/clutter-ref.xml			\
    reference/clutter-overview.xml		\
    reference/clutter-clutteractor.xml		\
    reference/clutter-cluttercolor.xml		\
    reference/clutter-cluttercontainer.xml	\
    reference/clutter-cluttergroup.xml		\
    reference/clutter-clutterrectangle.xml	\
    reference/clutter-cluttertexture.xml	\
    $(NULL)

HTMLdir = $(datadir)/gtk-doc/html/pyclutter-$(REF_VERSION)
HTML_DATA =					\
	html/index.html				\
	html/index.sgml				\
	html/pt01.html 				\
	html/pt02.html 				\
	html/pt03.html 				\
	html/pt04.html 				\
	html/ch01.html 				\
	html/ch02.html 				\
	html/class-clutteractor.html		\
	html/class-cluttercolor.html		\
	html/class-cluttercontainer.html	\
	html/class-cluttergroup.html		\
	html/class-clutterrectangle.html	\
	html/class-cluttertexture.html		\
	html/pyclutter.devhelp

CSS_FILES = $(PYGOBJECT_PYGDOCS)/style.css
CSSdir = $(HTMLdir)
CSS_DATA = $(CSS_FILES)

BUILT_SOURCES = 		\
	build_stamp 		\
	reference/builddate.xml	\
	$(HTML_DATA)

CLEANFILES = 			\
	build_stamp 		\
	clutter-ref.*		\
	reference/builddate.xml	\
	$(HTML_DATA)

EXTRA_DIST = 		\
	$(XMLFILES) 	\
	$(XSLFILES)	\
	$(FIX_XREF)

REFERENCE_DEPS = 	\
	reference 	\
	$(XMLFILES)	\
	$(XSLFILES)

$(HTML_DATA): build_stamp

if ENABLE_DOCS

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c 'import datetime; print datetime.date.today()' > $@

build_stamp: reference/builddate.xml
	xsltproc --nonet --xinclude -o $(BUILDDIR)/html/ \
		--path $(BUILDDIR)/reference:$(srcdir)/reference \
		--stringparam gtkdoc.bookname "pyclutter" \
		--stringparam gtkdoc.version ${REF_VERSION} \
		$(HTML_STYLE) \
	$(srcdir)/reference/clutter-ref.xml \
	&& $(PYGOBJECT_FIXXREF) -i $(PYGOBJECT_PYGDOCS) $(BUILDDIR)/html \
	&& touch $@

pdf: reference/builddate.xml
	xsltproc \
		--nonet \
		--xinclude \
		-o pyclutter-ref.fo \
	$(PDF_STYLE) reference/clutter-ref.xml \
	&& pdfxmltex pyclutter-ref.fo > output < /dev/null

endif
