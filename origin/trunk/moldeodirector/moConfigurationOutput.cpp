#include "moConfigurationOutput.h"

//(*InternalHeaders(moConfigurationOutput)
#include <wx/intl.h>
#include <wx/string.h>
//*)



//(*IdInit(moConfigurationOutput)
const long moConfigurationOutput::ID_STATICBOX1 = wxNewId();
const long moConfigurationOutput::ID_STATICTEXT1 = wxNewId();
const long moConfigurationOutput::ID_STATICTEXT2 = wxNewId();
const long moConfigurationOutput::ID_STATICBOX2 = wxNewId();
const long moConfigurationOutput::ID_SPINCTRL1 = wxNewId();
const long moConfigurationOutput::ID_SPINCTRL2 = wxNewId();
const long moConfigurationOutput::ID_COMBOBOX1 = wxNewId();
const long moConfigurationOutput::ID_COMBOBOX2 = wxNewId();
const long moConfigurationOutput::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moConfigurationOutput,wxPanel)
	//(*EventTable(moConfigurationOutput)
	//*)
END_EVENT_TABLE()

moConfigurationOutput::moConfigurationOutput(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moConfigurationOutput)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(432,114), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Render resolution"), wxPoint(16,16), wxSize(416,128), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Width"), wxPoint(40,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Height"), wxPoint(40,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Output screen"), wxPoint(16,152), wxSize(416,96), 0, _T("ID_STATICBOX2"));
	SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxPoint(80,40), wxSize(72,21), 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	SpinCtrl1->SetValue(_T("0"));
	SpinCtrl2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxPoint(80,72), wxSize(72,21), 0, 0, 100, 0, _T("ID_SPINCTRL2"));
	SpinCtrl2->SetValue(_T("0"));
	ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(224,40), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	ComboBox1->SetSelection( ComboBox1->Append(_("Choose standard resolution")) );
	ComboBox1->Append(_("640x480"));
	ComboBox1->Append(_("800x600"));
	ComboBox1->Append(_("1024x768"));
	ComboBox1->Append(_("1280x800"));
	ComboBox2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(40,176), wxSize(96,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	ComboBox2->SetSelection( ComboBox2->Append(_("Display 1")) );
	ComboBox2->Append(_("Display 2"));
	ComboBox2->Append(_("Display 3"));
	ButtonAdvancedOutput = new wxButton(this, ID_BUTTON1, _("Advanced Ouput"), wxPoint(40,216), wxSize(112,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moConfigurationOutput::OnButtonAdvancedOutputClick);
	//*)


}

moConfigurationOutput::~moConfigurationOutput()
{
	//(*Destroy(moConfigurationOutput)
	//*)
}


void moConfigurationOutput::OnButtonAdvancedOutputClick(wxCommandEvent& event)
{

    m_pAdvancedOutput = new moConfigurationAdvancedOutput(this);

    m_pAdvancedOutput->Show();

}

