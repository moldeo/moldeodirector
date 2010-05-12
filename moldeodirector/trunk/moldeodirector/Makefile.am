ACLOCAL_AMFLAGS=-I m4

datadir = ${prefix}/share/moldeodirector
modulesdir = ${libdir}/moldeo
docdir = ${prefix}/share/doc/moldeodirector
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

AM_CPPFLAGS = $(all_includes) -DDATADIR=\"$(datadir)\" -DMODULESDIR=\"$(modulesdir)\"
AM_CXXFLAGS = $(all_includes) -DDATADIR=\"$(datadir)\" -DMODULESDIR=\"$(modulesdir)\"

bin_PROGRAMS = moldeodirector

moldeodirector_SOURCES = \
	moldeodirector.cpp \
	HtmlPanel.cpp \
	moIDirectorActions.cpp \
	mo3dModelPanel.cpp \
	moConfigurationAdvancedOutput.cpp  moldeodirectorMain.cpp \
	moConfigurationDialog.cpp	   \
	moConfigurationGeneral.cpp	   moNewEffectDialog.cpp \
	moConfigurationOutput.cpp	   moNewProject.cpp \
	moConnectionsWindow.cpp		   moObjectMotion.cpp \
	moDirectorChildConsole.cpp	   moPanelTexture.cpp \
	moDirectorChildFrame.cpp	   moPreviewFrame.cpp \
	moDirectorConsole.cpp		   moPreviewWindow.cpp \
	moDirectorCore.cpp		   moProjectTreeCtrl.cpp \
	moDirectorFrame.cpp		   moResourcesTreeCtrl.cpp \
	moDirectorIODeviceManager.cpp	   moScriptPanel.cpp \
	moDirectorStartFrame.cpp	   moSessionProject.cpp \
	moColorMotion.cpp                  moShaderCtrl.cpp \
	moEffectLayerCtrl.cpp		   moShadersPanel.cpp \
	moFilesbook.cpp			   moTextureItemCtrl.cpp \
	moFontPanel.cpp			   moTimelineRuler.cpp \
	moFunctionPanel.cpp		   moTreeObjectsLayerCtrl.cpp \
	moGLCanvas.cpp			   moValueCtrl.cpp \
	wxMoldeoLineCtrl.cpp               wxMoldeoPinCtrl.cpp \
	wxMoTimelineBandCtrl.cpp           wxMoldeoObjectCanvas.cpp \
	wxMoLevelCtrl.cpp                  wxMoTimelineRulerCtrl.cpp \
	wxMoldeoObjectCtrl.cpp             wxMoRotaryCtrl.cpp \
	treemultictrl/TreeMultiItemBase.cpp  treemultictrl/TreeMultiItemWindow.cpp \
	treemultictrl/TreeMultiItemNode.cpp  treemultictrl/wxTreeMultiCtrl.cpp \
	treemultictrl/TreeMultiItemRoot.cpp  vdtc/virtualdirtreectrl.cpp


# moldeodirectorApp.cpp
# moldeodirector.cpp

moldeodirector_CPPFLAGS = \
	-I ./treemultictrl \
	-I ./vdtc \
	${LIBMOLDEO_CFLAGS} \
	${WX_CFLAGS} 

moldeodirector_LDADD = \
	-lwx_gtk2u_gl-2.8 \
	${LIBMOLDEO_LIBS} \
	${FREEIMAGE_LIBS} \
	${GLEW_LIBS} \
	${GLUT_LIBS} \
	${GLE_LIBS} \
	${CGGL_LIBS} \
	${BOOST_ASIO_LIB} \
	${BOOST_THREAD_LIB} \
	${BOOST_FILESYSTEM_LIB} \
	${WX_LIBS}

