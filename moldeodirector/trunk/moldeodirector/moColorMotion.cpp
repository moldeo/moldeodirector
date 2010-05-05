#include "moColorMotion.h"

//(*InternalHeaders(moColorMotion)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include <wx/colordlg.h>
#include <wx/colour.h>

//(*IdInit(moColorMotion)
const long moColorMotion::ID_STATICBITMAP1 = wxNewId();
const long moColorMotion::ID_PANEL5 = wxNewId();
const long moColorMotion::ID_SLIDERRED = wxNewId();
const long moColorMotion::ID_SLIDERGREEN = wxNewId();
const long moColorMotion::ID_SLIDERBLUE = wxNewId();
const long moColorMotion::ID_SLIDERALPHA = wxNewId();
const long moColorMotion::ID_BITMAPBUTTON1 = wxNewId();
const long moColorMotion::ID_PANELCOLOR = wxNewId();
const long moColorMotion::ID_STATICBITMAP2 = wxNewId();
const long moColorMotion::ID_PANEL3 = wxNewId();
const long moColorMotion::ID_TEXTCTRLRED = wxNewId();
const long moColorMotion::ID_TEXTCTRLGREEN = wxNewId();
const long moColorMotion::ID_TEXTCTRLBLUE = wxNewId();
const long moColorMotion::ID_TEXTCTRLALPHA = wxNewId();
const long moColorMotion::ID_COMBOBOXCOLORPRESETS = wxNewId();
const long moColorMotion::ID_PANEL2 = wxNewId();
//*)

const long moColorMotion::ID_LEVELRED = wxNewId();
const long moColorMotion::ID_LEVELGREEN = wxNewId();
const long moColorMotion::ID_LEVELBLUE = wxNewId();
const long moColorMotion::ID_LEVELALPHA = wxNewId();

BEGIN_EVENT_TABLE(moColorMotion,wxPanel)
	//(*EventTable(moColorMotion)
	//*)
	EVT_MOUSE_EVENTS( moColorMotion::OnMouseEvent )
END_EVENT_TABLE()

moColorMotion::moColorMotion(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moColorMotion)
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(352,221), wxTAB_TRAVERSAL|wxCLIP_CHILDREN, _T("wxID_ANY"));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(192,8), wxSize(184,272), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(0,0,0));
	PanelTranslateCoords = new wxPanel(Panel2, ID_PANEL5, wxPoint(8,8), wxSize(44,62), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	StaticBitmap1 = new wxStaticBitmap(PanelTranslateCoords, ID_STATICBITMAP1, wxBitmap(wxImage(_T("../../doc/icons/colors.png"))), wxPoint(0,0), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
	SliderRed = new wxSlider(Panel2, ID_SLIDERRED, 0, 0, 255, wxPoint(56,8), wxSize(56,16), 0, wxDefaultValidator, _T("ID_SLIDERRED"));
	SliderGreen = new wxSlider(Panel2, ID_SLIDERGREEN, 0, 0, 255, wxPoint(56,24), wxSize(56,16), 0, wxDefaultValidator, _T("ID_SLIDERGREEN"));
	SliderBlue = new wxSlider(Panel2, ID_SLIDERBLUE, 0, 0, 255, wxPoint(56,40), wxSize(56,16), 0, wxDefaultValidator, _T("ID_SLIDERBLUE"));
	SliderAlpha = new wxSlider(Panel2, ID_SLIDERALPHA, 0, 0, 255, wxPoint(56,56), wxSize(56,16), 0, wxDefaultValidator, _T("ID_SLIDERALPHA"));
	BitmapButton1 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("../../doc/icons/pickcolor.png"))), wxPoint(128,8), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BitmapButton1->SetDefault();
	PanelColor = new wxPanel(Panel2, ID_PANELCOLOR, wxPoint(128,40), wxSize(32,32), wxTAB_TRAVERSAL, _T("ID_PANELCOLOR"));
	PanelColor->SetBackgroundColour(wxColour(255,255,255));
	Panel3 = new wxPanel(Panel2, ID_PANEL3, wxPoint(8,96), wxSize(38,62), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	StaticBitmap2 = new wxStaticBitmap(Panel3, ID_STATICBITMAP2, wxBitmap(wxImage(_T("../../doc/icons/colors.png"))), wxPoint(0,0), wxDefaultSize, 0, _T("ID_STATICBITMAP2"));
	TextCtrlRed = new wxTextCtrl(Panel2, ID_TEXTCTRLRED, wxEmptyString, wxPoint(56,96), wxSize(88,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLRED"));
	TextCtrlGreen = new wxTextCtrl(Panel2, ID_TEXTCTRLGREEN, wxEmptyString, wxPoint(56,112), wxSize(88,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLGREEN"));
	TextCtrlBlue = new wxTextCtrl(Panel2, ID_TEXTCTRLBLUE, wxEmptyString, wxPoint(56,128), wxSize(88,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLBLUE"));
	TextCtrlAlpha = new wxTextCtrl(Panel2, ID_TEXTCTRLALPHA, wxEmptyString, wxPoint(56,144), wxSize(88,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLALPHA"));
	ComboBoxMotionColorPresets = new wxComboBox(Panel2, ID_COMBOBOXCOLORPRESETS, wxEmptyString, wxPoint(56,168), wxSize(88,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOXCOLORPRESETS"));
	ComboBoxMotionColorPresets->Append(_("Random colors"));
	ComboBoxMotionColorPresets->Append(_("Cyclic conic"));
	ComboBoxMotionColorPresets->Append(_("Cyclic cubic"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Grayscale"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Red"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Green"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Blue"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Yellow"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Cyan"));
	ComboBoxMotionColorPresets->Append(_("Cyclic Magenta"));
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_SLIDERRED,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moColorMotion::OnSliderRedCmdScroll);
	Connect(ID_SLIDERRED,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moColorMotion::OnSliderRedCmdScroll);
	Connect(ID_SLIDERGREEN,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moColorMotion::OnSliderGreenCmdScroll);
	Connect(ID_SLIDERGREEN,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moColorMotion::OnSliderGreenCmdScroll);
	Connect(ID_SLIDERBLUE,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moColorMotion::OnSliderBlueCmdScroll);
	Connect(ID_SLIDERBLUE,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moColorMotion::OnSliderBlueCmdScroll);
	Connect(ID_SLIDERALPHA,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moColorMotion::OnSliderAlphaCmdScroll);
	Connect(ID_SLIDERALPHA,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moColorMotion::OnSliderAlphaCmdScroll);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moColorMotion::OnButtonPickColorClick);
	Connect(ID_TEXTCTRLRED,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlRedText);
	Connect(ID_TEXTCTRLGREEN,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlGreenText);
	Connect(ID_TEXTCTRLBLUE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlBlueText);
	Connect(ID_TEXTCTRLALPHA,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlAlphaText);
	Connect(ID_COMBOBOXCOLORPRESETS,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&moColorMotion::OnComboBoxMotionColorPresetsSelect);
	//*)

	m_pLevelRedCtrl =  new wxMoLevelCtrl(Panel2, moColorMotion::ID_LEVELRED, 50, 0 , 100, SliderRed->GetPosition(), SliderRed->GetSize() , 0, wxDefaultValidator, _T("ID_LEVELRED") );
    Connect(moColorMotion::ID_LEVELRED, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelRed );
	if (SliderRed) SliderRed->Destroy();

	m_pLevelGreenCtrl =  new wxMoLevelCtrl(Panel2, moColorMotion::ID_LEVELGREEN, 50, 0 , 100, SliderGreen->GetPosition(), SliderGreen->GetSize() , 0, wxDefaultValidator, _T("ID_LEVELGREEN") );
    Connect(moColorMotion::ID_LEVELGREEN, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelGreen );
	if (SliderGreen) SliderGreen->Destroy();

	m_pLevelBlueCtrl =  new wxMoLevelCtrl(Panel2, moColorMotion::ID_LEVELBLUE, 50, 0 , 100, SliderBlue->GetPosition(), SliderBlue->GetSize() , 0, wxDefaultValidator, _T("ID_LEVELBLUE") );
    Connect(moColorMotion::ID_LEVELBLUE, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelBlue );
	if (SliderBlue) SliderBlue->Destroy();

	m_pLevelAlphaCtrl =  new wxMoLevelCtrl(Panel2, moColorMotion::ID_LEVELALPHA, 50, 0 , 100, SliderAlpha->GetPosition(), SliderAlpha->GetSize() , 0, wxDefaultValidator, _T("ID_LEVELALPHA") );
    Connect( moColorMotion::ID_LEVELALPHA, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelAlpha );
	if (SliderAlpha) SliderAlpha->Destroy();

}

moColorMotion::~moColorMotion()
{
	//(*Destroy(moColorMotion)
	//*)
}

void moColorMotion::OnMouseEvent( wxMouseEvent& event ) {
    Log(  moText("mouse") );
    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        GetParent()->ProcessEvent(event);

        //OpenMob( m_MobDescriptor );
    }
    event.Skip();

}

void moColorMotion::Inspect( moValueDescriptor p_ValueDescriptor ) {

    m_ValueDescriptor = p_ValueDescriptor;

    if (m_ValueDescriptor.GetValue().GetSubValueCount()==4) {

        //tiene un shader aplicado????
        TextCtrlRed->SetValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(0).Text());
        TextCtrlGreen->SetValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(1).Text());
        TextCtrlBlue->SetValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(2).Text());
        TextCtrlAlpha->SetValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(3).Text());

        moValue& pValue( m_ValueDescriptor.GetValue() );

        m_pLevelRedCtrl->ChangeValue( atoi( pValue[0].Text() ) );
        m_pLevelGreenCtrl->ChangeValue( atoi( pValue[1].Text() )  );
        m_pLevelBlueCtrl->ChangeValue( atoi( pValue[2].Text() )  );
        m_pLevelAlphaCtrl->ChangeValue( atoi( pValue[3].Text() )  );

    }

}

void moColorMotion::OnLevelRed(wxCommandEvent& event) {
    Log(  FloatToStr( (float) event.GetInt() / 100.0 ) );
    TextCtrlRed->SetValue( (wxChar*)(char*) FloatToStr( (float) event.GetInt() / 100.0 ) );

}

void moColorMotion::OnLevelGreen(wxCommandEvent& event) {
    Log(  FloatToStr( (float) event.GetInt() / 100.0 ) );
    TextCtrlGreen->SetValue( (wxChar*)(char*) FloatToStr( (float) event.GetInt() / 100.0 ) );

}

void moColorMotion::OnLevelBlue(wxCommandEvent& event) {
    Log(  FloatToStr( (float) event.GetInt() / 100.0 ) );
    TextCtrlBlue->SetValue( (wxChar*)(char*) FloatToStr( (float) event.GetInt() / 100.0 ) );

}

void moColorMotion::OnLevelAlpha(wxCommandEvent& event) {
    Log(  FloatToStr( (float) event.GetInt() / 100.0 ) );
    TextCtrlAlpha->SetValue( (wxChar*)(char*) FloatToStr( (float) event.GetInt() / 100.0 ) );

}

void moColorMotion::OnTextCtrlRedText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)TextCtrlRed->GetValue().c_str() ) );

    SetValue( m_ValueDescriptor );
}

void moColorMotion::OnTextCtrlGreenText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(1).SetText( moText((char*)(wxChar*)TextCtrlGreen->GetValue().c_str() ) );

    SetValue( m_ValueDescriptor );
}

void moColorMotion::OnTextCtrlBlueText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(2).SetText( moText((char*)(wxChar*)TextCtrlBlue->GetValue().c_str() ) );

    SetValue( m_ValueDescriptor );
}

void moColorMotion::OnTextCtrlAlphaText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(3).SetText( moText((char*)(wxChar*)TextCtrlAlpha->GetValue().c_str() ) );

    SetValue( m_ValueDescriptor );
}

void moColorMotion::OnSliderRedCmdScroll(wxScrollEvent& event)
{
    TextCtrlRed->SetValue( (wxChar*)(char*) FloatToStr( (float)SliderRed->GetValue() / 255.0 ) );
}

void moColorMotion::OnSliderGreenCmdScroll(wxScrollEvent& event)
{
    TextCtrlGreen->SetValue( (wxChar*)(char*) FloatToStr( (float)SliderGreen->GetValue() / 255.0 ) );
}

void moColorMotion::OnSliderBlueCmdScroll(wxScrollEvent& event)
{
    TextCtrlBlue->SetValue( (wxChar*)(char*) FloatToStr( (float)SliderBlue->GetValue() / 255.0 ) );
}

void moColorMotion::OnSliderAlphaCmdScroll(wxScrollEvent& event)
{
    TextCtrlAlpha->SetValue( (wxChar*)(char*) FloatToStr( (float)SliderAlpha->GetValue() / 255.0 ) );
}


void moColorMotion::OnButtonPickColorClick(wxCommandEvent& event)
{
    wxColourDialog* pColourDlg = new wxColourDialog(this);

    if ( pColourDlg->ShowModal()==wxID_OK ) {
        wxColour pColour = pColourDlg->GetColourData().GetColour();

        TextCtrlRed->SetValue( (wxChar*)(char*) FloatToStr( (float)pColour.Red()/255.0) );
        TextCtrlGreen->SetValue( (wxChar*)(char*) FloatToStr( (float)pColour.Green()/255.0) );
        TextCtrlBlue->SetValue( (wxChar*)(char*) FloatToStr( (float)pColour.Blue()/255.0) );
        TextCtrlAlpha->SetValue( (wxChar*)(char*) FloatToStr( (float)pColour.Alpha()/255.0) );

        PanelColor->SetBackgroundColour( pColour );
        PanelColor->Refresh();

    }
}

void moColorMotion::OnComboBoxMotionColorPresetsSelect(wxCommandEvent& event)
{
/*
Random colors
Cyclic conic
Cyclic cubic
Cyclic Grayscale
Cyclic Red
Cyclic Green
Cyclic Blue
Cyclic Yellow
Cyclic Cyan
Cyclic Magenta
*/
        switch(event.GetSelection()) {
            case 0://Random colors
                TextCtrlRed->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t+pi/2) ")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*sin(4*t+pi/3) ")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*sin(4*t+3*pi)*cos(t) ")) );
                break;
            case 1://Cyclic conic
                TextCtrlRed->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t+pi/4) ")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*sin(3*t+pi/3) ")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*sin(4*t+3*pi)*cos(t) ")) );
                break;
            case 2://Cyclic cubic
                TextCtrlRed->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t+pi/2) ")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*sin(2*t+pi/3) ")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*sin(2*t+3*pi)*cos(t) ")) );
                break;
            case 3://Cyclic Grayscale
                TextCtrlRed->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                break;
            case 4://Cyclic Red
                TextCtrlRed->SetValue( wxString(_T("0.5 + 0.5*cos(4*t) ")) );
                TextCtrlGreen->SetValue( wxString(_T("0.5")) );
                TextCtrlBlue->SetValue( wxString(_T("0.5")) );
                break;
            case 5://Cyclic Green
                TextCtrlRed->SetValue( wxString(_T("0.5")) );
                TextCtrlGreen->SetValue( wxString(_T("0.5 + 0.5*cos(4*t) ")) );
                TextCtrlBlue->SetValue( wxString(_T("0.5")) );
                break;
            case 6://Cyclic Blue
                TextCtrlRed->SetValue( wxString(_T("0.5")) );
                TextCtrlGreen->SetValue( wxString(_T("0.5")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                break;
            case 7://Cyclic Yellow
                TextCtrlRed->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                TextCtrlBlue->SetValue( wxString(_T("0.5 ")) );
                break;
            case 8://Cyclic Cyan
                TextCtrlRed->SetValue( wxString(_T(" 0.5")) );
                TextCtrlGreen->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                TextCtrlBlue->SetValue( wxString(_T(" 0.5 + 0.5*cos(4*t) ")) );
                break;
            case 9://Cyclic Magenta
                TextCtrlRed->SetValue( wxString(_T("0.5 + 0.5*cos(4*t)")) );
                TextCtrlGreen->SetValue( wxString(_T("0.5")) );
                TextCtrlBlue->SetValue( wxString(_T("0.5 + 0.5*cos(4*t)")) );
                break;

        }
}
