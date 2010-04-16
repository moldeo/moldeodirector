/***************************************************************
 * Name:      testwxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2008-11-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "moldeodirectorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(testwxFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(testwxFrame)
const long testwxFrame::ID_SLIDER1 = wxNewId();
const long testwxFrame::ID_STATICTEXT1 = wxNewId();
const long testwxFrame::idMenuQuit = wxNewId();
const long testwxFrame::idMenuAbout = wxNewId();
const long testwxFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(testwxFrame,wxFrame)
    //(*EventTable(testwxFrame)
    //*)
END_EVENT_TABLE()

testwxFrame::testwxFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(testwxFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 100, wxPoint(128,72), wxSize(216,64), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("HOLA"), wxPoint(144,96), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&testwxFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&testwxFrame::OnAbout);
    //*)

    moConsole* TestConsole = new moConsole();

    int fxcount;

    if (TestConsole)
        fxcount = TestConsole->GetEffectManager().Effects().Count();

    wxMessageBox(wxString(_("Console created: effects:")) + wxString( moText2Wx( IntToStr(fxcount))) );
}

testwxFrame::~testwxFrame()
{
    //(*Destroy(testwxFrame)
    //*)
}

void testwxFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void testwxFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
