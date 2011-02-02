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


  Description:
	principal frame

*******************************************************************************/
#ifndef _MO_DIRECTOR_FRAME_
#define _MO_DIRECTOR_FRAME_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

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

#include "moLayersPanel.h"
#include "moConnectionsWindow.h"
#include "moExplorerNotebook.h"
#include "moLogNotebook.h"
#include "PreviewWindowSystemMem.h"

#include <wx/aui/auibook.h>

class moFilesbook;

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
        void CreateExplorerBook();
        void CreateFilesBook();
        void CreateGLWindows( wxWindow* parent);

        void CreateLayerControls();
        void CreateInspector();
        void CreateLogBook();

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

        void OnExample( wxCommandEvent& event);
        void OnExampleVideoBuffer( wxCommandEvent& event );
        void OnExampleParticles( wxCommandEvent& event );
        void OnExampleParticlesBounce( wxCommandEvent& event );
        void OnExampleParticlesInteractive( wxCommandEvent& event );

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


        ///===========================================
        /// INTERFACE DIRECTOR ACTIONS IMPLEMENTED
        ///===========================================
        virtual moDirectorStatus FullScreen(bool force=false);
        virtual moDirectorStatus ProjectPreview();
        virtual void ViewSwapBuffers();
        virtual MO_HANDLE   GetHandle();

        virtual moDirectorStatus FocusOutput();
        virtual moDirectorStatus OpenMob( moMobDescriptor p_MobDescriptor );
        virtual moDirectorStatus EditMob( moMobDescriptor p_MobDescriptor );
        virtual moDirectorStatus SetMob( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus CloseMob( moMobDescriptor p_MobDescriptor );
        virtual moDirectorStatus SaveMob( moMobDescriptor p_MobDescriptor );
        virtual moDirectorStatus CloseAll();
        virtual moDirectorStatus SaveAll();
        virtual moDirectorStatus CloseProject();

        ///PROJECT
        virtual moDirectorStatus ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );

        ///MOB
        virtual moDirectorStatus  MobUpdated( moMobDescriptor p_MobDesc );

        ///PARAMETERS
        virtual moDirectorStatus ParameterUpdated( moParameterDescriptor p_ParameterDesc );
        virtual moDirectorStatus EditParameter( moParameterDescriptor p_ParameterDesc );

        ///VALUES
        virtual moDirectorStatus  EditValue( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus  ValueUpdated( moValueDescriptor p_ValueDesc );

        virtual void Log( moText p_message );
        virtual void LogError( moText p_message );

        ///SHOW TIP
        ///    virtual void ShowTip();

private:

        /**
        *
        *   CORE ?
        *
        */
        moDirectorCore* m_pDirectorCore;

        moDirectory   m_SamplesDirectory;
        moFileArray   m_SampleProjects;


        /**
        *
        *   GL CANVAS CREATION
        *
        */
        moGLCanvas* CreateGLCanvas();
        moGLCanvas* m_pGLCanvas;
        wxGLContext* m_pGLContext;
        wxGLCanvas* m_pBaseGLCanvas;

        /**
        *
        *   CONNECTION WINDOWS
        *
        */
        #ifdef WXART2D
        moConnectionsWindow* m_pConnectionsWindow;
        #endif

        /**
        * ventana de Preview
        */

        moPreviewWindow* m_pPreviewWindow;
        PreviewWindowSystemMem* m_pPreviewWindowSys;

        /**
        * Cuadro de Preview
        */

        moPreviewFrame* m_pPreviewFrame;

        /**
        * Libro de exploracion
        */
        moExplorerNotebook*		m_pExplorerNotebook;

        /**
        * Panel de capas ( y control de efectos )
        */
        moLayersPanelCtrl  *m_pLayersPanelCtrl;

        wxAuiNotebook*      m_pGUINotebook;


        /**
        * Libro de registro de salida
        */
        moLogNotebook*          m_pLogBook;

        /**
        * Libro de inspectores
        */
        wxAuiNotebook*          m_pInspectorNotebook;

        /**
        * Inspectores (de valores)
        */
        moObjectMotion*         m_pObjectMotion;
        moPanelTexture*         m_pPanelTexture;
        moColorMotion*          m_pColorMotion;
        moFunctionPanel*        m_pFunctionPanel;
        moShadersPanel*         m_pShadersPanel;
        mo3dModelPanel*         m_p3dModelPanel;
        moScriptPanel*          m_pScriptPanel;

        /**
        * Libro de sub-ventana de parametros
        * @see moDirectorChildFrame
        */
        moFilesbook*             m_pFilesBook;


        /**
        * Administrador de ventana wxAUI
        * @see wxAuiManager
        */
        wxAuiManager FrameManager;

        /**
        * Lista de sub-ventanas
        * @see wxList
        * @see moDirectorChildFrame
        */
        wxList		m_pChildFrameList;

        /**
        * Cuadro de impresión html para el inicio de la aplicación
        * @see moDirectorStartFrame
        */
        moDirectorStartFrame*   m_pStartFrame;


        /**
        * COLORES PREDEFINIDOS
        */

        wxColour    m_cForeground;
        wxColour    m_cBackground;

        void OnEraseBackground(wxEraseEvent& event);
        void OnSize(wxSizeEvent& event);

        MOuchar *PreviewBits;
        MOuint PreviewBitsW,PreviewBitsH;
        wxImage* pImgPreviewBits;
        wxBitmap*  pBmpPreviewBits;

        DECLARE_EVENT_TABLE()

};

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT, -1)


#include "moFilesbook.h"

#endif

