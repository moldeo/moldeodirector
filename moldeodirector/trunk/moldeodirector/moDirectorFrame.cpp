#include "moDirectorFrame.h"

#include "moNewProject.h"
#include "moNewEffectDialog.h"

#include <wx/display.h>
#include "wx/tipdlg.h"

DEFINE_EVENT_TYPE(wxEVT_MY_EVENT)


moDataNotebook::moDataNotebook( wxWindow* parent, wxWindowID id ) :
		wxAuiNotebook(parent, id, wxPoint(0,0), wxSize(100,100),  wxBORDER_NONE | wxAUI_NB_TAB_SPLIT | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TAB_MOVE ),
		m_pVirtualDirTreeCtrl(NULL),
		m_pProjectTreeCtrl(NULL),
		m_pIODevicesTreeCtrl(NULL),
		m_pResourcesTreeCtrl(NULL) {


}

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions(event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(moDirectorFrame, wxFrame)
	EVT_MENU( MODIRECTOR_NEWEFFECT, moDirectorFrame::OnNewEffect )
	EVT_MENU( MODIRECTOR_NEWPREEFFECT, moDirectorFrame::OnNewEffect )
	EVT_MENU( MODIRECTOR_NEWPOSTEFFECT, moDirectorFrame::OnNewEffect )
	EVT_MENU( MODIRECTOR_NEWIODEVICE, moDirectorFrame::OnNewEffect )
	EVT_MENU( MODIRECTOR_NEWRESOURCE, moDirectorFrame::OnNewEffect )

    EVT_MENU( MODIRECTOR_NEWPROJECT, moDirectorFrame::OnNewProject )
    EVT_MENU( MODIRECTOR_OPENPROJECT, moDirectorFrame::OnOpenProject )
	EVT_MENU( MODIRECTOR_CLOSEPROJECT, moDirectorFrame::OnCloseProject )
	EVT_MENU( MODIRECTOR_SAVEPROJECT, moDirectorFrame::OnSaveProject )

// Examples Submenu
	EVT_MENU( MODIRECTOR_EXAMPLE_SIMPLE, moDirectorFrame::OnExampleSimple )
	EVT_MENU( MODIRECTOR_EXAMPLE_CAMERA, moDirectorFrame::OnExampleCamera )
	EVT_MENU( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA, moDirectorFrame::OnExampleInteractiveCamera )
	EVT_MENU( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU, moDirectorFrame::OnExampleInteractiveCameraGPU )
	EVT_MENU( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU_KLT2, moDirectorFrame::OnExampleInteractiveCameraGPUKLT2 )
	EVT_MENU( MODIRECTOR_EXAMPLE_CAMERA_CIRCULAR_BUFFER, moDirectorFrame::OnExampleCameraCircularBuffer )

// End Examples Submenu


	EVT_MENU( MODIRECTOR_SAVEMOB, moDirectorFrame::OnSaveMob )
	EVT_MENU( MODIRECTOR_CLOSEMOB, moDirectorFrame::OnCloseMob )
	EVT_MENU( MODIRECTOR_OPENMOB, moDirectorFrame::OnOpenMob )
	EVT_MENU( MODIRECTOR_IMPORTMOB, moDirectorFrame::OnImportMob )

	EVT_MENU( MODIRECTOR_SAVEALL, moDirectorFrame::OnSaveAll )
	EVT_MENU( MODIRECTOR_CLOSEALL, moDirectorFrame::OnCloseAll )

	EVT_MENU( MODIRECTOR_QUIT,  moDirectorFrame::OnQuit )
    EVT_MENU( MODIRECTOR_ABOUT, moDirectorFrame::OnAbout )

    EVT_MENU( MODIRECTOR_PREFERENCES, moDirectorFrame::OnEditPreferences )

	EVT_MENU( MODIRECTOR_PROJECT_PREVIEW, moDirectorFrame::OnProjectPreview )
	EVT_MENU( MODIRECTOR_PROJECT_PREVIEW_FULLSCREEN, moDirectorFrame::OnProjectPreviewFullscreen )
	EVT_MENU( MODIRECTOR_FULLSCREEN, moDirectorFrame::OnFullscreen )
	EVT_MENU( MODIRECTOR_CONFIGURATION, moDirectorFrame::OnConfiguration )

	EVT_KEY_DOWN( moDirectorFrame::OnKeyDown )
	//EVT_COMMAND( -1, MODIRECTOR_COMMAND, moDirectorFrame::OnCommand)
	//EVT_NOTIFY(event, MODIRECTOR_NOTIFY, moDirectorFrame::OnNotify)
	EVT_CLOSE( moDirectorFrame::OnClose )

	EVT_COMMAND  (wxID_ANY, wxEVT_MY_EVENT, moDirectorFrame::OnCommand)

END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------


// frame constructor
moDirectorFrame::moDirectorFrame(const wxString& title)

{
    wxDisplay thisDisplay(0);
    wxDisplay theOtherDisplay(1);

    thisDisplay.GetFromWindow(this);

    wxRect client = thisDisplay.GetClientArea();
    wxRect client2 = theOtherDisplay.GetClientArea();

    wxString clientareastr;
    wxString clientareastr2;

    clientareastr.Printf(_(" area: %d,%d,%d,%d"), client.GetLeft(), client.GetTop(), client.GetWidth(), client.GetHeight() );
    clientareastr2.Printf(_(" area: %d,%d,%d,%d"), client2.GetLeft(), client2.GetTop(), client2.GetWidth(), client2.GetHeight() );

   //wxMessageBox(thisDisplay.GetName() + clientareastr);
   //wxMessageBox(theOtherDisplay.GetName() + clientareastr2 );
    wxFrame::Create(NULL, wxID_ANY, title, wxPoint(0,0), wxSize(1024,768));

    m_cForeground = wxColour(255,255,255);
    m_cBackground = wxColour(0,0,0);

    // set the frame icon
    //SetIcon(wxICON(sample));

	FrameManager.SetManagedWindow(this);

#if wxUSE_MENUS
    // create a menu bar

	//FILE
    wxMenu *fileMenu = new wxMenu;

	wxMenuItem *preeffectsMenuItem = NULL;
	wxMenu *preeffectsMenu = new wxMenu;

	wxMenu *effectsMenu = new wxMenu;
	wxMenu *posteffectsMenu = new wxMenu;
	wxMenu *iodevicesMenu = new wxMenu;
	wxMenu *parameterMenu = new wxMenu;

	//Examples Menu
	wxMenu *examplesMenu = new wxMenu;
	examplesMenu->Append( MODIRECTOR_EXAMPLE_SIMPLE, _T("Simple Project"), _T("Simple Moldeo project"));
	examplesMenu->Append( MODIRECTOR_EXAMPLE_CAMERA, _T("Cameras"), _T("Simple cameras project"));
	examplesMenu->Append( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA, _T("Interactive Cameras"), _T("Simple cameras with tracking project"));
	examplesMenu->Append( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU, _T("Interactive Cameras GPU"), _T("Simple cameras with tracking project"));
	examplesMenu->Append( MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU_KLT2, _T("Interactive Cameras GPU KLT2"), _T("Simple cameras with tracking project"));
	examplesMenu->Append( MODIRECTOR_EXAMPLE_CAMERA_CIRCULAR_BUFFER, _T("Camera with Circular Buffer"), _T("Simple cameras with tracking project"));

	//File Menu

	fileMenu->Append( MODIRECTOR_NEWPROJECT, _T("&New Project\tAlt-N"), _T("Create a new project"));
	fileMenu->Append( MODIRECTOR_OPENPROJECT, _T("&Open Project\tAlt-O"), _T("Open an existing project"));
	fileMenu->Append( MODIRECTOR_CLOSEPROJECT, _T("&Close Project"), _T("Close the current project"));
	fileMenu->Append( MODIRECTOR_CLOSEMOB, _T("&Close Mob"), _T("Close the current mob file"));

    fileMenu->AppendSeparator();
    fileMenu->AppendSubMenu( examplesMenu, _T("Examples"), _T("Moldeo sample projects"));

    fileMenu->AppendSeparator();
    fileMenu->Append( MODIRECTOR_SAVEPROJECT, _T("Save Project\tCtrl-S"), _T("Save the current project"));
    fileMenu->Append( MODIRECTOR_SAVEMOB, _T("Save Object\tAlt-S"), _T("Save the current object"));
    fileMenu->Append( MODIRECTOR_SAVEALL, _T("Save All\tCtrl-A"), _T("Save All"));

	fileMenu->AppendSeparator();
    fileMenu->Append(MODIRECTOR_NEWPREEFFECT, _T("Add P&reEffect\tAlt-W"), _T("Add a new pre-effect"));
	fileMenu->Append(MODIRECTOR_NEWEFFECT, _T("Add &Effect\tAlt-E"), _T("Add a new effect"));
	fileMenu->Append(MODIRECTOR_NEWPOSTEFFECT, _T("Add P&ostEffect\tAlt-R"), _T("Add a new post-effect"));
    fileMenu->Append(MODIRECTOR_IMPORTMOB, _T("Import &Moldeo Object from config file\tAlt-E"), _T("Import Mob"));

    fileMenu->AppendSeparator();
    fileMenu->Append(MODIRECTOR_NEWIODEVICE, _T("Add IODevice"), _T("Add IODevice"));
	fileMenu->Append(MODIRECTOR_NEWRESOURCE, _T("Add Resource"), _T("Add Resource"));


	fileMenu->Append(MODIRECTOR_QUIT, _T("E&xit\tAlt-X"), _T("Quit this program"));
	//EDIT
	wxMenu *editMenu = new wxMenu;
    editMenu->AppendSeparator();
    editMenu->Append( MODIRECTOR_PREFERENCES, _T("Prefere&nces"), _T("Application preferences"));
	//VIEW
	wxMenu *viewMenu = new wxMenu;
	viewMenu->Append( MODIRECTOR_FULLSCREEN, _T("&Interface Fullscreen\tAlt-F11"), _T("Interface Fullscreen"));
	viewMenu->Append( MODIRECTOR_PROJECT_PREVIEW, _T("&Preview\tAlt-P"), _T("View frame preview"));
	viewMenu->Append( MODIRECTOR_PROJECT_PREVIEW_FULLSCREEN, _T("&Toggle Preview Fullscreen\tAlt-Return"), _T("Frame preview fullscreen"));

	//OPTIONS
	wxMenu *optionsMenu = new wxMenu;
	optionsMenu->Append( MODIRECTOR_CONFIGURATION, _T("&Configuration..."), _T("Configuration options..."));


    //HELP
    wxMenu *helpMenu = new wxMenu;

    helpMenu->Append(MODIRECTOR_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));


    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
	menuBar->Append(editMenu, _T("&Edit"));
	menuBar->Append(viewMenu, _T("&View"));
	menuBar->Append(optionsMenu, _T("&Options"));

    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun(by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to Moldeo Director!"));
#endif // wxUSE_STATUSBAR

    CreateDataBook();
    CreateGUINotebook();
    CreateInspector();
    CreateLayerControls();
    CreateProjectPanel();
    CreateFilesBook();


//	m_pLogTextCtrl = CreateTextCtrl();
//	m_pLogTextCtrl->SetForegroundColour(m_cForeground);
//    m_pLogTextCtrl->SetBackgroundColour(m_cBackground);


	FrameManager.AddPane( m_pDataNotebook,      wxAuiPaneInfo().Name(wxT("explorer")).Caption(wxT("Explorer")).CenterPane().Hide().CaptionVisible().Floatable().Movable().Dockable());
	FrameManager.AddPane( m_pFilesBook,         wxAuiPaneInfo().Name(wxT("filesbook")).CenterPane().Hide().Caption(wxT("Parameters")).CaptionVisible().Floatable().Movable().Dockable());
	FrameManager.AddPane( m_pInspectorNotebook, wxAuiPaneInfo().Name(wxT("inspector")).CenterPane().Hide().Caption(wxT("Inspector")).CaptionVisible().Floatable().Movable().Dockable());
	FrameManager.AddPane( m_pLayersPanelCtrl,   wxAuiPaneInfo().Name(wxT("layers")).CenterPane().Hide().Caption(wxT("Layers")).CaptionVisible().Floatable().Movable().Dockable());
//	FrameManager.AddPane( m_pLogTextCtrl,       wxAuiPaneInfo().Name(wxT("log")).CenterPane().Hide().Caption(wxT("Log")).CaptionVisible().Floatable().Movable().Dockable());

	FrameManager.AddPane( m_pGUINotebook, wxAuiPaneInfo().Name(wxT("preview")).Caption(wxT("Console")).CaptionVisible().Floatable().Movable().Dockable().MaximizeButton().MinimizeButton().Resizable(true));

	//LEFT PANE
	FrameManager.GetPane(wxT("explorer")).Show().Left().Layer(1).Row(0).Position(0).MinSize(0,370).BestSize(300,370);


	//CENTER PANE
	FrameManager.GetPane(wxT("preview")).Show().Center().Top().Layer(0).Row(0).Position(0).MinSize(0,370).BestSize(50,370);
	FrameManager.GetPane(wxT("layers")).Show().Center().Top().Layer(0).Row(1).Position(0).MinSize(300,250);
//	FrameManager.GetPane(wxT("log")).Show().Center().Layer(0).Row(2).Position(0).MinSize(300,50).BestSize(300,50);

	//RIGHT PANE
	FrameManager.GetPane(wxT("inspector")).Show().Right().Layer(1).Row(0).Position(0);
	FrameManager.GetPane(wxT("filesbook")).Show().Right().Layer(1).Row(0).Position(1);

    wxAuiDockArt* pFrameArt;

    pFrameArt = FrameManager.GetArtProvider();
    pFrameArt->SetColor( wxAUI_DOCKART_SASH_COLOUR, wxColour(80,80,80) );
    pFrameArt->SetColor( wxAUI_DOCKART_BORDER_COLOUR, wxColour(255,255,255) );
    pFrameArt->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR, wxColour(10,40,120) );
    pFrameArt->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR, wxColour(0,0,0) );
    pFrameArt->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR, wxColour(255,255,255) );
    //pFrameArt->SetColor( wxAUI_DOCKART_SASH_COLOUR, wxColour(255*30/100,255*30/100,255*30/100 );
    //pFrameArt->SetColor( wxAUI_DOCKART_SASH_COLOUR, wxColour(255*30/100,255*30/100,255*30/100 );
    //pFrameArt->SetColor( wxAUI_DOCKART_SASH_COLOUR, wxColour(255*30/100,255*30/100,255*30/100 );
    //moTabArt*   pTabArt = new moTabArt();
    wxAuiTabArt*    pTabArt = m_pInspectorNotebook->GetArtProvider();
    wxFont* pFont = new wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    pTabArt->SetNormalFont(*pFont);

    //m_pInspectorNotebook->SetArtProvider(pTabArt);



	FrameManager.Update();
/*
    int s_index = rand() % 5;
    wxTipProvider *moTipProvider = wxCreateFileTipProvider(wxT("tips.txt"), s_index);
    wxShowTip(this,moTipProvider,true);
    delete moTipProvider;
    */

}

moDirectorFrame::~moDirectorFrame() {

    m_pGLCanvas = NULL;
	FrameManager.UnInit();

}

void
moDirectorFrame::CreateGUINotebook() {

	m_pGUINotebook = new wxAuiNotebook( this, wxID_ANY, wxPoint(0,0), wxSize(300,200), wxBORDER_NONE | wxAUI_NB_TAB_SPLIT | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TAB_MOVE  );
	m_pGUINotebook->SetForegroundColour(m_cForeground);
    m_pGUINotebook->SetBackgroundColour(m_cBackground);

    CreateGLWindows();

    //m_pConnectionsWindow = new moConnectionsWindow(m_pGUINotebook,wxID_ANY, wxPoint(0,0), wxSize(300,200));
    //m_pConnectionsWindow->Init(this);

    m_pGUINotebook->AddPage( m_pPreviewWindow, wxT("Preview"));
    //m_pGUINotebook->AddPage( m_pConnectionsWindow, wxT("Connections"));
}

void
moDirectorFrame::CreateDataBook() {

	m_pDataNotebook = new moDataNotebook( this, wxID_ANY);
	if (m_pDataNotebook) {
		m_pDataNotebook->SetForegroundColour(m_cForeground);
        m_pDataNotebook->SetBackgroundColour(m_cBackground);

        m_pDataNotebook->m_pLogTextCtrl = CreateTextCtrl();
        wxFont* pLogFont = new wxFont( 13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        m_pDataNotebook->m_pLogTextCtrl->SetFont( *pLogFont );
        //m_pDataNotebook->m_pLogTextCtrl->SetInsertionPoint(0);

		m_pDataNotebook->m_pVirtualDirTreeCtrl = new wxVirtualDirTreeCtrl(m_pDataNotebook, wxID_ANY, wxPoint(0,0), wxSize(300,377),wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE );
		m_pDataNotebook->m_pVirtualDirTreeCtrl->SetForegroundColour(m_cForeground);
        m_pDataNotebook->m_pVirtualDirTreeCtrl->SetBackgroundColour(m_cBackground);

		m_pDataNotebook->m_pProjectTreeCtrl = new moProjectTreeCtrl(m_pDataNotebook, wxID_ANY, wxPoint(0,0), wxSize(300,377), wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE);
		m_pDataNotebook->m_pProjectTreeCtrl->SetForegroundColour(m_cForeground);
        m_pDataNotebook->m_pProjectTreeCtrl->SetBackgroundColour(m_cBackground);
		m_pDataNotebook->m_pProjectTreeCtrl->SetDirectorFrame( this );

        m_pDataNotebook->m_pIODevicesTreeCtrl = new moProjectTreeCtrl(m_pDataNotebook, wxID_ANY, wxPoint(0,0), wxSize(300,377), wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE);
		m_pDataNotebook->m_pIODevicesTreeCtrl->SetForegroundColour(m_cForeground);
        m_pDataNotebook->m_pIODevicesTreeCtrl->SetBackgroundColour(m_cBackground);
		m_pDataNotebook->m_pIODevicesTreeCtrl->SetDirectorFrame( this );

        m_pDataNotebook->m_pResourcesTreeCtrl = new moProjectTreeCtrl(m_pDataNotebook, wxID_ANY, wxPoint(0,0), wxSize(300,377), wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE);
		m_pDataNotebook->m_pResourcesTreeCtrl->SetForegroundColour(m_cForeground);
        m_pDataNotebook->m_pResourcesTreeCtrl->SetBackgroundColour(m_cBackground);
		m_pDataNotebook->m_pResourcesTreeCtrl->SetDirectorFrame( this );

		m_pDataNotebook->AddPage( m_pDataNotebook->m_pLogTextCtrl, wxT("Log") );
		m_pDataNotebook->GetPage(0)->SetBackgroundColour(m_cBackground);

		m_pDataNotebook->AddPage( m_pDataNotebook->m_pProjectTreeCtrl, wxT("Project") );
		m_pDataNotebook->GetPage(1)->SetBackgroundColour(m_cBackground);
		m_pDataNotebook->AddPage( m_pDataNotebook->m_pIODevicesTreeCtrl, wxT("IODevices") );
		m_pDataNotebook->GetPage(2)->SetBackgroundColour(m_cBackground);
        m_pDataNotebook->AddPage( m_pDataNotebook->m_pResourcesTreeCtrl, wxT("Resources") );
		m_pDataNotebook->GetPage(3)->SetBackgroundColour(m_cBackground);
		m_pDataNotebook->AddPage( m_pDataNotebook->m_pVirtualDirTreeCtrl, wxT("Data") );
		m_pDataNotebook->GetPage(4)->SetBackgroundColour(m_cBackground);


	}


}

void
moDirectorFrame::CreateFilesBook() {

	m_pFilesBook = NULL;
	m_pFilesBook = new moFilesbook( this, wxID_ANY );

}

void
moDirectorFrame::CreateGLWindows() {

   int attribList[2];
    attribList[0] = WX_GL_RGBA; //true color
    attribList[1] = 0;

    m_pGLContext = NULL;
    //create base wxGLCanvas to create context...
    //retreive context...
    //m_pBaseGLCanvas = (wxGLCanvas*)new moGLCanvas( this, wxID_ANY, &attribList[0], wxPoint(0,0), wxSize(800,600) );
    //m_pGLContext = m_pBaseGLCanvas->GetContext();
    //m_pBaseGLCanvas->Destroy();

    //create preview window, dockable...

	m_pPreviewWindow = NULL;
	m_pPreviewWindow = new moPreviewWindow( m_pGUINotebook, wxID_ANY );

	if (m_pPreviewWindow) {

        m_pPreviewWindow->Init( this, m_pGLContext );
        m_pGLCanvas = m_pPreviewWindow->m_pGLCanvas;
        if (m_pGLCanvas) {
            m_pGLContext = m_pGLCanvas->GetContext();
            m_pGLCanvas->SetCurrent();
        }

	}

	m_pPreviewFrame = NULL;

}

void
moDirectorFrame::CreateProjectPanel() {


}

void
moDirectorFrame::CreateLayerControls() {

	m_pLayers2 = m_pLayers = NULL;
	m_pLayersPanelCtrl = new moLayersPanelCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(440,220), wxSP_NOBORDER | wxNO_BORDER );
	if (m_pLayersPanelCtrl) {
	    m_pLayers = m_pLayersPanelCtrl->m_pLayersTreeCtrl;
	    m_pLayers2 = NULL;
/*
        m_pLayers = new moTreeObjectsLayerCtrl( m_pLayersPanelCtrl, wxID_ANY, wxPoint(0,0), wxSize(150,220) );
        m_pLayers->SetForegroundColour(m_cForeground);
        m_pLayers->SetBackgroundColour( wxColour(0,0,0) );
        m_pLayers->ShowScrollBars( true, false);

        m_pLayers2 = new moTreeObjectsLayerCtrl( m_pLayersPanelCtrl, wxID_ANY );
        m_pLayers2->SetForegroundColour(m_cForeground);
        m_pLayers2->SetBackgroundColour( wxColour(52,52,52) );
        m_pLayers2->ShowScrollBars( true, true);
        m_pLayers2->SetSecondTargetWindow( m_pLayers );
        m_pLayers->SetSecondTargetWindow( m_pLayers2 );
*/
        /*
        m_pLayersPanelCtrl->SplitVertically( m_pLayers, m_pLayers2 );
        m_pLayersPanelCtrl->SetSashPosition( 220, true );
        m_pLayersPanelCtrl->SetForegroundColour(m_cForeground);
        m_pLayersPanelCtrl->SetBackgroundColour( wxColour(52,52,52) );
        */
	}

}


void
moDirectorFrame::CreateInspector() {

	m_pInspectorNotebook = new wxAuiNotebook( this, wxID_ANY, wxPoint(0,0), wxSize(400,300), wxBORDER_NONE | wxAUI_NB_TAB_SPLIT | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TAB_MOVE  );
	m_pInspectorNotebook->SetForegroundColour(m_cForeground);
    m_pInspectorNotebook->SetBackgroundColour(m_cBackground);

    m_pPanelTexture = new moPanelTexture( m_pInspectorNotebook, wxID_ANY );
    m_pPanelTexture->SetNextActionHandler( this );

    m_pObjectMotion = new moObjectMotion( m_pInspectorNotebook, wxID_ANY );
    m_pObjectMotion->SetNextActionHandler( this );

    m_pColorMotion =  new moColorMotion( m_pInspectorNotebook, wxID_ANY );
    m_pColorMotion->SetNextActionHandler( this );

    m_pFunctionPanel =  new moFunctionPanel( m_pInspectorNotebook, wxID_ANY );
    m_pFunctionPanel->SetNextActionHandler( this );

    m_pShadersPanel = new moShadersPanel( m_pInspectorNotebook, wxID_ANY );
    m_pShadersPanel->SetNextActionHandler( this );

    m_p3dModelPanel = new mo3dModelPanel( m_pInspectorNotebook, wxID_ANY );
    m_p3dModelPanel->SetNextActionHandler( this );

    m_pScriptPanel = new moScriptPanel( m_pInspectorNotebook, wxID_ANY );
    m_pScriptPanel->SetNextActionHandler( this );

	m_pInspectorNotebook->AddPage( m_pPanelTexture, wxT("Texture") );
	m_pInspectorNotebook->AddPage( m_pColorMotion , wxT("Color") );
	m_pInspectorNotebook->AddPage( m_pObjectMotion, wxT("Motion") );
	m_pInspectorNotebook->AddPage( m_pFunctionPanel, wxT("Function") );
	m_pInspectorNotebook->AddPage( m_p3dModelPanel , wxT("3d Model") );
	m_pInspectorNotebook->AddPage( m_pShadersPanel , wxT("Shader") );

	m_pInspectorNotebook->AddPage( new wxPanel(m_pInspectorNotebook,wxID_ANY) , wxT("Sound") );
	m_pInspectorNotebook->AddPage( new wxPanel(m_pInspectorNotebook,wxID_ANY) , wxT("Font") );
	m_pInspectorNotebook->AddPage( m_pScriptPanel, wxT("Script") );
	m_pInspectorNotebook->AddPage( new wxTextCtrl(m_pInspectorNotebook,wxID_ANY) , wxT("Text") );


}


//Invocar al DirectorFrame para inspeccionar un valor, se propaga al resto de los parametros del MOB correspondiente
// esto sirve tambien para cuando se hace foco en algun objeto del MOB, si se llama a este, se asegura
// que todos los inspectores seran notificados
void
moDirectorFrame::Inspect( moValueDescriptor  p_ValueDescriptor, bool setselection  ) {

        switch( p_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {
            case MO_PARAM_ALPHA:
            case MO_PARAM_SYNC:
            case MO_PARAM_PHASE:
            case MO_PARAM_FUNCTION:
            case MO_PARAM_NUMERIC:
                // to the function inspector....
                m_pFunctionPanel->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;
            case MO_PARAM_ROTATEX:
            case MO_PARAM_ROTATEY:
            case MO_PARAM_ROTATEZ:
            case MO_PARAM_TRANSLATEX:
            case MO_PARAM_TRANSLATEY:
            case MO_PARAM_TRANSLATEZ:
            case MO_PARAM_SCALEX:
            case MO_PARAM_SCALEY:
            case MO_PARAM_SCALEZ:
                m_pObjectMotion->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;

            case MO_PARAM_COLOR:
                m_pColorMotion->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;

            case MO_PARAM_TEXTURE:
            case MO_PARAM_VIDEO:
                m_pPanelTexture->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;
            case MO_PARAM_OBJECT:
            case MO_PARAM_3DMODEL:
                m_p3dModelPanel->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;
            case MO_PARAM_FILTER:
                m_pShadersPanel->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;
            case MO_PARAM_SCRIPT:
                m_pScriptPanel->Inspect( p_ValueDescriptor );
                if (setselection) m_pInspectorNotebook->SetSelection(0);
                break;

        }

}


void
moDirectorFrame::Inspect( moMobDescriptor  p_MobDescriptor ) {

        moValueDescriptor p_ValueDescriptor;
        moParameterDescriptors mParams;
        moParameterDescriptor mParam;

        mParams = GetParameterDescriptors( p_MobDescriptor );

        for(int i=0; i<(int)mParams.Count(); i++) {

            mParam = mParams[i];

            moValueIndex valindex;
            valindex.m_ParamIndex = mParam.GetIndex();
            valindex.m_ValueIndex = mParam.GetIndexValue();

            p_ValueDescriptor = GetValue( moValueDescriptor( mParams[i], valindex ) );

            Inspect( p_ValueDescriptor );

        }

}


void moDirectorFrame::OnKeyDown( wxKeyEvent &event ) {

	event.Skip();

}

void moDirectorFrame::OnCommand( wxCommandEvent& event ) {

	// do something
	wxString text = event.GetString();
	wxMessageBox(text);
	OnOpenProject(event);

}

void
moDirectorFrame::SetDirectorCore( moDirectorCore* p_pDirectorCore ) {

	m_pDirectorCore = p_pDirectorCore;
	this->SetNextActionHandler( (moIDirectorActions*)m_pDirectorCore );

}

void
moDirectorFrame::SetIODeviceManager( wxEvtHandler*  m_pEventHandler ) {

    if (m_pPreviewFrame)
        if (m_pPreviewFrame->m_pGLCanvas)
         m_pPreviewFrame->m_pGLCanvas->Init( this);
    if (m_pPreviewWindow)
        if (m_pPreviewWindow->m_pGLCanvas)
            m_pPreviewWindow->m_pGLCanvas->Init( this);
}

moGLCanvas*  moDirectorFrame::GetGLCanvas() {
	return m_pGLCanvas;
}

MOboolean
moDirectorFrame::Init() {

    m_pStartFrame = new moDirectorStartFrame( m_pFilesBook );

    if (m_pStartFrame) {
        //m_pStartFrame->Activate();
        m_pFilesBook->AddPage( (wxWindow*) m_pStartFrame, _T("Welcome to Moldeo Director"));

        //m_pFilesBook->AddPage( (wxWindow*) new wxScrolledWindow( this, wxID_ANY), "Welcome to Moldeo Director Dialog");
        //m_pFilesBook->AddPage((wxWindow*)new wxDialog(this,wxID_ANY,"Dialog"), "Welcome to Moldeo Director Dialog");
        //m_pFilesBook->AddPage((wxWindow*)new wxPanel(this,wxID_ANY), "Welcome to Moldeo Director Panel");
        //m_pFilesBook->AddPage((wxWindow*)new wxTextCtrl(this,wxID_ANY), "Welcome to Moldeo Director Control");
        //m_pFilesBook->AddPage(new wxFrame(this,wxID_ANY,"Dialog",wxPoint(0,0), wxSize(100,100),wxFRAME_NO_TASKBAR | wxBORDER_NONE | wxNO_BORDER,"Start frame" ), "Welcome to Moldeo Director Dialog");
        //m_pFilesBook->AddPage(new wxDialog(this,wxID_ANY,"Dialog"), "Welcome to Moldeo Director Dialog");
        //m_pStartFrame->Maximize();
        m_pStartFrame->Init(this);
    }
	return true;
}

MOboolean moDirectorFrame::Finish() {

    m_pGLCanvas = NULL;

	return true;
}


void moDirectorFrame::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

void moDirectorFrame::OnSize(wxSizeEvent& event)
{
    event.Skip();
}

wxPanel* moDirectorFrame::CreatePanel() {

	return new wxPanel(this, -1,
		wxPoint(0,0), wxSize(160,250),wxTAB_TRAVERSAL, _T("panel"));

}


wxTextCtrl* moDirectorFrame::CreateTextCtrl()
{

    return new wxTextCtrl(this,-1, wxT(""),
                          wxPoint(0,0), wxSize(500,90),
                          wxNO_BORDER | wxTE_MULTILINE | wxTE_RICH);
}


void
moDirectorFrame::CreateGLContext() {

	if (m_pGLCanvas)
        m_pGLContext = m_pGLCanvas->GetContext();

}

void moDirectorFrame::OnClose(wxCloseEvent& event) {
	if( wxMessageBox(_T("Really close Moldeo Director?"), _T("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) != wxYES )
    {
        event.Veto();

        return;
    } else {
		if(this->CloseProject()==MO_DIRECTOR_STATUS_OK) {
		    if (this->CloseApp()==MO_DIRECTOR_STATUS_OK) {
                event.Skip();
                return;
		    }
		}
		event.Veto();
	}
}

void moDirectorFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void moDirectorFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of Moldeo Director.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Moldeo Director"), wxOK | wxICON_INFORMATION, this);
}


void
moDirectorFrame::OnNewProject( wxCommandEvent& event ) {

	moNewProject*   pNewProject = new moNewProject( this, -1 );

    if (pNewProject)
	if (pNewProject->ShowModal() == wxID_OK) {

        this->NewProject( pNewProject->GetProjectDescriptor() );

	}

}

//INTERFACE METHODS
void
moDirectorFrame::OnOpenProject(wxCommandEvent& event) {

	wxFileDialog* pFileDialog = NULL;
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	//open browser window
	if ( event.GetString()==_T("") ) {

        pFileDialog = new wxFileDialog( this );

        if(pFileDialog) {

            pFileDialog->SetWildcard(wxT("MOL files (*.mol)|*.mol|All files (*.*)|*.*"));

            if( pFileDialog->ShowModal() == wxID_OK ) {

                wxFileName	FileName( pFileDialog->GetPath() );

                wxString path = FileName.GetPath();
                #ifdef MO_WIN32
                    path+= "\\";
                #else
                    path+= _T("/");
                #endif
                wxString name = FileName.GetFullName();
                const char *cfilepath = (char*)path.c_str();
                const char *cfilename = (char*)name.c_str();

                ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );

                mStatus = OpenProject( ProjectDescriptor );
                SetTitle(wxString(name)+wxString(_(" - Moldeo Director")));

            }

        }

	} else {

	    Log( moText("Direct opening..") + moWx2Text(event.GetString()));

        wxFileName	FileName( event.GetString() );

        wxString path = FileName.GetPath();
        #ifdef MO_WIN32
            path+= "\\";
        #else
            path+= _T("/");
        #endif
        wxString name = FileName.GetFullName();
        const char *cfilepath = (char*)path.c_str();
        const char *cfilename = (char*)name.c_str();

        ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );

        mStatus = OpenProject( ProjectDescriptor );
        SetTitle(wxString(name)+wxString(_(" - Moldeo Director")));


    }

}

void
moDirectorFrame::OnSaveProject(wxCommandEvent& event) {
    SaveProject();
}

void
moDirectorFrame::OnCloseProject(wxCommandEvent& event) {

    wxString tName = moText2Wx( GetProject().GetFullConfigName() );

    int result = wxMessageBox(_T("Save project before close \"")+tName+_T("\" ?"), _T("Please confirm"),
                      wxICON_QUESTION | wxYES_NO | wxCANCEL );
    switch(result) {
        case wxYES:
            //save before closing
            SaveProject();
            CloseProject();
            break;
        case wxNO:
            //do not save project
            CloseProject();
            break;
        case wxCANCEL:
            break;
    }


}

void
moDirectorFrame::OnNewEffect( wxCommandEvent& event ) {

    moNewEffectDialog*  pNewEffectDialog = new moNewEffectDialog( this, -1 );

    pNewEffectDialog->Init( this );

    if( pNewEffectDialog->ShowModal() == wxID_OK ) {

        moMobDefinition pMobDefinition = pNewEffectDialog->GetMobDefinition();

        NewMob( moMobDescriptor( pMobDefinition ) );

    }

}

void
moDirectorFrame::OnImportMob( wxCommandEvent& event ) {

    wxFileDialog* pFileDialog = NULL;
	moMobDescriptor MobDescriptor;
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

    ProjectDescriptor = GetProject();


	//open browser window
	if ( event.GetString()==_T("") ) {

        pFileDialog = new wxFileDialog( this );

        if(pFileDialog) {

            pFileDialog->SetWildcard(wxT("Config files (*.cfg)|*.cfg|All files (*.*)|*.*"));

            if( pFileDialog->ShowModal() == wxID_OK ) {

                wxFileName	FileName( pFileDialog->GetPath() );

                wxString path = FileName.GetPath();
                #ifdef MO_WIN32
                    path+= "\\";
                #else
                    path+= _T("/");
                #endif
                wxString fullpath = FileName.GetFullPath();

                mStatus = ImportMob( moWx2Text(fullpath) );

            }

        }

	} else {

	    Log( moText("Direct importing..") + moWx2Text(event.GetString()));

        wxFileName	FileName( event.GetString() );

        wxString path = FileName.GetPath();
        #ifdef MO_WIN32
            path+= "\\";
        #else
            path+= _T("/");
        #endif
        wxString fullpath = FileName.GetFullPath();

        mStatus = ImportMob( moWx2Text(fullpath) );

    }

}

moDirectorStatus
moDirectorFrame::OpenMob( moMobDescriptor p_MobDescriptor ) {

    moDirectorChildFrame* pChild = NULL;

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
            pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
            if (pChild) {
                if( pChild->IsMob( p_MobDescriptor ) ) {

                    //to avoid innecesary inspections:
                    //check the actual selection
                    //focus and return

                    if (m_pFilesBook->GetSelection()!=i) {
                        m_pFilesBook->SetSelection(i);
                    }

                    //now that we founded it run the iterative Inspector...
                    this->Inspect( p_MobDescriptor );

                    return MO_DIRECTOR_STATUS_CONFIG_ALREADY_OPENED;
                }
            }
        }
    }

    // Never get here if filesbook has the page opened...
    m_pDirectorCore->OpenMob( p_MobDescriptor );
}


void
moDirectorFrame::OnOpenMob( wxCommandEvent& event ) {


}


void
moDirectorFrame::OnSaveMob( wxCommandEvent& event ) {

    //guardar el MOB correspondiente al MOB elegido
    moDirectorChildFrame* pChild = NULL;

    int i = m_pFilesBook->GetSelection();
    if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
        pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
        if (pChild) {
            pChild->Save();
        }
    }

}

void
moDirectorFrame::OnCloseMob( wxCommandEvent& event ) {

    moDirectorChildFrame* pChild = NULL;

    int i = m_pFilesBook->GetSelection();
    if (m_pFilesBook->GetPage(i)->GetName() == _T("child frame") ) {
        pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
        if (pChild) {
            if ( pChild->Close() ) {
                pChild->Destroy();
                m_pFilesBook->RemovePage(i);
            }
        }
    }

}

void
moDirectorFrame::OnSaveAll( wxCommandEvent& event ) {

    this->SaveAll();

}


void
moDirectorFrame::OnCloseAll( wxCommandEvent& event ) {

    this->CloseAll();

}

moDirectorStatus
moDirectorFrame::CloseAll() {

    moDirectorChildFrame* pChild = NULL;

    //int i = m_pFilesBook->GetSelection();
    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
            pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
            if (pChild) {
                if (pChild->Close()) {
                    pChild->Destroy();
                    m_pFilesBook->RemovePage(i);
                    i--;
                } else return MO_DIRECTOR_STATUS_ERROR;
            }
        }
    }
    return MO_DIRECTOR_STATUS_OK;

}

moDirectorStatus
moDirectorFrame::SaveAll() {

    moDirectorChildFrame* pChild = NULL;

    //int i = m_pFilesBook->GetSelection();
    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
            pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
            if (pChild) {
                pChild->Save();
            }
        }
    }
    return MO_DIRECTOR_STATUS_OK;

}

moDirectorStatus
moDirectorFrame::CloseProject() {

	moDirectorChildFrame* pChild = NULL;
	moDirectorChildConsole* pDirectorChildConsole = NULL;

    if (this->CloseAll()==MO_DIRECTOR_STATUS_OK) {

        if ( m_pDirectorCore->CloseProject() == MO_DIRECTOR_STATUS_OK ) {

            if(m_pDataNotebook)
                if (m_pDataNotebook->m_pProjectTreeCtrl)
                    m_pDataNotebook->m_pProjectTreeCtrl->DeleteAllItems();
            if (m_pLayers)
                m_pLayers->DeleteAllItems();
            if (m_pLayers2)
                m_pLayers2->DeleteAllItems();
            //if(m_pConnectionsWindow)
                //m_pConnectionsWindow->DeleteAll();

            return MO_DIRECTOR_STATUS_OK;
        }
    }
    return MO_DIRECTOR_STATUS_ERROR;

}

void
moDirectorFrame::OnProjectPreview( wxCommandEvent& event ) {

    ProjectPreview();

}

void
moDirectorFrame::OnProjectPreviewFullscreen( wxCommandEvent& event ) {

    FullScreen(false);

}

void
moDirectorFrame::OnFullscreen( wxCommandEvent& event ) {

    if (!IsFullScreen() ) {
        ShowFullScreen( true, wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION );
    } else {
        ShowFullScreen( false);
    }

}


void
moDirectorFrame::OnConfiguration( wxCommandEvent& event ) {

    moConfigurationDialog* pConfigurationDialog = new moConfigurationDialog(this);
    pConfigurationDialog->Show();

}


moDirectorChildFrame* moDirectorFrame::CreateChildFrame( moMobDescriptor p_MobDescriptor ) {

    // Make another frame, containing a canvas

	wxString title =(wxChar*)(char*) p_MobDescriptor.GetMobDefinition().GetConfigName();

    moDirectorChildFrame* pDirectorChildFrame = new moDirectorChildFrame( m_pFilesBook, title);

    //pDirectorChildFrame->SetTitle(title);

    // Give it an icon
#ifdef __WXMSW__
    //pDirectorChildFrame->SetIcon(wxIcon(_T("chrt_icn")));
#else
    //pDirectorChildFrame->SetIcon(wxIcon( mondrian_xpm ));
#endif

    //pDirectorChildFrame->Show(true);

	//extract filename form config full path name
	wxFileName xfname( wxString((wxChar*)(char*) p_MobDescriptor.GetMobDefinition().GetName() ) );

	m_pFilesBook->AddPage( pDirectorChildFrame,
                            (wxChar*)(char*) p_MobDescriptor.GetMobDefinition().GetLabelName(),
                            true);

	return pDirectorChildFrame;
}

/*================================================

  IDirectorActions Implemented by FrameDirector:

================================================*/

moDirectorStatus
moDirectorFrame::FocusOutput() {

    int outputwidth;
    int outputheight;
    int outputleft;
    int outputtop;

    {
        wxDisplay thisDisplay(0);
        wxDisplay theOtherDisplay(1);
        wxDisplay theOther2Display(2);

        thisDisplay.GetFromWindow(this);

        wxRect client = thisDisplay.GetClientArea();
        wxRect client2 = theOtherDisplay.GetClientArea();
        wxRect client3 = theOther2Display.GetClientArea();

        wxString clientareastr;
        wxString clientareastr2;
        wxString clientareastr3;

        clientareastr.Printf(_(" area: %d,%d,%d,%d"), client.GetLeft(), client.GetTop(), client.GetWidth(), client.GetHeight() );
        clientareastr2.Printf(_(" area: %d,%d,%d,%d"), client2.GetLeft(), client2.GetTop(), client2.GetWidth(), client2.GetHeight() );
        clientareastr3.Printf(_(" area: %d,%d,%d,%d"), client3.GetLeft(), client3.GetTop(), client3.GetWidth(), client3.GetHeight() );

       //wxMessageBox(thisDisplay.GetName() + clientareastr);
       //wxMessageBox(theOtherDisplay.GetName() + clientareastr2 );
       //wxMessageBox(theOther2Display.GetName() + clientareastr3 );


       if (client2.GetWidth()!=0){

           outputwidth = client2.GetWidth();
           outputheight = client2.GetHeight();
           outputleft = client2.GetLeft();
           outputtop = client2.GetTop();

       } else {

            outputwidth = m_pDirectorCore->GetResourceManager()->GetRenderMan()->GetOutputConfiguration().m_OutputResolution.width;
            outputheight = m_pDirectorCore->GetResourceManager()->GetRenderMan()->GetOutputConfiguration().m_OutputResolution.height;
            outputleft = 0;
            outputtop = 0;

       }


    }


    if(m_pGLCanvas) {
        if (m_pPreviewFrame) {
            if (m_pPreviewFrame->GetSize().GetWidth()!=outputwidth) m_pPreviewFrame->SetClientSize(wxSize(outputwidth,outputheight));
            else m_pPreviewFrame->Move(outputleft,outputtop);
        }
        m_pGLCanvas->Activate( m_pDirectorCore->GetDirectorIODeviceManager() );
    }

}


moDirectorStatus
moDirectorFrame::FullScreen( bool force ) {

    if (m_pPreviewFrame==NULL) {
        ProjectPreview();
        if (m_pPreviewFrame)
            m_pPreviewFrame->FullScreen();
    } else
    if ( m_pPreviewFrame!=NULL && !m_pPreviewFrame->IsShown() ) {
        ProjectPreview();
        m_pPreviewFrame->FullScreen(true);
    } else
    if (m_pPreviewFrame!=NULL && m_pPreviewFrame->IsShown()) {
        m_pPreviewFrame->FullScreen();
    }


}

moDirectorStatus
moDirectorFrame::ProjectPreview() {

    if (m_pPreviewWindow)
        if (m_pGLCanvas)
            if (m_pGLCanvas==m_pPreviewWindow->m_pGLCanvas) {

                //m_pPreviewWindow->m_pGLCanvas->Finish();

                if (!m_pPreviewFrame) {
                    m_pPreviewFrame = new moPreviewFrame( this, wxID_ANY );
                    //if (!m_pGLContext) {
                        m_pGLContext = m_pPreviewWindow->m_pGLCanvas->GetContext();
                    //}
                    m_pPreviewFrame->Init( this, m_pGLContext );
                }
                m_pPreviewFrame->Init( this, m_pGLContext );
                m_pPreviewFrame->m_pGLCanvas->SetCurrent();
                m_pPreviewFrame->Show();

                m_pGLCanvas = m_pPreviewFrame->m_pGLCanvas;

            } else {
                m_pGLCanvas = NULL;
                m_pPreviewFrame->m_pGLCanvas->Finish();
                m_pPreviewFrame->Hide();

                m_pPreviewWindow->m_pGLCanvas->Finish();//agregado...al sacarse arriba
                m_pPreviewWindow->Init( this, m_pGLContext );
                m_pPreviewWindow->m_pGLCanvas->SetCurrent();
                m_pPreviewWindow->Refresh();

                m_pGLCanvas = m_pPreviewWindow->m_pGLCanvas;

            }
        else return MO_DIRECTOR_STATUS_OK;
    else return MO_DIRECTOR_STATUS_OK;
    return MO_DIRECTOR_STATUS_OK;

}

void
moDirectorFrame::ViewSwapBuffers() {
    if (m_pGLCanvas!=NULL) {

        int ttid = m_pDirectorCore->GetResourceManager()->GetTextureMan()->GetTextureMOId( moText("preview_texture"), false);
        moTexture* ptex = m_pDirectorCore->GetResourceManager()->GetTextureMan()->GetTexture(ttid);
        int glid = 0;
        if (ptex) {
            glid = ptex->GetGLId();
        }


        if (m_pPreviewFrame && m_pGLCanvas==m_pPreviewFrame->m_pGLCanvas) {

            m_pPreviewWindow->m_pGLCanvas->SetCurrent();
            m_pDirectorCore->GetResourceManager()->GetGLMan()->SetOrthographicView(400, 300);

            glBindTexture(GL_TEXTURE_2D, glid );
            glColor4f(1.0,1.0,1.0,1.0);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0.0);
                glVertex2f(0, 0);

                glTexCoord2f(1.0, 0.0);
                glVertex2f(400, 0);

                glTexCoord2f(1.0, 1.0);
                glVertex2f(400, 300);

                glTexCoord2f(0, 1.0);
                glVertex2f(0, 300);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);

            m_pPreviewWindow->m_pGLCanvas->SwapBuffers();
            //m_pPreviewWindow->m_pGLCanvas->Refresh();

        }

        //m_pGLCanvas->SwapBuffers();
        m_pGLCanvas->ViewSwapBuffers( glid );
    }
}

MO_HANDLE
moDirectorFrame::GetHandle() {
    if (m_pGLCanvas)
        return m_pGLCanvas->GetHandle();
    return NULL;

}


moDirectorStatus
moDirectorFrame::EditMob( moMobDescriptor p_MobDescriptor ) {

	moDirectorStatus res;
	moMobDescriptor MobDescriptor;


    moDirectorChildFrame* pChild = NULL;
    moDirectorChildConsole* pDirectorChildConsole = NULL;

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
            pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
            if (pChild) {
                if( pChild->IsMob( p_MobDescriptor ) ) {
                    return MO_DIRECTOR_STATUS_CONFIG_ALREADY_OPENED;
                }
            }
        }
    }

    //si el archivo todavia no fue abierto...
    pChild = NULL;
    pChild = CreateChildFrame( p_MobDescriptor );

    if(pChild!=NULL) {

        //m_pChildFrameList.Append( pChild );
        pChild->Init( this, p_MobDescriptor);

        return MO_DIRECTOR_STATUS_OK;

    } else return MO_DIRECTOR_STATUS_NOT_FOUND;

	return res;
}

moDirectorStatus
moDirectorFrame::CloseMob( moMobDescriptor p_MobDesc ) {

	if ( m_pDirectorCore->CloseMob( p_MobDesc ) == MO_DIRECTOR_STATUS_OK ) {

		moDirectorChildFrame* pChild;

		for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
            if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
                pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
                if (pChild) {
                    if( pChild->IsMob( p_MobDesc ) ) {
                        m_pFilesBook->RemovePage( i );
                        return MO_DIRECTOR_STATUS_OK;
                    }
                }
            }
		}
	}
	return MO_DIRECTOR_STATUS_MOB_NOT_FOUND;

}

moDirectorStatus
moDirectorFrame::SaveMob( moMobDescriptor p_MobDescriptor ) {
	return m_pDirectorCore->SaveMob( p_MobDescriptor );
}

moDirectorStatus
moDirectorFrame::ProjectUpdated( moProjectDescriptor p_ProjectDescriptor ) {

	MOuint i;
	wxTreeItemId exid;
	wxString cPath;
	wxString cMol;
	wxString xitemname;
	moMobDescriptor MobDesc;

    if (m_pPanelTexture)
        m_pPanelTexture->InitTexturesTree();

	if (!m_pDataNotebook) return MO_DIRECTOR_STATUS_ERROR;
	if (!m_pDataNotebook->m_pProjectTreeCtrl) return MO_DIRECTOR_STATUS_ERROR;

	m_pDataNotebook->m_pProjectTreeCtrl->DeleteAllItems();
	m_pDataNotebook->m_pIODevicesTreeCtrl->DeleteAllItems();
	m_pDataNotebook->m_pResourcesTreeCtrl->DeleteAllItems();

	cPath = (wxChar*)(const char*)p_ProjectDescriptor.GetConfigPath();
	cMol = (wxChar*)(const char*) p_ProjectDescriptor.GetConfigName();

	if(m_pDataNotebook->m_pVirtualDirTreeCtrl)
		m_pDataNotebook->m_pVirtualDirTreeCtrl->SetRootPath( cPath, wxVDTC_DEFAULT);

	FrameManager.GetPane(wxT("manager")).Caption(wxT("Project manager: ")+cMol);

    wxTreeItemId preeffectsid,
    effectsid,
    posteffectsid,
    mastereffectsid,
    iodevicesid,
    resourcesid,
    consoleid;

	wxTreeItemId root = m_pDataNotebook->m_pProjectTreeCtrl->AddRoot( (wxChar*)(char*)(moText("Layer effects: ") + p_ProjectDescriptor.GetConfigName()) );

	iodevicesid = m_pDataNotebook->m_pIODevicesTreeCtrl->AddRoot( (wxChar*)(char*)(moText("IODevices: ") + p_ProjectDescriptor.GetConfigName()) );

	resourcesid = m_pDataNotebook->m_pResourcesTreeCtrl->AddRoot( (wxChar*)(char*)(moText("Resources: ") + p_ProjectDescriptor.GetConfigName()) );

    consoleid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem(root, wxT("Console"), 0);
	preeffectsid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem(root, wxT("PreEffects"), 0);
	effectsid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem(root, wxT("Effects"), 0);
	posteffectsid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem(root, wxT("PostEffects"), 0);
	mastereffectsid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem(root, wxT("MasterEffects"), 0);

	//moMoldeoObjects	*pMOBS = p_ProjectDescriptor.m_pMOBS;
	moMobDescriptors pMobDescriptors = GetMobDescriptors();

	moItemLayerWindow* pobject = NULL;
	moEffectLayerTimelineCtrl* pobject2 = NULL;

	if (m_pLayers) {
		m_pLayers->DeleteAllItems();

		m_preeffectsid = m_pLayers->AddRoot( wxT("0"), wxT("pre-effects"), NULL );
		m_effectsid = m_pLayers->AddRoot( wxT("1"), wxT("effects"), NULL );
		m_posteffectsid = m_pLayers->AddRoot( wxT("2"), wxT("post-effects"), NULL );
	}

	if (m_pLayers2) {
		m_pLayers2->DeleteAllItems();

		m_preeffectsid2 = m_pLayers2->AddRoot( wxT("timeline"), wxT("pre-effects"),  NULL );
		m_effectsid2 = m_pLayers2->AddRoot( wxT("timeline"), wxT("effects"), NULL );
		m_posteffectsid2 = m_pLayers2->AddRoot( wxT("timeline"), wxT("post-effects"),  NULL );
	}

	//intento de borrar unicamente los layers correspondientes...al final resolvimos borrar todo...mejor..
	//esto lo usaremos para actualizar lo que querramos de cada layer
	//TreeMultiItemNode *preeffectslayers = (TreeMultiItemNode *)m_preeffectsid.GetItem();
	//if (preeffectslayers)
		//preeffectslayers->

    wxTreeMultiWindowInfo wndinfo( wxTMC_SPAN_WIDTH, 0, 0, false);
    wndinfo.SetTopSpacing(0);
    wndinfo.SetFrontSpacing(0);
    wndinfo.Indent(0);
    //m_pLayers->SetCheckboxView();

    if (m_pLayers) m_pLayers->SetSpacingY(0);
    if (m_pLayers2) m_pLayers2->SetSpacingY(0);

	for( i=0;  i < pMobDescriptors.Count(); i++) {
	    moMobDescriptor pMobDescriptor = pMobDescriptors[i];
		xitemname = wxString( (wxChar*)(char*) pMobDescriptor.GetMobDefinition().GetName() ) + wxT("::");
		xitemname+= wxString( (wxChar*)(char*) pMobDescriptor.GetMobDefinition().GetConfigName() );

		switch( pMobDescriptor.GetMobDefinition().GetType() ) {

		    case MO_OBJECT_CONSOLE:
                exid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem( consoleid, xitemname , 1 );
                if (exid.IsOk()) m_pDataNotebook->m_pProjectTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
                break;

			case MO_OBJECT_PREEFFECT:
				exid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem( preeffectsid, xitemname , 1 );
				if (exid.IsOk()) m_pDataNotebook->m_pProjectTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
				pobject = new moItemLayerWindow( m_pLayers , wxID_ANY, wxPoint(0,0), wxSize(m_pLayersPanelCtrl->GetSize().GetWidth(),40) );
				//pobject2 = new moEffectLayerTimelineCtrl(m_pLayers2);
				if (pobject) {
				    pobject->SetNextActionHandler(this);
					pobject->Set( pMobDescriptor );
				    //pobject2->SetNextActionHandler(this);
					//pobject2->Set( pMobDescriptor );
					m_pLayers->AppendWindow( m_preeffectsid, pobject, _(""), wndinfo);
					//m_pLayers2->AppendWindow( m_preeffectsid2, pobject2, _(""), wndinfo);
				}
				break;

			case MO_OBJECT_EFFECT:
				//tree
				exid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem( effectsid, xitemname , 1);
				if (exid.IsOk()) m_pDataNotebook->m_pProjectTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));

				//timelinetree
				pobject = new moItemLayerWindow( m_pLayers , wxID_ANY, wxPoint(0,0), wxSize(m_pLayersPanelCtrl->GetSize().GetWidth(),40) );
				//pobject2 = new moEffectLayerTimelineCtrl(m_pLayers2);
				if (pobject) {
				    pobject->SetNextActionHandler(this);
					pobject->Set( pMobDescriptor );
				    //pobject2->SetNextActionHandler(this);
					//pobject2->Set( pMobDescriptor );
					//tree
					m_pLayers->AppendWindow( m_effectsid, pobject, _(""), wndinfo);
					//and timeline
					//m_pLayers2->AppendWindow( m_effectsid2, pobject2, _(""), wndinfo);
				}
				break;
			case MO_OBJECT_POSTEFFECT:
				exid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem( posteffectsid, xitemname , 1);
				if (exid.IsOk()) m_pDataNotebook->m_pProjectTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
				pobject = new moItemLayerWindow( m_pLayers , wxID_ANY, wxPoint(0,0), wxSize(m_pLayersPanelCtrl->GetSize().GetWidth(),40) );
				//pobject2 = new moEffectLayerTimelineCtrl(m_pLayers2);
				if (pobject) {
				    pobject->SetNextActionHandler(this);
					pobject->Set( pMobDescriptor );
				    //pobject2->SetNextActionHandler(this);
					//pobject2->Set( pMobDescriptor );
					m_pLayers->AppendWindow( m_posteffectsid, pobject, _(""), wndinfo);
					//m_pLayers2->AppendWindow( m_posteffectsid2, pobject2, _(""), wndinfo);
				}
				break;
			case MO_OBJECT_MASTEREFFECT:
				exid = m_pDataNotebook->m_pProjectTreeCtrl->AppendItem( mastereffectsid, xitemname , 1);
				if (exid.IsOk()) m_pDataNotebook->m_pProjectTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
				break;
			case MO_OBJECT_IODEVICE:
				exid = m_pDataNotebook->m_pIODevicesTreeCtrl->AppendItem( iodevicesid, xitemname , 1);
				if (exid.IsOk()) m_pDataNotebook->m_pIODevicesTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
				break;
			case MO_OBJECT_RESOURCE:
				exid = m_pDataNotebook->m_pResourcesTreeCtrl->AppendItem( resourcesid, xitemname , 1);
				if (exid.IsOk()) m_pDataNotebook->m_pResourcesTreeCtrl->SetItemData( exid, new moMobItemData( pMobDescriptor ));
				break;

			default:
				exid.Unset();
				break;
		}

	}

	m_pDataNotebook->m_pProjectTreeCtrl->Expand(root);
	m_pDataNotebook->m_pIODevicesTreeCtrl->Expand(iodevicesid);
	m_pDataNotebook->m_pResourcesTreeCtrl->Expand(resourcesid);

	FrameManager.Update();

	//m_pConnectionsWindow->ProjectUpdated( p_ProjectDescriptor );

	return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus
moDirectorFrame::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {

	moDirectorChildFrame* pChild;

    moMobDescriptor MobDesc = p_ParameterDesc.GetMobDescriptor();

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
            if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
                pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
                if (pChild) {
                    if( pChild->IsMob( MobDesc ) ) {
                        return pChild->ParameterUpdated( p_ParameterDesc );
                    }
                }
            }
    }

    return MO_DIRECTOR_STATUS_MOB_NOT_FOUND;

}


moDirectorStatus
moDirectorFrame::EditParameter( moParameterDescriptor p_ParameterDesc ) {

	moDirectorChildFrame* pChild;

    moMobDescriptor MobDesc = p_ParameterDesc.GetMobDescriptor();

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
			if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
                pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
                if (pChild) {
                    if( pChild->IsMob( MobDesc ) ) {
                        return pChild->EditParameter( p_ParameterDesc );
                    }
                }
			}
    }

    return MO_DIRECTOR_STATUS_MOB_NOT_FOUND;

}

moDirectorStatus
moDirectorFrame::EditValue( moValueDescriptor p_ValueDesc ) {

	moDirectorChildFrame* pChild;

    moParameterDescriptor ParamDesc = p_ValueDesc.GetParamDescriptor();
    moMobDescriptor MobDesc = ParamDesc.GetMobDescriptor();

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
			pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
			if (pChild) {
                if( pChild->IsMob( MobDesc ) ) {
                    return pChild->EditValue( p_ValueDesc );
                }
			}
        }
    }

    return MO_DIRECTOR_STATUS_MOB_NOT_FOUND;

}

moDirectorStatus
moDirectorFrame::ValueUpdated( moValueDescriptor p_ValueDesc ) {

    moDirectorStatus Dstatus = MO_DIRECTOR_STATUS_OK;

	moDirectorChildFrame* pChild;

    moParameterDescriptor ParamDesc = p_ValueDesc.GetParamDescriptor();
    moMobDescriptor MobDesc = ParamDesc.GetMobDescriptor();

    for( size_t i=0; i<m_pFilesBook->GetPageCount(); i++ ) {
        if (m_pFilesBook->GetPage(i)->GetName()==_T("child frame") ) {
			pChild =(moDirectorChildFrame*)m_pFilesBook->GetPage(i);
			if (pChild) {
                if( pChild->IsMob( MobDesc ) ) {
                    Dstatus = CHECK_DIRECTOR_STATUS_ERROR( Dstatus, pChild->ValueUpdated( p_ValueDesc ));
                }
			}
        }
    }

    //aca tenemos que actualizar tambien a los controles
    //dentro de los effect-layer-control

    //hay que hacerlo bien, a través del LayerControlPanel
    if (m_pLayers) Dstatus = CHECK_DIRECTOR_STATUS_ERROR( Dstatus, m_pLayers->ValueUpdated( p_ValueDesc ) );
    if (m_pLayers2) Dstatus = CHECK_DIRECTOR_STATUS_ERROR( Dstatus, m_pLayers2->ValueUpdated( p_ValueDesc ) );

    return Dstatus;
}

void
moDirectorFrame::Log( moText p_message ) {

	wxString  w =(wxChar*)(char*)p_message;

    if (m_pDataNotebook->m_pLogTextCtrl->GetNumberOfLines()>10000) {
        m_pDataNotebook->m_pLogTextCtrl->Clear();
    }

	m_pDataNotebook->m_pLogTextCtrl->SetDefaultStyle( wxTextAttr( wxColour( 50, 255, 50 )) );
	m_pDataNotebook->m_pLogTextCtrl->AppendText(w + wxT("\n"));

	m_pDataNotebook->m_pLogTextCtrl->ShowPosition(m_pDataNotebook->m_pLogTextCtrl->GetLastPosition());

}

void
moDirectorFrame::LogError( moText p_message ) {
	//seria bueno en rojo...

	wxString  w =(wxChar*)(char*)p_message;

    if (m_pDataNotebook->m_pLogTextCtrl->GetNumberOfLines()>10000) {
        m_pDataNotebook->m_pLogTextCtrl->Clear();
    }

	m_pDataNotebook->m_pLogTextCtrl->SetDefaultStyle( wxTextAttr( wxColour(255,0,0) ) );
	m_pDataNotebook->m_pLogTextCtrl->AppendText(w + wxT("\n"));

    m_pDataNotebook->m_pLogTextCtrl->ShowPosition(m_pDataNotebook->m_pLogTextCtrl->GetLastPosition());
	//wxMessageBox(w);

}
/*
void
moDirectorFrame::ShowTip() {
    int s_index = rand() % 5;
    wxMessageBox(wxT("Entro"),wxT("Moldeo Director"));
    wxTipProvider *moTipProvider = wxCreateFileTipProvider(wxT("tips.txt"), s_index);
    wxShowTip(this,moTipProvider,true);
    delete moTipProvider;
}
*/
void moDirectorFrame::OnEditPreferences(wxCommandEvent& event) {
    wxMessageBox(wxT("On Edit Preferences - Functionality to be implemented"),wxT("Moldeo Director"));
}

void moDirectorFrame::OnExampleSimple(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/test.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("test.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("test.mol - Moldeo Director"));

}

void moDirectorFrame::OnExampleCamera(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/camaras.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("camaras.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("camaras.mol - Moldeo Director"));

}

void moDirectorFrame::OnExampleInteractiveCamera(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/camarasinteractivas.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("camarasinteractivas.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("camarasinteractivas.mol - Moldeo Director"));

}

void moDirectorFrame::OnExampleInteractiveCameraGPU(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/camarasinteractivasgpu.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("camarasinteractivasgpu.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("camarasinteractivasgpu.mol - Moldeo Director"));

}

void moDirectorFrame::OnExampleInteractiveCameraGPUKLT2(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/camarasinteractivasgpuklt2.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("camarasinteractivasgpuklt2.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("camarasinteractivasgpuklt2.mol - Moldeo Director"));

}

void moDirectorFrame::OnExampleCameraCircularBuffer(wxCommandEvent& event) {
	moProjectDescriptor ProjectDescriptor;
	moDirectorStatus	mStatus;

	wxString text = _("../../data/test/camarascircular.mol");
	wxMessageBox(text);
    ProjectDescriptor.Set( moText("../../data/test/"), moText("camarascircular.mol") );
    mStatus = OpenProject( ProjectDescriptor );
    SetTitle(wxT("camarascircular.mol - Moldeo Director"));

}

