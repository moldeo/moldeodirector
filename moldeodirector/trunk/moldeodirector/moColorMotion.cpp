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
const long moColorMotion::ID_SLIDERVALUE = wxNewId();
const long moColorMotion::ID_SLIDERSATURATION = wxNewId();
const long moColorMotion::ID_SLIDERHUE = wxNewId();
const long moColorMotion::ID_SLIDERRED = wxNewId();
const long moColorMotion::ID_SLIDERGREEN = wxNewId();
const long moColorMotion::ID_SLIDERBLUE = wxNewId();
const long moColorMotion::ID_SLIDERALPHA = wxNewId();
const long moColorMotion::ID_BITMAPBUTTONPICKCOLOR = wxNewId();
const long moColorMotion::ID_PANELCOLOR = wxNewId();
const long moColorMotion::ID_TEXTCTRLRED = wxNewId();
const long moColorMotion::ID_TEXTCTRLGREEN = wxNewId();
const long moColorMotion::ID_TEXTCTRLBLUE = wxNewId();
const long moColorMotion::ID_TEXTHTMLCOLOURCTRL = wxNewId();
const long moColorMotion::ID_TEXTCTRLALPHA = wxNewId();
const long moColorMotion::ID_COMBOBOXCOLORPRESETS = wxNewId();
const long moColorMotion::ID_STATICTEXT3 = wxNewId();
const long moColorMotion::ID_STATICTEXT4 = wxNewId();
const long moColorMotion::ID_STATICTEXT5 = wxNewId();
const long moColorMotion::ID_STATICTEXT6 = wxNewId();
const long moColorMotion::ID_STATICTEXT7 = wxNewId();
const long moColorMotion::ID_STATICTEXT9 = wxNewId();
const long moColorMotion::ID_STATICTEXT10 = wxNewId();
const long moColorMotion::ID_STATICTEXT8 = wxNewId();
const long moColorMotion::ID_STATICTEXT2 = wxNewId();
const long moColorMotion::ID_STATICTEXT1 = wxNewId();
const long moColorMotion::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moColorMotion,wxPanel)
	//(*EventTable(moColorMotion)
	//*)
	EVT_MOUSE_EVENTS( moColorMotion::OnMouseEvent )
END_EVENT_TABLE()

moColorMotion::moColorMotion(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moColorMotion)
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(434,210), wxTAB_TRAVERSAL|wxCLIP_CHILDREN, _T("wxID_ANY"));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	FlexGridSizer1->AddGrowableRow(1);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(192,8), wxSize(356,200), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(0,0,0));
	SliderValue = new wxMoColourLevelCtrl(Panel2, ID_SLIDERVALUE, 0, 0, 255, wxPoint(56,56), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERVALUE"));
	SliderSaturation = new wxMoColourLevelCtrl(Panel2, ID_SLIDERSATURATION, 0, 0, 255, wxPoint(56,32), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERSATURATION"));
	SliderHue = new wxMoColourLevelCtrl(Panel2, ID_SLIDERHUE, 0, 0, 255, wxPoint(56,8), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERHUE"));
	SliderRed = new wxMoColourLevelCtrl(Panel2, ID_SLIDERRED, 0, 0, 255, wxPoint(56,80), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERRED"));
	SliderGreen = new wxMoColourLevelCtrl(Panel2, ID_SLIDERGREEN, 0, 0, 255, wxPoint(56,104), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERGREEN"));
	SliderBlue = new wxMoColourLevelCtrl(Panel2, ID_SLIDERBLUE, 0, 0, 255, wxPoint(56,128), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERBLUE"));
	SliderAlpha = new wxMoColourLevelCtrl(Panel2, ID_SLIDERALPHA, 0, 0, 255, wxPoint(56,152), wxSize(96,16), 0, wxDefaultValidator, _T("ID_SLIDERALPHA"));
	BitmapButtonPickColor = new wxBitmapButton(Panel2, ID_BITMAPBUTTONPICKCOLOR, wxBitmap(wxImage(_T("../../data/icons/pickcolor.png"))), wxPoint(160,172), wxSize(32,32), wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTONPICKCOLOR"));
	BitmapButtonPickColor->SetDefault();
	BitmapButtonPickColor->SetForegroundColour(wxColour(255,255,255));
	BitmapButtonPickColor->SetBackgroundColour(wxColour(0,0,0));
	ColourPanel = new wxMoColourPanel(Panel2, ID_PANELCOLOR, wxPoint(56,176), wxSize(96,32), wxTAB_TRAVERSAL, _T("ID_PANELCOLOR"));
	ColourPanel->SetBackgroundColour(wxColour(255,255,255));
	TextCtrlRed = new wxTextCtrl(Panel2, ID_TEXTCTRLRED, wxEmptyString, wxPoint(160,78), wxSize(184,16), wxNO_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLRED"));
	TextCtrlGreen = new wxTextCtrl(Panel2, ID_TEXTCTRLGREEN, wxEmptyString, wxPoint(160,102), wxSize(184,16), wxNO_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLGREEN"));
	TextCtrlBlue = new wxTextCtrl(Panel2, ID_TEXTCTRLBLUE, wxEmptyString, wxPoint(160,126), wxSize(184,16), wxNO_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLBLUE"));
	TextHtmlColourCtrl = new wxTextCtrl(Panel2, ID_TEXTHTMLCOLOURCTRL, wxEmptyString, wxPoint(56,216), wxSize(96,16), 0, wxDefaultValidator, _T("ID_TEXTHTMLCOLOURCTRL"));
	TextCtrlAlpha = new wxTextCtrl(Panel2, ID_TEXTCTRLALPHA, wxEmptyString, wxPoint(160,152), wxSize(184,16), wxNO_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLALPHA"));
	ComboBoxMotionColorPresets = new wxComboBox(Panel2, ID_COMBOBOXCOLORPRESETS, wxEmptyString, wxPoint(160,48), wxSize(112,21), 0, 0, wxNO_BORDER, wxDefaultValidator, _T("ID_COMBOBOXCOLORPRESETS"));
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
	StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Hue"), wxPoint(16,8), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3->SetForegroundColour(wxColour(255,255,255));
	StaticText4 = new wxStaticText(Panel2, ID_STATICTEXT4, _("Lum"), wxPoint(16,56), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText4->SetForegroundColour(wxColour(255,255,255));
	StaticText5 = new wxStaticText(Panel2, ID_STATICTEXT5, _("Red"), wxPoint(16,80), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText5->SetForegroundColour(wxColour(255,255,255));
	StaticText6 = new wxStaticText(Panel2, ID_STATICTEXT6, _("Green"), wxPoint(16,104), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText6->SetForegroundColour(wxColour(255,255,255));
	StaticText7 = new wxStaticText(Panel2, ID_STATICTEXT7, _("Blue"), wxPoint(16,128), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticText7->SetForegroundColour(wxColour(255,255,255));
	StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT9, _("Alpha"), wxPoint(16,152), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticText9->SetForegroundColour(wxColour(255,255,255));
	StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT10, _("Color"), wxPoint(16,180), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText10->SetForegroundColour(wxColour(255,255,255));
	StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT8, _("Color Motion"), wxPoint(160,32), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticText8->SetForegroundColour(wxColour(255,255,255));
	StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("Pick a color"), wxPoint(192,182), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText2->SetForegroundColour(wxColour(255,255,255));
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Sat"), wxPoint(16,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->SetForegroundColour(wxColour(255,255,255));
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_BITMAPBUTTONPICKCOLOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moColorMotion::OnButtonPickColorClick);
	Connect(ID_TEXTCTRLRED,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlRedText);
	Connect(ID_TEXTCTRLGREEN,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlGreenText);
	Connect(ID_TEXTCTRLBLUE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlBlueText);
	Connect(ID_TEXTHTMLCOLOURCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextHtmlColourCtrlText);
	Connect(ID_TEXTCTRLALPHA,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moColorMotion::OnTextCtrlAlphaText);
	Connect(ID_COMBOBOXCOLORPRESETS,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&moColorMotion::OnComboBoxMotionColorPresetsSelect);
	//*)

  SliderRed->Init( wxMoColorLevelCtrl::RED );
  Connect(moColorMotion::ID_SLIDERRED, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelRed );

  SliderGreen->Init( wxMoColorLevelCtrl::GREEN );
  Connect(moColorMotion::ID_SLIDERGREEN, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelGreen );

  SliderBlue->Init( wxMoColorLevelCtrl::BLUE );
  Connect(moColorMotion::ID_SLIDERBLUE, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelBlue );

  SliderAlpha->Init( wxMoColorLevelCtrl::ALPHA );
  Connect(moColorMotion::ID_SLIDERALPHA, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelAlpha );

  SliderHue->Init( wxMoColorLevelCtrl::HUE );
  Connect(moColorMotion::ID_SLIDERHUE,  wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelHue );

  SliderSaturation->Init( wxMoColorLevelCtrl::SATURATION );
  Connect(moColorMotion::ID_SLIDERSATURATION, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelSaturation );

  SliderValue->Init( wxMoColorLevelCtrl::VALUE );
  Connect(moColorMotion::ID_SLIDERVALUE, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moColorMotion::OnLevelValue );


  SliderRed->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderRed->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderRed->SetColourPanel( ColourPanel );

  SliderGreen->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderGreen->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderGreen->SetColourPanel( ColourPanel );

  SliderBlue->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderBlue->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderBlue->SetColourPanel( ColourPanel );

  SliderAlpha->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderAlpha->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderAlpha->SetColourPanel( ColourPanel );

  SliderHue->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderHue->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderHue->SetColourPanel( ColourPanel );

  SliderSaturation->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderSaturation->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderSaturation->SetColourPanel( ColourPanel );

  SliderValue->SetRGBAColorComponents( SliderRed, SliderGreen, SliderBlue, SliderAlpha );
  SliderValue->SetHSVColorComponents( SliderHue, SliderSaturation, SliderValue );
  SliderValue->SetColourPanel( ColourPanel );

}

moColorMotion::~moColorMotion()
{
	//(*Destroy(moColorMotion)
	//*)
}

void moColorMotion::OnMouseEvent( wxMouseEvent& event ) {
    //Log(  moText("mouse") );
    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        GetParent()->ProcessEvent(event);

        //OpenMob( m_MobDescriptor );
    }
    event.Skip();

}

void
moColorMotion::UpdateColour( wxColour p_Colour ) {

  UpdateColour( FloatToStr( p_Colour.Red()/255.0),
                FloatToStr( p_Colour.Green()/255.0),
                FloatToStr( p_Colour.Blue()/255.0),
                FloatToStr( p_Colour.Alpha()/255.0)
                );

}

void
moColorMotion::UpdateColour( moText red, moText green, moText blue, moText alpha ) {

  moValueDescriptor pValueDescriptor;

  ///atencion! aquí lo que hacemos es crear una copia para enviar el nuevo dato
  /// de esta manera si existe un error, no necesitamos modificar nada, el core lo hará automáticamente
  /// a través de la función ValueUpdated()
  pValueDescriptor = m_ValueDescriptor;

  moValue& pValue( pValueDescriptor.GetValue() );

  if (red.Length() && red!=pValue.GetSubValue(MO_RED).Text()) {
      pValue.GetSubValue(MO_RED).SetText( red );
  }

  if (green.Length() && green!=pValue.GetSubValue(MO_GREEN).Text()) {
    pValue.GetSubValue(MO_GREEN).SetText( green );
  }

  if (blue.Length() && blue!=pValue.GetSubValue(MO_BLUE).Text()) {
    pValue.GetSubValue(MO_BLUE).SetText( blue );
  }

  if ( alpha.Length() && alpha!=pValue.GetSubValue(MO_ALPHA).Text()) {
    pValue.GetSubValue(MO_ALPHA).SetText( alpha );
  }

  ///Avizamos al core del cambio para que refleje los cambios
  SetValue( pValueDescriptor );

}

/// La funcion Inspect siempre debe ser pasiva. O sea no reflejar cambios...

void moColorMotion::Inspect( moValueDescriptor p_ValueDescriptor ) {

    ///traer el valor completo...actualizado
    m_ValueDescriptor = GetValue( p_ValueDescriptor );

    moValue& mValue( m_ValueDescriptor.GetValue() );

    if ( mValue.GetSubValueCount()==4) {

        if (mValue[0].GetType()!=MO_VALUE_FUNCTION ||
        mValue[1].GetType()!=MO_VALUE_FUNCTION ||
        mValue[2].GetType()!=MO_VALUE_FUNCTION ||
        mValue[3].GetType()!=MO_VALUE_FUNCTION) {
          LogError(moText(" value data is not MO_VALUE_FUNCTION"));
          return;
        } else {
          mValue[0].Eval();
          mValue[1].Eval();
          mValue[2].Eval();
          mValue[3].Eval();
        }

        m_ActualColour = wxColour( mValue[0].Float()*255,
                        mValue[1].Float()*255,
                        mValue[2].Float()*255,
                        mValue[3].Float()*255);

        SliderRed->SetColourValue( m_ActualColour , true ); ///propagate to other controls

        TextCtrlRed->ChangeValue( moText2Wx(mValue.GetSubValue(0).Text()) );
        TextCtrlGreen->ChangeValue( moText2Wx(mValue.GetSubValue(1).Text()) );
        TextCtrlBlue->ChangeValue( moText2Wx(mValue.GetSubValue(2).Text()) );
        TextCtrlAlpha->ChangeValue( moText2Wx(mValue.GetSubValue(3).Text()) );

        TextHtmlColourCtrl->ChangeValue( m_ActualColour.GetAsString(wxC2S_HTML_SYNTAX) );

    }

}

void moColorMotion::OnLevelHue(wxCommandEvent& event) {
    UpdateColour( FloatToStr(SliderHue->RedNormal()), FloatToStr(SliderHue->GreenNormal()), FloatToStr(SliderHue->BlueNormal()), "");

}

void moColorMotion::OnLevelSaturation(wxCommandEvent& event) {
    UpdateColour( FloatToStr(SliderHue->RedNormal()), FloatToStr(SliderHue->GreenNormal()), FloatToStr(SliderHue->BlueNormal()), "");
}

void moColorMotion::OnLevelValue(wxCommandEvent& event) {
    UpdateColour( FloatToStr(SliderHue->RedNormal()), FloatToStr(SliderHue->GreenNormal()), FloatToStr(SliderHue->BlueNormal()), "");
}


void moColorMotion::OnLevelRed(wxCommandEvent& event) {
    UpdateColour( FloatToStr( SliderRed->RedNormal() ), "", "", "" );

}

void moColorMotion::OnLevelGreen(wxCommandEvent& event) {
    UpdateColour( "" , FloatToStr( SliderGreen->GreenNormal() ), "", "" );
}

void moColorMotion::OnLevelBlue(wxCommandEvent& event) {
    UpdateColour( "", "" , FloatToStr( SliderBlue->BlueNormal() ), "");
}

void moColorMotion::OnLevelAlpha(wxCommandEvent& event) {
    UpdateColour( "", "" , "", FloatToStr( SliderAlpha->GetColourValue().Alpha()/255.0 ));
}

void moColorMotion::OnTextCtrlRedText(wxCommandEvent& event)
{
    UpdateColour( moWx2Text(TextCtrlRed->GetValue()), "", "", "" );

}

void moColorMotion::OnTextCtrlGreenText(wxCommandEvent& event)
{
  UpdateColour( "", moWx2Text(TextCtrlGreen->GetValue()), "", "" );
}

void moColorMotion::OnTextCtrlBlueText(wxCommandEvent& event)
{
  UpdateColour( "", "", moWx2Text(TextCtrlBlue->GetValue()), "");
}

void moColorMotion::OnTextCtrlAlphaText(wxCommandEvent& event)
{
  UpdateColour( "", "", "", moWx2Text(TextCtrlAlpha->GetValue()) );
}

void moColorMotion::OnButtonPickColorClick(wxCommandEvent& event)
{
    wxColourDialog* pColourDlg = new wxColourDialog(this);

    if ( pColourDlg->ShowModal()==wxID_OK ) {
      UpdateColour( pColourDlg->GetColourData().GetColour() );
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

void moColorMotion::OnTextHtmlColourCtrlText(wxCommandEvent& event)
{
    wxColour newColour;
    if (newColour.Set( TextHtmlColourCtrl->GetValue() ) ) {
      UpdateColour( newColour );
    }
}
