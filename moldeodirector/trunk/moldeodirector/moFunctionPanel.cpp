#include "moFunctionPanel.h"

//(*InternalHeaders(moFunctionPanel)
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moFunctionPanel)
const long moFunctionPanel::ID_FUNCTIONTEXTCTRL = wxNewId();
const long moFunctionPanel::ID_STATICBITMAP1 = wxNewId();
const long moFunctionPanel::ID_PANELPLOT2D = wxNewId();
const long moFunctionPanel::ID_STATICTEXT1 = wxNewId();
const long moFunctionPanel::ID_SLIDERNUMBER = wxNewId();
const long moFunctionPanel::ID_TEXTCTRL1 = wxNewId();
const long moFunctionPanel::ID_TEXTCTRLMAX = wxNewId();
const long moFunctionPanel::ID_BUTTON5 = wxNewId();
const long moFunctionPanel::ID_BUTTON1 = wxNewId();
const long moFunctionPanel::ID_BUTTON4 = wxNewId();
const long moFunctionPanel::ID_BUTTON2 = wxNewId();
const long moFunctionPanel::ID_BUTTON7 = wxNewId();
const long moFunctionPanel::ID_BUTTON3 = wxNewId();
const long moFunctionPanel::ID_BUTTON8 = wxNewId();
const long moFunctionPanel::ID_BUTTON9 = wxNewId();
const long moFunctionPanel::ID_BUTTON6 = wxNewId();
const long moFunctionPanel::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moFunctionPanel,wxPanel)
	//(*EventTable(moFunctionPanel)
	//*)
END_EVENT_TABLE()

moFunctionPanel::moFunctionPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moFunctionPanel)
	Create(parent, id, wxDefaultPosition, wxSize(224,300), wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(0,0,0));
	FunctionTextCtrl = new wxTextCtrl(this, ID_FUNCTIONTEXTCTRL, wxEmptyString, wxPoint(8,56), wxSize(144,32), 0, wxDefaultValidator, _T("ID_FUNCTIONTEXTCTRL"));
	PanelPlot2d = new wxPanel(this, ID_PANELPLOT2D, wxPoint(8,120), wxSize(144,144), wxTAB_TRAVERSAL, _T("ID_PANELPLOT2D"));
	PanelPlot2d->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
	StaticBitmap1 = new wxStaticBitmap(PanelPlot2d, ID_STATICBITMAP1, wxBitmap(wxImage(_T("../../art/icons/functiontest.png")).Rescale(wxSize(136,72).GetWidth(),wxSize(136,72).GetHeight())), wxPoint(0,8), wxSize(136,72), 0, _T("ID_STATICBITMAP1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Type: Function"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->SetForegroundColour(wxColour(255,255,255));
	SliderNumber = new wxSlider(this, ID_SLIDERNUMBER, 0, 0, 100, wxPoint(0,24), wxSize(152,24), 0, wxDefaultValidator, _T("ID_SLIDERNUMBER"));
	TextCtrlMin = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxPoint(152,24), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrlMax = new wxTextCtrl(this, ID_TEXTCTRLMAX, _("100"), wxPoint(200,24), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLMAX"));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(160,56), wxSize(88,164), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	ButtonCos = new wxButton(Panel1, ID_BUTTON5, _("cos"), wxPoint(0,0), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	ButtonSin = new wxButton(Panel1, ID_BUTTON1, _("sin"), wxPoint(32,0), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	ButtonTan = new wxButton(Panel1, ID_BUTTON4, _("tan"), wxPoint(0,24), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	ButtonLog = new wxButton(Panel1, ID_BUTTON2, _("log"), wxPoint(32,24), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	ButtonExp = new wxButton(Panel1, ID_BUTTON7, _("exp"), wxPoint(32,48), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	ButtonSqr = new wxButton(Panel1, ID_BUTTON3, _("sqr"), wxPoint(0,48), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	ButtonSqrt = new wxButton(Panel1, ID_BUTTON8, _("sqrt"), wxPoint(0,72), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	Button1x = new wxButton(Panel1, ID_BUTTON9, _("1/x"), wxPoint(32,72), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	ButtonCosSin = new wxButton(Panel1, ID_BUTTON6, _("cos*sin"), wxPoint(0,96), wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));

	Connect(ID_FUNCTIONTEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moFunctionPanel::OnFunctionTextCtrlText);
	//*)

}

moFunctionPanel::~moFunctionPanel()
{
	//(*Destroy(moFunctionPanel)
	//*)
}

void
moFunctionPanel::Inspect( moValueDescriptor p_ValueDescriptor ) {

    //SIEMPRE GENERAR UN SWITCH CASE DEL TIPO, PARA EVITAR MAL USOS DEL INSPECT CON VALORES
    //QUE NO CORRESPONDEN

    switch(p_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {

        case MO_PARAM_NUMERIC:
            FunctionTextCtrl->ChangeValue( (wxChar*)(char*)p_ValueDescriptor.GetValue().GetSubValue(0).ToText() );
            break;

        case MO_PARAM_ALPHA:
        case MO_PARAM_SYNC:
        case MO_PARAM_PHASE:
        case MO_PARAM_FUNCTION:
            // Linea gustavo
            FunctionTextCtrl->ChangeValue( (wxChar*)(char*)p_ValueDescriptor.GetValue().GetSubValue(0).Text() );
            break;
        default:
            return;
            break;

    }

    m_ValueDescriptor = p_ValueDescriptor;

}


void moFunctionPanel::OnFunctionTextCtrlText(wxCommandEvent& event)
{
    int ii;

    switch(m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {

        case MO_PARAM_NUMERIC:
            ii = atoi( (const char*)FunctionTextCtrl->GetValue().c_str() );
            m_ValueDescriptor.GetValue().GetSubValue(0).SetInt(ii);
            break;

        case MO_PARAM_ALPHA:
        case MO_PARAM_SYNC:
        case MO_PARAM_PHASE:
        case MO_PARAM_FUNCTION:
            m_ValueDescriptor.GetValue().GetSubValue(0).SetText( (char*)(wxChar*) FunctionTextCtrl->GetValue().c_str() );
            break;
        default:
            return;
            break;
    }

    SetValue( m_ValueDescriptor );
}
