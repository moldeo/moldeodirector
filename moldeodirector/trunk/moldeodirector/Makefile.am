ACLOCAL_AMFLAGS=-I m4
AM_CPPFLAGS = $(all_includes)

bin_PROGRAMS = moldeodirector

moldeodirector_SOURCES = \
	HtmlPanel.cpp			   moIDirectorActions.cpp \
	mo3dModelPanel.cpp		   moldeodirectorApp.cpp \
	moColorMotion.cpp		   moldeodirector.cpp \
	moConfigurationAdvancedOutput.cpp  moldeodirectorMain.cpp \
	moConfigurationDialog.cpp	   moMobConfig.cpp \
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
	moEffectConfig.cpp		   moShaderCtrl.cpp \
	moEffectLayerCtrl.cpp		   moShadersPanel.cpp \
	moFilesbook.cpp			   moTextureItemCtrl.cpp \
	moFontPanel.cpp			   moTimelineRuler.cpp \
	moFunctionPanel.cpp		   moTreeObjectsLayerCtrl.cpp \
	moGLCanvas.cpp			   moValueCtrl.cpp

moldeodirector_CPPFLAGS = -I /usr/local/include/libmoldeo \
	${WX_CFLAGS} \
	${LUA51_CFLAGS} \
	${FT2_CFLAGS} \
	${GST_CFLAGS}

moldeodirector_LIBS = ${WX_LIBS}

