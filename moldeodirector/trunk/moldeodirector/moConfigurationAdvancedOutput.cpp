#include "moConfigurationAdvancedOutput.h"

//(*InternalHeaders(moConfigurationAdvancedOutput)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moConfigurationAdvancedOutput)
const long moConfigurationAdvancedOutput::ID_BUTTON1 = wxNewId();
const long moConfigurationAdvancedOutput::ID_BUTTON2 = wxNewId();
const long moConfigurationAdvancedOutput::ID_CHOICE5 = wxNewId();
const long moConfigurationAdvancedOutput::ID_PANEL1 = wxNewId();
const long moConfigurationAdvancedOutput::ID_PANEL2 = wxNewId();
const long moConfigurationAdvancedOutput::ID_PANEL3 = wxNewId();
const long moConfigurationAdvancedOutput::ID_CHOICE1 = wxNewId();
const long moConfigurationAdvancedOutput::ID_STATICTEXT2 = wxNewId();
const long moConfigurationAdvancedOutput::ID_STATICTEXT3 = wxNewId();
const long moConfigurationAdvancedOutput::ID_STATICTEXT4 = wxNewId();
const long moConfigurationAdvancedOutput::ID_STATICTEXT1 = wxNewId();
const long moConfigurationAdvancedOutput::ID_CHOICE2 = wxNewId();
const long moConfigurationAdvancedOutput::ID_CHOICE4 = wxNewId();
const long moConfigurationAdvancedOutput::ID_CHOICE3 = wxNewId();
const long moConfigurationAdvancedOutput::ID_PANEL4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moConfigurationAdvancedOutput,wxFrame)
	//(*EventTable(moConfigurationAdvancedOutput)
	//*)
END_EVENT_TABLE()

moConfigurationAdvancedOutput::moConfigurationAdvancedOutput(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moConfigurationAdvancedOutput)
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(606,373));
	FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(490,33), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Button1 = new wxButton(Panel1, ID_BUTTON1, _("Add Clip"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("Delete Clip"), wxPoint(88,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Choice4 = new wxChoice(Panel1, ID_CHOICE5, wxPoint(176,8), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
	Choice4->SetSelection( Choice4->Append(_("Choose resolution")) );
	Choice4->Append(_("640x480"));
	Choice4->Append(_("800x600"));
	Choice4->Append(_("1024x768"));
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(173,32), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxSize(488,338), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxSize(194,107), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	Display1 = new wxChoice(Panel4, ID_CHOICE1, wxPoint(64,8), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Display1->SetSelection( Display1->Append(_("clip full")) );
	Display1->Append(_("clip 1"));
	Display1->Append(_("clip 2"));
	Display1->Append(_("clip 3"));
	StaticText2 = new wxStaticText(Panel4, ID_STATICTEXT2, _("Display 1"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(Panel4, ID_STATICTEXT3, _("Display 2"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(Panel4, ID_STATICTEXT4, _("Display 3"), wxPoint(8,72), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText1 = new wxStaticText(Panel4, ID_STATICTEXT1, _("Display 4"), wxPoint(8,104), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Choice1 = new wxChoice(Panel4, ID_CHOICE2, wxPoint(64,40), wxSize(130,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice1->SetSelection( Choice1->Append(_("clip 1")) );
	Choice1->Append(_("clip 2"));
	Choice1->Append(_("clip 3"));
	Choice1->Append(_("clip 4"));
	Choice3 = new wxChoice(Panel4, ID_CHOICE4, wxPoint(64,72), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
	Choice3->SetSelection( Choice3->Append(_("clip 1")) );
	Choice3->Append(_("clip 2"));
	Choice3->Append(_("clip 3"));
	Choice3->Append(_("clip 4"));
	Choice2 = new wxChoice(Panel4, ID_CHOICE3, wxPoint(64,104), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice2->Append(_("clip 1"));
	Choice2->Append(_("clip 2"));
	Choice2->Append(_("clip 3"));
	Choice2->Append(_("clip 4"));
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&moConfigurationAdvancedOutput::OnPanel1Paint,0,this);
	Panel2->Connect(wxEVT_PAINT,(wxObjectEventFunction)&moConfigurationAdvancedOutput::OnPanel2Paint,0,this);
	//*)
}

moConfigurationAdvancedOutput::~moConfigurationAdvancedOutput()
{
	//(*Destroy(moConfigurationAdvancedOutput)
	//*)
}


void moConfigurationAdvancedOutput::OnPanel2Paint(wxPaintEvent& event)
{
}

void moConfigurationAdvancedOutput::OnPanel1Paint(wxPaintEvent& event)
{
}
