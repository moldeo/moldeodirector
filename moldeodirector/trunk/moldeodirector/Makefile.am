ACLOCAL_AMFLAGS=-I m4

datadir = ${prefix}/share/moldeodirector
modulesdir = ${libdir}/moldeo
docdir = ${prefix}/share/doc/moldeodirector
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

AM_CPPFLAGS = $(all_includes) -DMOLDEODATADIR=\"$(datadir)\" -DMODULESDIR=\"$(modulesdir)\"
AM_CXXFLAGS = $(all_includes) -DMOLDEODATADIR=\"$(datadir)\" -DMODULESDIR=\"$(modulesdir)\"

bin_PROGRAMS = moldeodirector

moldeodirector_SOURCES = \
	HtmlPanel.h \
	mo3dModelPanel.h \
	moAuiTabArt.h \
	moColorMotion.h \
	moConfigurationAdvancedOutput.h \
	moConfigurationDialog.h \
	moConfigurationGeneral.h \
	moConfigurationOutput.h \
	moConnectionsWindow.h \
	moDirectorChildConsole.h \
	moDirectorChildFrame.h \
	moDirectorConsole.h \
	moDirectorCore.h \
	moDirectorFrame.h \
	moDirectorIODeviceManager.h \
	moDirectorStartFrame.h \
	moDirectorTypes.h \
	moEffectsPaletteCtrl.h \
	moExplorerNotebook.h \
	moFilesbook.h \
	moFontPanel.h \
	moFunctionPanel.h \
	moGLCanvas.h \
	moIDirectorActions.h \
	moLayerEffectCtrl.h \
	moLayersPanel.h \
	moLayersTreeCtrl.h \
	moldeodirector.h \
	moLogNotebook.h \
	moNewEffectDialog.h \
	moNewProject.h \
	moObjectMotion.h \
	moPanelTexture.h \
	moPreviewFrame.h \
	moPreviewWindow.h \
	moProjectTreeCtrl.h \
	moResourcesTreeCtrl.h \
	moScriptPanel.h \
	moShaderCtrl.h \
	moShadersPanel.h \
	moTextureItemCtrl.h \
	moTimelineRuler.h \
	moValueCtrl.h \
	moVisualsPaletteCtrl.h \
	PreviewWindowSystemMem.h \
	HtmlPanel.cpp \
	mo3dModelPanel.cpp \
	moColorMotion.cpp \
	moConfigurationAdvancedOutput.cpp \
	moConfigurationDialog.cpp \
	moConfigurationGeneral.cpp \
	moConfigurationOutput.cpp \
	moConnectionsWindow.cpp \
	moDirectorChildConsole.cpp \
	moDirectorChildFrame.cpp \
	moDirectorConsole.cpp \
	moDirectorCore.cpp \
	moDirectorFrame.cpp \
	moDirectorIODeviceManager.cpp \
	moDirectorStartFrame.cpp \
	moEffectsPaletteCtrl.cpp \
	moExplorerNotebook.cpp \
	moFilesbook.cpp \
	moFontPanel.cpp \
	moFunctionPanel.cpp \
	moGLCanvas.cpp \
	moIDirectorActions.cpp \
	moLayerEffectCtrl.cpp \
	moLayersPanel.cpp \
	moLayersTreeCtrl.cpp \
	moldeodirector.cpp \
	moLogNotebook.cpp \
	moNewEffectDialog.cpp \
	moNewProject.cpp \
	moObjectMotion.cpp \
	moPanelTexture.cpp \
	moPreviewFrame.cpp \
	moPreviewWindow.cpp \
	moProjectTreeCtrl.cpp \
	moResourcesTreeCtrl.cpp \
	moScriptPanel.cpp \
	moShaderCtrl.cpp \
	moShadersPanel.cpp \
	moTextureItemCtrl.cpp \
	moTimelineRuler.cpp \
	moValueCtrl.cpp \
	moVisualsPaletteCtrl.cpp \
	PreviewWindowSystemMem.cpp \
	treemultictrl/tmcimages.h \
	treemultictrl/TreeMultiItemBase.h \
	treemultictrl/TreeMultiItemNode.h \
	treemultictrl/TreeMultiItemRoot.h \
	treemultictrl/TreeMultiItemWindow.h \
	treemultictrl/wxTreeMultiCtrl.h \
	treemultictrl/default_checked_icon.xpm \
	treemultictrl/default_collapse.xpm \
	treemultictrl/default_expand.xpm \
	treemultictrl/default_tristate_icon.xpm \
	treemultictrl/default_unchecked_icon.xpm \
	treemultictrl/linux_collapse.xpm \
	treemultictrl/linux_expand.xpm \
	treemultictrl/mac_collapse.xpm \
	treemultictrl/mac_expand.xpm \
	treemultictrl/win_checked_icon.xpm \
	treemultictrl/win_tristate_icon.xpm \
	treemultictrl/win_unchecked_icon.xpm \
	treemultictrl/TreeMultiItemBase.cpp \
	treemultictrl/TreeMultiItemNode.cpp \
	treemultictrl/TreeMultiItemRoot.cpp \
	treemultictrl/TreeMultiItemWindow.cpp \
	treemultictrl/wxTreeMultiCtrl.cpp \
	vdtc/file.xpm \
	vdtc/folder.xpm \
	vdtc/root.xpm \
	vdtc/virtualdirtreectrl.h \
	vdtc/virtualdirtreectrl.cpp

# moldeodirectorApp.cpp
# moldeodirector.cpp

moldeodirector_CPPFLAGS = \
	-I ./treemultictrl \
	-I ./vdtc \
	`pkg-config --cflags gtk+-2.0` \
	${MOLDEOCONTROLS_CFLAGS} \
	${LIBMOLDEO_CFLAGS} \
	${WX_CFLAGS} 

moldeodirector_LDADD = \
	-lwx_gtk2_gl-2.8 \
	${MOLDEOCONTROLS_LIBS} \
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





