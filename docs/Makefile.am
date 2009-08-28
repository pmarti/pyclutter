NULL =

BUILDDIR = $(top_builddir)/docs

REF_VERSION  = $(PYCLUTTER_MAJOR_VERSION).$(PYCLUTTER_MINOR_VERSION)
FULL_VERSION = $(REF_VERSION).$(PYCLUTTER_MICRO_VERSION)

HTML_STYLE = @PYGOBJECT_DATADIR@/pygobject/xsl/ref-html-style.xsl
PDF_STYLE  = @PYGOBJECT_DATADIR@/pygobject/xsl/pdf-style.xsl

XMLFILES = 						\
    reference/clutter-ref.xml				\
    reference/clutter-overview.xml			\
    reference/clutter-clutteractorbox.xml		\
    reference/clutter-clutteractor.xml			\
    reference/clutter-clutteralpha.xml			\
    reference/clutter-clutterbackend.xml		\
    reference/clutter-clutterbehaviourdepth.xml		\
    reference/clutter-clutterbehaviourellipse.xml	\
    reference/clutter-clutterbehaviouropacity.xml	\
    reference/clutter-clutterbehaviourpath.xml		\
    reference/clutter-clutterbehaviourrotate.xml	\
    reference/clutter-clutterbehaviourscale.xml		\
    reference/clutter-clutterbehaviour.xml		\
    reference/clutter-clutterchildmeta.xml		\
    reference/clutter-clutterclonetexture.xml		\
    reference/clutter-cluttercolor.xml			\
    reference/clutter-cluttercontainer.xml		\
    reference/clutter-cluttergroup.xml			\
    reference/clutter-cluttereffecttemplate.xml		\
    reference/clutter-clutterevent.xml			\
    reference/clutter-cluttergeometry.xml		\
    reference/clutter-cluttergroup.xml			\
    reference/clutter-clutterknot.xml			\
    reference/clutter-clutterlistmodel.xml		\
    reference/clutter-cluttermedia.xml			\
    reference/clutter-cluttermodeliter.xml		\
    reference/clutter-cluttermodel.xml			\
    reference/clutter-clutterrectangle.xml		\
    reference/clutter-clutterscore.xml			\
    reference/clutter-clutterscriptable.xml		\
    reference/clutter-clutterscript.xml			\
    reference/clutter-cluttershader.xml			\
    reference/clutter-clutterstage.xml			\
    reference/clutter-cluttertexture.xml		\
    reference/clutter-cluttertext.xml			\
    reference/clutter-cluttertimeline.xml		\
    reference/clutter-cluttervertex.xml 		\
    $(NULL)

HTML_FILES =					\
	html/*.html				\
	html/index.sgml				\
	html/pyclutter.devhelp

CSS_FILES = @PYGOBJECT_PYGDOCS@/style.css

TARGET_DIR = $(datadir)/gtk-doc/html/pyclutter
CSSdir = $(TARGET_DIR)
CSS_DATA = style.css

style.css:
	@cp -f $(CSS_FILES) $@

CLEANFILES = $(CSS_DATA)

EXTRA_DIST = \
	$(HTML_FILES)	\
	$(XMLFILES)	\
	$(XSLFILES)	
	$(NULL)

install-data-local:
	installfiles=`echo $(top_srcdir)/docs/html/*`; \
	if test "$$installfiles" = '$(top_srcdir)/docs/html/*'; \
	then echo '-- Nothing to install' ; \
	else \
	  $(mkinstalldirs) $(DESTDIR)$(TARGET_DIR); \
	  for i in $$installfiles; do \
	    echo '-- Installing '$$i ; \
	    $(INSTALL_DATA) $$i $(DESTDIR)$(TARGET_DIR); \
	  done; \
	  echo '-- Installing $(srcdir)/html/index.sgml' ; \
	  $(INSTALL_DATA) $(srcdir)/html/index.sgml $(DESTDIR)$(TARGET_DIR) || :; \
	fi

install-data-hook:
	@$(PYGOBJECT_FIXXREF) -i $(PYGOBJECT_PYGDOCS) $(DESTDIR)$(TARGET_DIR)

uninstall-local:
	rm -rf $(DESTDIR)$(TARGET_DIR)/*

if ENABLE_DOCS

BUILT_SOURCES = reference/builddate.xml $(HTML_FILES)
DISTCLEANFILES = reference/builddate.xml $(HTML_FILES)

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c 'import datetime; print datetime.date.today()' > $@

$(HTML_FILES): $(XMLFILES) $(XSLFILES)
	xsltproc --nonet --xinclude -o $(BUILDDIR)/html/ \
		--path $(BUILDDIR)/reference:$(srcdir)/reference \
		--stringparam gtkdoc.bookname "pyclutter" \
		--stringparam gtkdoc.version ${REF_VERSION} \
		$(HTML_STYLE) \
	$(srcdir)/reference/clutter-ref.xml

#pdf: reference/builddate.xml
#	xsltproc \
#		--nonet \
#		--xinclude \
#		-o pyclutter-ref.fo \
#	$(PDF_STYLE) reference/clutter-ref.xml \
#	&& pdfxmltex pyclutter-ref.fo > output < /dev/null

endif
