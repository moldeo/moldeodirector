/*******************************************************************************

                                moDirectorFrame.h

  ****************************************************************************
  *                                                                          *
  *   This source is free software; you can redistribute it and/or modify    *
  *   it under the terms of the GNU General Public License as published by   *
  *   the Free Software Foundation; either version 2 of the License, or      *
  *  (at your option) any later version.                                    *
  *                                                                          *
  *   This code is distributed in the hope that it will be useful, but       *
  *   WITHOUT ANY WARRANTY; without even the implied warranty of             *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
  *   General Public License for more details.                               *
  *                                                                          *
  *   A copy of the GNU General Public License is available on the World     *
  *   Wide Web at <http://www.gnu.org/copyleft/gpl.html>. You can also       *
  *   obtain it by writing to the Free Software Foundation,                  *
  *   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         *
  *                                                                          *
  ****************************************************************************

  Copyright(C) 2006 Fabricio Costa

  Authors:
  Fabricio Costa
  Andrés Colubri

  Description:
	principal frame

*******************************************************************************/
#ifndef _MO_DIRECTOR_FRAME_
#define _MO_DIRECTOR_FRAME_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "moProjectTreeCtrl.h"
#include "vdtc/virtualdirtreectrl.h"
#include "treemultictrl/wxTreeMultiCtrl.h"
#include "moFilesbook.h"
#include "moDirectorCore.h"
#include "moDirectorChildFrame.h"
#include "moDirectorStartFrame.h"

#include "moObjectMotion.h"
#include "moColorMotion.h"
#include "moPanelTexture.h"
#include "moFunctionPanel.h"
#include "moPreviewWindow.h"
#include "moPreviewFrame.h"
#include "moShadersPanel.h"
#include "mo3dModelPanel.h"

#include "moScriptPanel.h"

#include "moConfigurationDialog.h"

#include "moEffectLayerCtrl.h"
#include "moTreeObjectsLayerCtrl.h"
#include "moConnectionsWindow.h"

#include <wx/aui/auibook.h>

class moFilesbook;

class moTabArt : public wxAuiTabArt {

    public:

        moTabArt() : wxAuiTabArt() {
        }
        virtual ~moTabArt() {
        }


};


class moDataNotebook : public wxAuiNotebook {

	public:

		moDataNotebook( wxWindow* parent, wxWindowID id );
		virtual ~moDataNotebook() {}

    wxVirtualDirTreeCtrl*	m_pVirtualDirTreeCtrl;
    moProjectTreeCtrl*      m_pProjectTreeCtrl;
    moProjectTreeCtrl*      m_pIODevicesTreeCtrl;
    moProjectTreeCtrl*      m_pResourcesTreeCtrl;
	wxTextCtrl*			    m_pLogTextCtrl;

};

// Define a new frame type: this is going to be our main frame
class moDirectorFrame : public wxFrame, public moIDirectorActions
{

public:
    // ctor(s)
    moDirectorFrame(const wxString& title);
	virtual ~moDirectorFrame();
	MOboolean Init();
	MOboolean Finish();

    void CreateGUINotebook();
    void CreateDataBook();
    void CreateFilesBook();
    void CreateGLWindows();
    void CreateProjectPanel();
    void CreateLayerControls();
    void CreateInspector();

	void SetDirectorCore( moDirectorCore* p_pDirectorCore );
    void SetIODeviceManager( wxEvtHandler*  m_pEventHandler );

	wxGLContext*    GetGLContext();
	moGLCanvas*     GetGLCanvas();

	void CreateGLContext();

    // event handlers(these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
    void OnEditPreferences(wxCommandEvent& event);

	void OnNewEffect( wxCommandEvent& event );
	void OnImportMob( wxCommandEvent& event );

	void OnNewProject( wxCommandEvent& event );
	void OnOpenProject( wxCommandEvent& event );
	void OnCloseProject( wxCommandEvent& event );
	void OnSaveProject( wxCommandEvent& event );

    // Examples submenu
	void OnExampleSimple( wxCommandEvent& event );
	void OnExampleCamera( wxCommandEvent& event );
	void OnExampleInteractiveCamera( wxCommandEvent& event );
	void OnExampleInteractiveCameraGPU( wxCommandEvent& event );
	void OnExampleInteractiveCameraGPUKLT2( wxCommandEvent& event );
	void OnExampleCameraCircularBuffer( wxCommandEvent& event );
    // End examples submenu
	void OnProjectPreview( wxCommandEvent& event );
	void OnProjectPreviewFullscreen( wxCommandEvent& event );
	void OnFullscreen( wxCommandEvent& event );

	void OnConfiguration( wxCommandEvent& event );

    void OnOpenMob( wxCommandEvent& event );
	void OnSaveMob( wxCommandEvent& event );
	void OnCloseMob( wxCommandEvent& event );

	void OnSaveAll( wxCommandEvent& event );
	void OnCloseAll( wxCommandEvent& event );

	void OnKeyDown( wxKeyEvent &event );
	void OnCommand( wxCommandEvent &event );

	moDirectorChildFrame* CreateChildFrame( moMobDescriptor p_MobDescriptor );

    void    Inspect( moValueDescriptor  p_ValueDescriptor, bool setselection = false  );
    void    Inspect( moMobDescriptor  p_MobDescriptor );


public:

    moDirectorStatus FullScreen(bool force=false);
    moDirectorStatus ProjectPreview();
    void ViewSwapBuffers();
    MO_HANDLE   GetHandle();

	moDirectorStatus FocusOutput();

	//DIRECTOR ACTIONS INTERFACE METHODS
	moDirectorStatus OpenMob( moMobDescriptor p_MobDescriptor );
	moDirectorStatus EditMob( moMobDescriptor p_MobDescriptor );
	moDirectorStatus CloseMob( moMobDescriptor p_MobDescriptor );
	moDirectorStatus SaveMob( moMobDescriptor p_MobDescriptor );
    moDirectorStatus CloseAll();
    moDirectorStatus SaveAll();
    moDirectorStatus CloseProject();

	moDirectorStatus ProjectUpdated( moProjectDescriptor p_ProjectDescriptor );


//PARAMETERS
	moDirectorStatus ParameterUpdated( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus EditParameter( moParameterDescriptor p_ParameterDesc );

//VALUES
    moDirectorStatus EditValue( moValueDescriptor p_ValueDesc );
    moDirectorStatus ValueUpdated( moValueDescriptor p_ValueDesc );

	void Log( moText p_message );
	void LogError( moText p_message );

//SHOW TIP
//    virtual void ShowTip();

private:

	wxPanel* CreatePanel();
	wxTextCtrl* CreateTextCtrl();
	moGLCanvas* CreateGLCanvas();

	//FILESBOOK
	moDirectorCore* m_pDirectorCore;

	moGLCanvas* m_pGLCanvas;
	wxGLContext* m_pGLContext;
	wxGLCanvas* m_pBaseGLCanvas;

    #ifdef WXART2D
    moConnectionsWindow* m_pConnectionsWindow;
    #endif
	moPreviewWindow* m_pPreviewWindow;

	moPreviewFrame* m_pPreviewFrame;

	moLayersPanelCtrl  *m_pLayersPanelCtrl;

	moDataNotebook*		m_pDataNotebook;
	wxAuiNotebook*      m_pGUINotebook;

	wxPanel*			m_pLog;
	wxPanel*			m_pInspector;

	moTreeLayerCtrl*			m_pLayers;
	moTreeLayerCtrl*			m_pLayers2;

	wxTreeMultiItem				m_preeffectsid,m_preeffectsid2;
	wxTreeMultiItem				m_effectsid, m_effectsid2;
	wxTreeMultiItem				m_posteffectsid,m_posteffectsid2;

    /** Inspector pages
    */
	wxAuiNotebook*          m_pInspectorNotebook;
	moObjectMotion*         m_pObjectMotion;
	moPanelTexture*         m_pPanelTexture;
	moColorMotion*          m_pColorMotion;
	moFunctionPanel*        m_pFunctionPanel;
	moShadersPanel*         m_pShadersPanel;
	mo3dModelPanel*         m_p3dModelPanel;

	moScriptPanel*          m_pScriptPanel;

	wxTextCtrl*			    m_pLogTextCtrl;

	moFilesbook*             m_pFilesBook;

	wxAuiManager FrameManager;

	wxList		m_pChildFrameList;
	moDirectorStartFrame*   m_pStartFrame;

    wxColour    m_cForeground;
    wxColour    m_cBackground;

    void OnEraseBackground(wxEraseEvent& event);
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};


// IDs for the controls and the menu commands
enum
{
    // menu items
    MODIRECTOR_QUIT = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    //(where it is special and put into the "Apple" menu)
    MODIRECTOR_ABOUT = wxID_ABOUT,
	MODIRECTOR_NEWPROJECT = 9913,
	MODIRECTOR_OPENPROJECT = 9914,
	MODIRECTOR_CLOSEPROJECT = 9915,
	MODIRECTOR_SAVEPROJECT = 9916,

    MODIRECTOR_EXAMPLES = 9917,

	MODIRECTOR_NEWPREEFFECT = 9926,
	MODIRECTOR_NEWEFFECT = 9927,
	MODIRECTOR_NEWPOSTEFFECT = 9928,
	MODIRECTOR_NEWIODEVICE = 9929,
	MODIRECTOR_NEWRESOURCE = 9930,

	MODIRECTOR_SAVEMOB = 9940,
	MODIRECTOR_SAVEALL = 9941,
	MODIRECTOR_CLOSEMOB = 9942,
	MODIRECTOR_CLOSEALL = 9943,
	MODIRECTOR_OPENMOB = 9944,
	MODIRECTOR_IMPORTMOB = 9945,

    MODIRECTOR_PREFERENCES = 9960,

	MODIRECTOR_PROJECT_PREVIEW = 9980,
	MODIRECTOR_PROJECT_PREVIEW_FULLSCREEN = 9981,
	MODIRECTOR_FULLSCREEN = 9982,
	MODIRECTOR_CONFIGURATION = 9983,
	MODIRECTOR_LOG = 9984,
	MODIRECTOR_COMMAND = 9990,

	MODIRECTOR_EXAMPLE_SIMPLE = 10010,
    MODIRECTOR_EXAMPLE_CAMERA = 10020,
	MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA = 10030,
    MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU = 10040,
    MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU_KLT2 = 10050,
    MODIRECTOR_EXAMPLE_CAMERA_CIRCULAR_BUFFER = 10060

};

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT, -1)


#include "moFilesbook.h"

#endif

