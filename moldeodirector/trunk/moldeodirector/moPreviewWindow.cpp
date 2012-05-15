#include "moPreviewWindow.h"

//(*InternalHeaders(moPreviewWindow)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moPreviewWindow)
const long moPreviewWindow::ID_BITMAPBUTTONPLAY = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONPAUSE = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONFULLSCREEN = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONSCREENSHOT = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONSAVEVIDEO = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONSAVESESSION = wxNewId();
const long moPreviewWindow::ID_BITMAPBUTTONSTOP = wxNewId();
//*)

BEGIN_EVENT_TABLE(moPreviewWindow,wxPanel)
	//(*EventTable(moPreviewWindow)
	//*)
END_EVENT_TABLE()

moPreviewWindow::moPreviewWindow(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxInitAllImageHandlers();
	//(*Initialize(moPreviewWindow)
	Create(parent, id, wxDefaultPosition, wxSize(401,336), wxTAB_TRAVERSAL, _T("id"));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonPlay = new wxBitmapButton(this, ID_BITMAPBUTTONPLAY, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/play32.png"))), wxPoint(0,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPLAY"));
	BitmapButtonPlay->SetDefault();
	BitmapButtonPlay->SetToolTip(_("Play"));
	BitmapButtonPlay->SetHelpText(_("Play"));
	BitmapButtonPause = new wxBitmapButton(this, ID_BITMAPBUTTONPAUSE, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/pause32.png"))), wxPoint(32,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPAUSE"));
	BitmapButtonPause->SetDefault();
	BitmapButtonPause->SetToolTip(_("Pause"));
	BitmapButtonPause->SetHelpText(_("Pause"));
	ButtonFullSCreen = new wxBitmapButton(this, ID_BITMAPBUTTONFULLSCREEN, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/fullscreen32.png"))), wxPoint(272,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONFULLSCREEN"));
	ButtonFullSCreen->SetDefault();
	ButtonFullSCreen->SetToolTip(_("Fullscreen"));
	ButtonFullSCreen->SetHelpText(_("Fullscreen"));
	BitmapButtonScreenshot = new wxBitmapButton(this, ID_BITMAPBUTTONSCREENSHOT, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/screenshot32.png"))), wxPoint(312,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCREENSHOT"));
	BitmapButtonScreenshot->SetDefault();
	BitmapButtonScreenshot->SetToolTip(_("Output - Focus"));
	BitmapButtonScreenshot->SetHelpText(_("Output - Focus"));
	BitmapButtonSaveVideo = new wxBitmapButton(this, ID_BITMAPBUTTONSAVEVIDEO, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/savevideo32.png"))), wxPoint(344,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSAVEVIDEO"));
	BitmapButtonSaveVideo->SetDefault();
	BitmapButtonSaveVideo->SetToolTip(_("Movie"));
	BitmapButtonSaveVideo->SetHelpText(_("Movie"));
	BitmapButtonSaveSession = new wxBitmapButton(this, ID_BITMAPBUTTONSAVESESSION, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/savesession32.png"))), wxPoint(64,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSAVESESSION"));
	BitmapButtonSaveSession->SetToolTip(_("Record"));
	BitmapButtonSaveSession->SetHelpText(_("Record"));
	BitmapButtonStop = new wxBitmapButton(this, ID_BITMAPBUTTONSTOP, wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/stop32.png"))), wxPoint(96,300), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSTOP"));
	BitmapButtonStop->SetDefault();
	BitmapButtonStop->SetToolTip(_("Stop"));
	BitmapButtonStop->SetHelpText(_("Stop"));

	Connect(ID_BITMAPBUTTONPLAY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnBitmapButtonPlayClick);
	Connect(ID_BITMAPBUTTONPAUSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnBitmapButtonPauseClick);
	Connect(ID_BITMAPBUTTONFULLSCREEN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnButtonFullSCreenClick);
	Connect(ID_BITMAPBUTTONSCREENSHOT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnBitmapButtonFocusAndActivate);
	Connect(ID_BITMAPBUTTONSAVESESSION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnBitmapButtonSaveSessionClick);
	Connect(ID_BITMAPBUTTONSTOP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPreviewWindow::OnBitmapButtonStopClick);
	//*)

	BitmapButtonPlay->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonPause->SetBackgroundColour(wxColour(0,0,0));
	ButtonFullSCreen->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonScreenshot->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonSaveVideo->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonSaveSession->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonStop->SetBackgroundColour(wxColour(0,0,0));

    BitmapButtonPlay->SetMargins( 0, 0 );
	ButtonFullSCreen->SetMargins( 0, 0 );

	m_pGLCanvas = NULL;
}

moPreviewWindow::~moPreviewWindow()
{
	//(*Destroy(moPreviewWindow)
	//*)
}

void moPreviewWindow::Init( moIDirectorActions* pActionsHandler, wxGLContext* p_pGLContext   ) {

    SetNextActionHandler( pActionsHandler);
    //int attribList[10];
    int n = 0;
    int attribList[] =
      {
        WX_GL_RGBA,
        WX_GL_DOUBLEBUFFER,
        WX_GL_MIN_RED, 8,
        WX_GL_MIN_GREEN, 8,
        WX_GL_MIN_BLUE, 8,
        WX_GL_MIN_ALPHA, 8,
        WX_GL_DEPTH_SIZE, 16,
        WX_GL_STENCIL_SIZE, 8,
        /*WX_GL_LEVEL, 0,
        WX_GL_AUX_BUFFERS, 0*/
        0
      };

    //attribList[n++] = WX_GL_RGBA;
    //attribList[n++] = WX_GL_DOUBLEBUFFER;
    //attribList[n++] = WX_GL_DEPTH_SIZE;
    //attribList[n++] = 32;
    //attribList[n++] = WX_GL_SAMPLES;
    //attribList[n++] = 4;
    //attribList[n] = 0; // terminate the list



    if (p_pGLContext) {
        if (m_pGLCanvas==NULL) {

            m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, attribList, wxPoint(0,0), wxSize(400,300), 0, wxT("moGLCanvas"));
            //m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, NULL, wxPoint(0,40), wxSize(400,300), 0, wxT("moGLCanvas"));
        }
    } else {
        if (m_pGLCanvas==NULL) {
            m_pGLCanvas = new moGLCanvas( this, -1, attribList, wxPoint(0,0), wxSize(400,300), 0, wxT("moGLCanvas"));
            //m_pGLCanvas = new moGLCanvas( this, -1, NULL, wxPoint(0,40), wxSize(400,300), 0, wxT("moGLCanvas"));
            //m_pGLCanvas = new moGLCanvas( this, -1, wxPoint(0,40), wxSize(400,300), 0, wxT("moGLCanvas"));
            //wxGLCanvas* pCanvas = new wxGLCanvas(  this, -1, wxPoint(0,40), wxSize(400,300), 0, wxT("moGLCanvas") );
        }
    }
    if (m_pGLCanvas)
        m_pGLCanvas->Init( this );
}

void moPreviewWindow::OnButtonFullSCreenClick(wxCommandEvent& event)
{
    FullScreen();
}

void moPreviewWindow::OnBitmapButtonFocusAndActivate(wxCommandEvent& event)
{
    FocusOutput();
}

void moPreviewWindow::OnBitmapButtonPlayClick(wxCommandEvent& event)
{
    this->Play();
}

void moPreviewWindow::OnBitmapButtonPauseClick(wxCommandEvent& event)
{
    this->Pause();
}

void moPreviewWindow::OnBitmapButtonSaveSessionClick(wxCommandEvent& event)
{
    this->SaveSession();
}

void moPreviewWindow::OnBitmapButtonStopClick(wxCommandEvent& event)
{
    this->Stop();
}
