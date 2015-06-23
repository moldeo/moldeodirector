#include "moPreviewFrame.h"

//(*InternalHeaders(moPreviewFrame)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include <wx/display.h>

//(*IdInit(moPreviewFrame)
const long moPreviewFrame::TOOLPLAY = wxNewId();
const long moPreviewFrame::TOOLPAUSE = wxNewId();
const long moPreviewFrame::TOOLFULLSCREEN = wxNewId();
const long moPreviewFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moPreviewFrame,wxFrame)
	//(*EventTable(moPreviewFrame)
	//*)
	//EVT_TOOL( wxID_ANY, moPreviewFrame::OnToolClick)
	EVT_SIZE( moPreviewFrame::OnSize )
	EVT_KEY_UP( moPreviewFrame::OnKeyUp )
END_EVENT_TABLE()

moPreviewFrame::moPreviewFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{

  m_pGLCanvas = NULL;
	m_pSizer = NULL;
  //Create(parent, wxID_ANY, _("Moldeo output"), pos, size, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	//(*Initialize(moPreviewFrame)
  Create(parent, wxID_ANY, _("Moldeo output"), pos, size, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(400,300));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
/*
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(32,32));
	ToolBarItem1 = ToolBar1->AddTool(TOOLPLAY, _("Play"), wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/play32.png"))), wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/play32dis.png"))), wxITEM_NORMAL, _("Play syncro"), _("Help text"));
	ToolBarItem2 = ToolBar1->AddTool(TOOLPAUSE, _("Pause"), wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/pause32.png"))), wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/pause32.png"))), wxITEM_NORMAL, _("Pause"), _("Pause"));
	ToolBarItem3 = ToolBar1->AddTool(TOOLFULLSCREEN, _("Fullscreen"), wxBitmap(wxImage(_T(MOLDEODATADIR"/icons/onofficon32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Fullscreen"), _("Fullscreen"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
*/

	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&moPreviewFrame::OnClose);
	//*)

	//ToolBar1->Hide();

}

moPreviewFrame::~moPreviewFrame()
{
	//(*Destroy(moPreviewFrame)
	//*)
}

void moPreviewFrame::Init( moIDirectorActions* pActionsHandler, wxGLContext* p_pGLContext ) {

    SetNextActionHandler( pActionsHandler);

    ReSetGLCanvas(p_pGLContext);

    Log("moPreviewFrame::Init > Preview frame initialized");
}

void moPreviewFrame::ReSetGLCanvas( wxGLContext* p_pGLContext ) {

    /**
    *   Create the wxGLCanvas in this frame with the original GLContext
    */

    if (m_pGLCanvas) delete m_pGLCanvas;
    m_pGLCanvas = NULL;

    if (!m_pGLCanvas) {

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


        m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, attribList, wxPoint(0,0), GetSize(), 0, wxT("moGLCanvas"));
        //m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, attribList, wxDefaultPosition, wxDefaultSize, 0, wxT("moGLCanvas"));
        //m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, attribList, wxPoint(0,0), wxSize(1024,768), 0, wxT("moGLCanvas"));
        //m_pGLCanvas = new moGLCanvas( this, p_pGLContext, -1, NULL, wxPoint(0,0), wxSize(1024,768), 0, wxT("moGLCanvas"));
        Log("moPreviewFrame::Init > Created m_pGLCanvas > "  +IntToStr(GetSize().GetWidth()) + moText("X") + IntToStr(GetSize().GetHeight()) );
    }


    if (m_pGLCanvas) {
        /*
        if (!m_pSizer) {
            //m_pSizer = new wxGridSizer(1,1,0,0);
        }
        //wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        if (m_pSizer) {
            Log("moPreviewFrame::ReSetGLCanvas > Created wxGridSizer...");
            m_pSizer->Add(m_pGLCanvas, wxALL|wxEXPAND);
            this->SetSizer(m_pSizer);
            this->SetAutoLayout(true);
        }
        */

        m_pGLCanvas->Init( this );
    }

}

void
moPreviewFrame::OnToolClick( wxCommandEvent &event) {

    if ( event.GetId() == TOOLPLAY) {
        ShowMessage( moText("Play") );
        //ToolBar1->Hide();
        //SetClientSize(wxSize(1024,768));
    } else if (event.GetId() == TOOLPAUSE) {
        ShowMessage( moText("Pause") );
        //ToolBar1->Hide();

    } else if (event.GetId() == TOOLFULLSCREEN) {
        ShowMessage( moText("Fullscreen") );
        FullScreen();
    }

    //wxDisplay thisDisplay(0);
    //wxDisplay theOtherDisplay(1);

    //thisDisplay.GetFromWindow(this);

    //wxRect client = thisDisplay.GetClientArea();
    //wxRect client2 = theOtherDisplay.GetClientArea();

    //wxString clientareastr;
    //wxString clientareastr2;

    //clientareastr.Printf(" area: %d,%d,%d,%d", client.GetLeft(), client.GetTop(), client.GetWidth(), client.GetHeight() );
    //clientareastr2.Printf(" area: %d,%d,%d,%d", client2.GetLeft(), client2.GetTop(), client2.GetWidth(), client2.GetHeight() );

   ///wxMessageBox(thisDisplay.GetName() + clientareastr);
   //wxMessageBox(theOtherDisplay.GetName() + clientareastr2 );


}


void moPreviewFrame::OnClose(wxCloseEvent& event)
{
    ProjectPreview();
}


moDirectorStatus
moPreviewFrame::FullScreen( bool force) {

    if (!IsFullScreen() || force ) {
        Log("moPreviewFrame going fullscreen.");
        //ShowFullScreen( true, wxFULLSCREEN_NOMENUBAR | wxFULLSCREEN_NOSTATUSBAR | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION | wxFULLSCREEN_NOTOOLBAR );
        ShowFullScreen( true );
    } else {
        Log("moPreviewFrame restoring.");
        ShowFullScreen( false, 0 );
    }

    return MO_DIRECTOR_STATUS_OK;

}


void moPreviewFrame::OnSize(wxSizeEvent& event)
{
    wxSize framesize;
    wxPoint framepos;

    framesize = event.GetSize();
    framepos = GetPosition();

    Log( moText("moPreviewFrame::OnSize > Frame On Size : ") + IntToStr(framesize.GetWidth()) + moText("X") + IntToStr(framesize.GetHeight())
        + moText( " Position:")
        + IntToStr( framepos.x ) + moText("X") + IntToStr( framepos.y )
        );

    if (m_pGLCanvas) {
        //ReSetGLCanvas( m_pGLCanvas->GetContext() );
        m_pGLCanvas->SetSize(0,0,framesize.GetWidth(), framesize.GetHeight());
        m_pGLCanvas->Reset();
    }

    Refresh();

    //SetView( 0 , 0, framesize.GetWidth() , framesize.GetHeight() );
    //Init();
    //wxFrame::OnSize(event);
}


void
moPreviewFrame::OnKeyUp( wxKeyEvent &event ) {
    Log( "moPreviewFrame::OnKeyUp > keycode up: " + IntToStr(event.GetKeyCode()) );
    /*fullscreen off on escape*/
    if (event.GetKeyCode()==27) {
        Log( "moPreviewFrame::OnKeyUp > Off fullscreen" );
        ShowFullScreen( false, 0);
    }
}


