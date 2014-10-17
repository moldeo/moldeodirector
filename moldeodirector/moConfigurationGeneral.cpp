#include "moConfigurationGeneral.h"

//(*InternalHeaders(moConfigurationGeneral)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moConfigurationGeneral)
const long moConfigurationGeneral::ID_STATICTEXT1 = wxNewId();
const long moConfigurationGeneral::ID_TEXTCTRL1 = wxNewId();
const long moConfigurationGeneral::ID_STATICTEXT2 = wxNewId();
const long moConfigurationGeneral::ID_TEXTCTRL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moConfigurationGeneral,wxPanel)
	//(*EventTable(moConfigurationGeneral)
	//*)
END_EVENT_TABLE()

moConfigurationGeneral::moConfigurationGeneral(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moConfigurationGeneral)
	Create(parent, id, wxDefaultPosition, wxSize(247,190), wxTAB_TRAVERSAL, _T("id"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Option 1"), wxPoint(24,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(24,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxPoint(152,24), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(152,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	//*)
}

moConfigurationGeneral::~moConfigurationGeneral()
{
	//(*Destroy(moConfigurationGeneral)
	//*)
}


