#include "moObjectMotion.h"

//(*InternalHeaders(moObjectMotion)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moObjectMotion)
const long moObjectMotion::ID_SLIDERTX = wxNewId();
const long moObjectMotion::ID_SLIDERTZ = wxNewId();
const long moObjectMotion::ID_SLIDERTY = wxNewId();
const long moObjectMotion::ID_TEXTCTRLTX = wxNewId();
const long moObjectMotion::ID_TEXTCTRLTY = wxNewId();
const long moObjectMotion::ID_SLIDERRZ = wxNewId();
const long moObjectMotion::ID_SLIDERSZ = wxNewId();
const long moObjectMotion::ID_SLIDERSY = wxNewId();
const long moObjectMotion::ID_TEXTCTRLRX = wxNewId();
const long moObjectMotion::ID_SLIDERRX = wxNewId();
const long moObjectMotion::ID_SLIDERRY = wxNewId();
const long moObjectMotion::ID_TEXTCTRLRY = wxNewId();
const long moObjectMotion::ID_SLIDERSX = wxNewId();
const long moObjectMotion::ID_PANEL6 = wxNewId();
const long moObjectMotion::ID_TEXTCTRLTZ = wxNewId();
const long moObjectMotion::ID_PANEL9 = wxNewId();
const long moObjectMotion::ID_PANELPOSITION = wxNewId();
const long moObjectMotion::ID_STATICBITMAP1 = wxNewId();
const long moObjectMotion::ID_PANEL5 = wxNewId();
const long moObjectMotion::ID_TEXTCTRLSZ = wxNewId();
const long moObjectMotion::ID_STATICBITMAP5 = wxNewId();
const long moObjectMotion::ID_PANEL7 = wxNewId();
const long moObjectMotion::ID_TEXTCTRLSY = wxNewId();
const long moObjectMotion::ID_STATICBITMAP3 = wxNewId();
const long moObjectMotion::ID_PANEL4 = wxNewId();
const long moObjectMotion::ID_TEXTCTRLSX = wxNewId();
const long moObjectMotion::ID_TEXTCTRLRZ = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONPOSCIRCULAR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONPOSHOR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONPOSVERT = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTON8 = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONPOSRAND = wxNewId();
const long moObjectMotion::ID_PANEL1 = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONROTCIRCULAR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONROTHOR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONROTVER = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONROTDIAG = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONROTRAND = wxNewId();
const long moObjectMotion::ID_PANEL2 = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONSCACIRCULAR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONSCAHOR = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONSCAVER = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONSCADIAG = wxNewId();
const long moObjectMotion::ID_BITMAPBUTTONSCARAND = wxNewId();
const long moObjectMotion::ID_PANEL10 = wxNewId();
const long moObjectMotion::ID_PANELTRANSLATE = wxNewId();
//*)

BEGIN_EVENT_TABLE(moObjectMotion,wxPanel)
	//(*EventTable(moObjectMotion)
	//*)
END_EVENT_TABLE()

moObjectMotion::moObjectMotion(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moObjectMotion)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(240,298), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	Panel2 = new wxPanel(this, ID_PANELTRANSLATE, wxDefaultPosition, wxSize(224,393), wxNO_BORDER|wxTAB_TRAVERSAL|wxCLIP_CHILDREN, _T("ID_PANELTRANSLATE"));
	Panel2->SetMinSize(wxSize(-1,-1));
	Panel2->SetForegroundColour(wxColour(255,255,255));
	Panel2->SetBackgroundColour(wxColour(0,0,0));
	SliderTx = new wxSlider(Panel2, ID_SLIDERTX, 0, -1000, 1000, wxPoint(48,8), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERTX"));
	SliderTz = new wxSlider(Panel2, ID_SLIDERTZ, 0, -1000, 1000, wxPoint(48,40), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERTZ"));
	SliderTy = new wxSlider(Panel2, ID_SLIDERTY, 0, -1000, 1000, wxPoint(48,24), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERTY"));
	TextCtrlTx = new wxTextCtrl(Panel2, ID_TEXTCTRLTX, wxEmptyString, wxPoint(112,8), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLTX"));
	TextCtrlTy = new wxTextCtrl(Panel2, ID_TEXTCTRLTY, wxEmptyString, wxPoint(112,24), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLTY"));
	SliderRz = new wxSlider(Panel2, ID_SLIDERRZ, 0, -180, 180, wxPoint(48,288), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERRZ"));
	SliderSz = new wxSlider(Panel2, ID_SLIDERSZ, 0, -100, 100, wxPoint(48,164), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERSZ"));
	SliderSy = new wxSlider(Panel2, ID_SLIDERSY, 0, -100, 100, wxPoint(48,148), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERSY"));
	TextCtrlRx = new wxTextCtrl(Panel2, ID_TEXTCTRLRX, wxEmptyString, wxPoint(112,256), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLRX"));
	SliderRx = new wxSlider(Panel2, ID_SLIDERRX, 0, -180, 180, wxPoint(48,256), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERRX"));
	SliderRy = new wxSlider(Panel2, ID_SLIDERRY, 0, -180, 180, wxPoint(48,272), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERRY"));
	TextCtrlRy = new wxTextCtrl(Panel2, ID_TEXTCTRLRY, wxEmptyString, wxPoint(112,272), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLRY"));
	SliderSx = new wxSlider(Panel2, ID_SLIDERSX, 0, -100, 100, wxPoint(48,132), wxSize(64,16), 0, wxDefaultValidator, _T("ID_SLIDERSX"));
	Panel4 = new wxPanel(Panel2, ID_PANEL6, wxPoint(8,56), wxSize(104,64), wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	Panel4->SetBackgroundColour(wxColour(255,255,255));
	TextCtrlTz = new wxTextCtrl(Panel2, ID_TEXTCTRLTZ, wxEmptyString, wxPoint(112,40), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLTZ"));
	Panel6 = new wxPanel(Panel2, ID_PANEL9, wxPoint(8,180), wxSize(104,64), wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	Panel6->SetBackgroundColour(wxColour(255,255,255));
	PanelPosition = new wxPanel(Panel2, ID_PANELPOSITION, wxPoint(8,304), wxSize(104,64), wxTAB_TRAVERSAL, _T("ID_PANELPOSITION"));
	PanelPosition->SetBackgroundColour(wxColour(255,255,255));
	PanelTranslateCoords = new wxPanel(Panel2, ID_PANEL5, wxPoint(8,8), wxSize(44,44), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	StaticBitmap1 = new wxStaticBitmap(PanelTranslateCoords, ID_STATICBITMAP1, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/translate.png"))), wxPoint(0,0), wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
	TextCtrlSz = new wxTextCtrl(Panel2, ID_TEXTCTRLSZ, wxEmptyString, wxPoint(112,164), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLSZ"));
	PanelScalesTxt = new wxPanel(Panel2, ID_PANEL7, wxPoint(8,256), wxSize(44,44), wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	StaticBitmap5 = new wxStaticBitmap(PanelScalesTxt, ID_STATICBITMAP5, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/rotate.png"))), wxPoint(0,0), wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP5"));
	TextCtrlSy = new wxTextCtrl(Panel2, ID_TEXTCTRLSY, wxEmptyString, wxPoint(112,148), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLSY"));
	PanelScales = new wxPanel(Panel2, ID_PANEL4, wxPoint(8,132), wxSize(44,44), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	StaticBitmap3 = new wxStaticBitmap(PanelScales, ID_STATICBITMAP3, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/scale.png"))), wxPoint(0,0), wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP3"));
	TextCtrlSx = new wxTextCtrl(Panel2, ID_TEXTCTRLSX, wxEmptyString, wxPoint(112,132), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLSX"));
	TextCtrlRz = new wxTextCtrl(Panel2, ID_TEXTCTRLRZ, wxEmptyString, wxPoint(112,288), wxSize(144,14), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_TEXTCTRLRZ"));
	Panel1 = new wxPanel(Panel2, ID_PANEL1, wxPoint(112,56), wxSize(144,64), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BitmapButtonPosCircular = new wxBitmapButton(Panel1, ID_BITMAPBUTTONPOSCIRCULAR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motioncircular.png"))), wxPoint(0,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPOSCIRCULAR"));
	BitmapButtonPosCircular->SetDefault();
	BitmapButtonPosHor = new wxBitmapButton(Panel1, ID_BITMAPBUTTONPOSHOR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionhorizontal.png"))), wxPoint(32,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPOSHOR"));
	BitmapButtonPosHor->SetDefault();
	BitmapButtonPosVer = new wxBitmapButton(Panel1, ID_BITMAPBUTTONPOSVERT, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionvertical.png"))), wxPoint(64,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPOSVERT"));
	BitmapButtonPosVer->SetDefault();
	BitmapButton8 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON8, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motiondiagonal.png"))), wxPoint(96,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
	BitmapButton8->SetDefault();
	BitmapButtonPosRand = new wxBitmapButton(Panel1, ID_BITMAPBUTTONPOSRAND, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionrandom.png"))), wxPoint(0,32), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONPOSRAND"));
	BitmapButtonPosRand->SetDefault();
	Panel3 = new wxPanel(Panel2, ID_PANEL2, wxPoint(112,304), wxSize(144,64), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BitmapButtonRotCircular = new wxBitmapButton(Panel3, ID_BITMAPBUTTONROTCIRCULAR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motioncircular.png"))), wxPoint(0,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONROTCIRCULAR"));
	BitmapButtonRotCircular->SetDefault();
	BitmapButtonRotHor = new wxBitmapButton(Panel3, ID_BITMAPBUTTONROTHOR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionhorizontal.png"))), wxPoint(32,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONROTHOR"));
	BitmapButtonRotHor->SetDefault();
	BitmapButtonRotVer = new wxBitmapButton(Panel3, ID_BITMAPBUTTONROTVER, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionvertical.png"))), wxPoint(64,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONROTVER"));
	BitmapButtonRotVer->SetDefault();
	BitmapButtonRotDiag = new wxBitmapButton(Panel3, ID_BITMAPBUTTONROTDIAG, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motiondiagonal.png"))), wxPoint(96,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONROTDIAG"));
	BitmapButtonRotDiag->SetDefault();
	BitmapButtonRotRand = new wxBitmapButton(Panel3, ID_BITMAPBUTTONROTRAND, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionrandom.png"))), wxPoint(0,32), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONROTRAND"));
	BitmapButtonRotRand->SetDefault();
	Panel7 = new wxPanel(Panel2, ID_PANEL10, wxPoint(112,180), wxSize(144,64), wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	BitmapButtonScaCircular = new wxBitmapButton(Panel7, ID_BITMAPBUTTONSCACIRCULAR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motioncircular.png"))), wxPoint(0,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCACIRCULAR"));
	BitmapButtonScaCircular->SetDefault();
	BitmapButtonScaHor = new wxBitmapButton(Panel7, ID_BITMAPBUTTONSCAHOR, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionhorizontal.png"))), wxPoint(32,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCAHOR"));
	BitmapButtonScaHor->SetDefault();
	BitmapButtonScaVer = new wxBitmapButton(Panel7, ID_BITMAPBUTTONSCAVER, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionvertical.png"))), wxPoint(64,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCAVER"));
	BitmapButtonScaVer->SetDefault();
	BitmapButtonScaDiag = new wxBitmapButton(Panel7, ID_BITMAPBUTTONSCADIAG, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motiondiagonal.png"))), wxPoint(96,0), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCADIAG"));
	BitmapButtonScaDiag->SetDefault();
	BitmapButtonScaRand = new wxBitmapButton(Panel7, ID_BITMAPBUTTONSCARAND, wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/motionrandom.png"))), wxPoint(0,32), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSCARAND"));
	BitmapButtonScaRand->SetDefault();
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_SLIDERTX,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderTxCmdScrollThumbTrack);
	Connect(ID_SLIDERTX,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderTxCmdScrollThumbTrack);
	Connect(ID_SLIDERTZ,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderTzCmdScrollThumbTrack);
	Connect(ID_SLIDERTZ,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderTzCmdScrollThumbTrack);
	Connect(ID_SLIDERTY,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderTyCmdScrollThumbTrack);
	Connect(ID_SLIDERTY,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderTyCmdScrollThumbTrack);
	Connect(ID_TEXTCTRLTX,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlTxText);
	Connect(ID_TEXTCTRLTY,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlTyText);
	Connect(ID_SLIDERRZ,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderRzCmdScrollThumbTrack);
	Connect(ID_SLIDERRZ,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderRzCmdScrollThumbTrack);
	Connect(ID_SLIDERSZ,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderSzCmdScrollThumbTrack);
	Connect(ID_SLIDERSZ,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderSzCmdScrollThumbTrack);
	Connect(ID_SLIDERSY,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderSyCmdScrollThumbTrack);
	Connect(ID_SLIDERSY,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderSyCmdScrollThumbTrack);
	Connect(ID_TEXTCTRLRX,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlRxText);
	Connect(ID_SLIDERRX,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderRxCmdScrollThumbTrack);
	Connect(ID_SLIDERRX,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderRxCmdScrollThumbTrack);
	Connect(ID_SLIDERRY,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderRyCmdScrollThumbTrack);
	Connect(ID_SLIDERRY,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderRyCmdScrollThumbTrack);
	Connect(ID_TEXTCTRLRY,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlRyText);
	Connect(ID_SLIDERSX,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&moObjectMotion::OnSliderSxCmdScrollThumbTrack);
	Connect(ID_SLIDERSX,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&moObjectMotion::OnSliderSxCmdScrollThumbTrack);
	Connect(ID_TEXTCTRLTZ,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlTzText);
	Connect(ID_TEXTCTRLSZ,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlSzText);
	Connect(ID_TEXTCTRLSY,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlSyText);
	Connect(ID_TEXTCTRLSX,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlSxText);
	Connect(ID_TEXTCTRLRZ,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moObjectMotion::OnTextCtrlRzText);
	Connect(ID_BITMAPBUTTONPOSCIRCULAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnButton1Click);
	Connect(ID_BITMAPBUTTONPOSHOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton3Click);
	Connect(ID_BITMAPBUTTONPOSVERT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton4Click);
	Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTONPOSRAND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButtonMotionCircularClick);
	Connect(ID_BITMAPBUTTONROTCIRCULAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButtonRotCircularClick);
	Connect(ID_BITMAPBUTTONROTHOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton3Click);
	Connect(ID_BITMAPBUTTONROTVER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton4Click);
	Connect(ID_BITMAPBUTTONROTDIAG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTONROTRAND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButtonMotionCircularClick);
	Connect(ID_BITMAPBUTTONSCACIRCULAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButtonScaCircularClick);
	Connect(ID_BITMAPBUTTONSCAHOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton3Click);
	Connect(ID_BITMAPBUTTONSCAVER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton4Click);
	Connect(ID_BITMAPBUTTONSCADIAG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTONSCARAND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moObjectMotion::OnBitmapButtonMotionCircularClick);
	//*)

}

moObjectMotion::~moObjectMotion()
{
	//(*Destroy(moObjectMotion)
	//*)
}

void moObjectMotion::Inspect( moValueDescriptor  p_ValueDescriptor) {

    m_MobDescriptor  = p_ValueDescriptor.GetParamDescriptor().GetMobDescriptor();

    moParameterDescriptors mParameterDescriptors = GetParameterDescriptors( m_MobDescriptor );

    //itera para conseguir los otros parámetros...
    for( int i = 0; i < (int)mParameterDescriptors.Count(); i++) {

        moParameterDescriptor pParamDescriptor = mParameterDescriptors[i];

        moValueIndex ValueIndex;
        ValueIndex.m_ParamIndex = pParamDescriptor.GetIndex();
        ValueIndex.m_ValueIndex = pParamDescriptor.GetIndexValue();

        moValueDescriptor mValueDesc( pParamDescriptor,ValueIndex);

        switch( (int)pParamDescriptor.GetParamDefinition().GetType() ) {

            case MO_PARAM_TRANSLATEX:
                m_ValueDescriptorTx = GetValue( mValueDesc );
                TextCtrlTx->ChangeValue( moText2Wx( m_ValueDescriptorTx.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_TRANSLATEY:
                m_ValueDescriptorTy = GetValue( mValueDesc );
                TextCtrlTy->ChangeValue( moText2Wx( m_ValueDescriptorTy.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_TRANSLATEZ:
                m_ValueDescriptorTz = GetValue( mValueDesc );
                TextCtrlTz->ChangeValue( moText2Wx( m_ValueDescriptorTz.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_SCALEX:
                m_ValueDescriptorSx = GetValue( mValueDesc );
                TextCtrlSx->ChangeValue( moText2Wx( m_ValueDescriptorSx.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_SCALEY:
                m_ValueDescriptorSy = GetValue( mValueDesc );
                TextCtrlSy->ChangeValue( moText2Wx( m_ValueDescriptorSy.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_SCALEZ:
                m_ValueDescriptorSz = GetValue( mValueDesc );
                TextCtrlSz->ChangeValue( moText2Wx( m_ValueDescriptorSz.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_ROTATEX:
                m_ValueDescriptorRx = GetValue( mValueDesc );
                TextCtrlRx->ChangeValue( moText2Wx( m_ValueDescriptorRx.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_ROTATEY:
                m_ValueDescriptorRy = GetValue( mValueDesc );
                TextCtrlRy->ChangeValue( moText2Wx( m_ValueDescriptorRy.GetValue().GetSubValue(0).Text() ) );
                break;

            case MO_PARAM_ROTATEZ:
                m_ValueDescriptorRz = GetValue( mValueDesc );
                TextCtrlRz->ChangeValue( moText2Wx( m_ValueDescriptorRz.GetValue().GetSubValue(0).Text() ) );
                break;

        }

    }

}


void moObjectMotion::OnTextCtrlTxText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorTx.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlTx->GetValue() ) );

    SetValue( m_ValueDescriptorTx );
}

void moObjectMotion::OnTextCtrlTyText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorTy.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlTy->GetValue() ) );

    SetValue( m_ValueDescriptorTy );
}

void moObjectMotion::OnTextCtrlTzText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorTz.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlTz->GetValue() ) );

    SetValue( m_ValueDescriptorTz );
}


void moObjectMotion::OnTextCtrlSxText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorSx.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlSx->GetValue() ) );

    SetValue( m_ValueDescriptorSx );
}

void moObjectMotion::OnTextCtrlSyText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorSy.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlSy->GetValue() ) );

    SetValue( m_ValueDescriptorSy );
}

void moObjectMotion::OnTextCtrlSzText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorSz.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlSz->GetValue() ) );

    SetValue( m_ValueDescriptorSz );
}

void moObjectMotion::OnTextCtrlRxText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorRx.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlRx->GetValue() ) );

    SetValue( m_ValueDescriptorRx );
}

void moObjectMotion::OnTextCtrlRyText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorRy.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlRy->GetValue() ) );

    SetValue( m_ValueDescriptorRy );
}

void moObjectMotion::OnTextCtrlRzText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptorRz.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlRz->GetValue() ) );

    SetValue( m_ValueDescriptorRz );
}

void moObjectMotion::OnSliderTxCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlTx->SetValue( moText2Wx( FloatToStr( (float)SliderTx->GetValue() / 1000.0 ) ) );
}

void moObjectMotion::OnSliderTyCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlTy->SetValue( moText2Wx( FloatToStr( (float)SliderTy->GetValue() / 1000.0 ) ) );
}

void moObjectMotion::OnSliderTzCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlTz->SetValue( moText2Wx( FloatToStr( (float)SliderTz->GetValue() / 1000.0 ) ) );
}

void moObjectMotion::OnSliderSxCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlSx->SetValue( moText2Wx( FloatToStr( (float)SliderSx->GetValue()/ 10.0 ) ) );
}

void moObjectMotion::OnSliderSyCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlSy->SetValue( moText2Wx( FloatToStr( (float)SliderSy->GetValue() / 10.0 ) ) );
}

void moObjectMotion::OnSliderSzCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlSz->SetValue( moText2Wx( FloatToStr( (float)SliderSz->GetValue() / 10.0 ) ) );
}

void moObjectMotion::OnSliderRxCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlRx->SetValue( moText2Wx( FloatToStr( (float)SliderRx->GetValue() ) ) );
}

void moObjectMotion::OnSliderRyCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlRy->SetValue( moText2Wx( FloatToStr( (float)SliderRy->GetValue() ) ) );
}

void moObjectMotion::OnSliderRzCmdScrollThumbTrack(wxScrollEvent& event)
{
    TextCtrlRz->SetValue( moText2Wx( FloatToStr( (float)SliderRz->GetValue() ) ) );
}

void moObjectMotion::OnButton1Click(wxCommandEvent& event)
{
    TextCtrlTx->SetValue( TextCtrlTx->GetValue() + _("+0.2*cos(t)") );
    TextCtrlTy->SetValue( TextCtrlTy->GetValue() +_("+0.2*sin(t)") );
}

void moObjectMotion::OnBitmapButton3Click(wxCommandEvent& event)
{
    TextCtrlTx->SetValue( TextCtrlTx->GetValue() + _("+0.2*cos(t)") );
    TextCtrlTy->SetValue( _("0.0") );
}

void moObjectMotion::OnBitmapButton4Click(wxCommandEvent& event)
{
    TextCtrlTx->SetValue( _("0.0") );
    TextCtrlTy->SetValue( TextCtrlTy->GetValue() +_("+0.2*sin(t)") );
}

void moObjectMotion::OnBitmapButton2Click(wxCommandEvent& event)
{
    TextCtrlTx->SetValue( TextCtrlTx->GetValue() + _("+0.2*cos(t)") );
    TextCtrlTy->SetValue( TextCtrlTy->GetValue() +_("+0.2*cos(t)") );
}

void moObjectMotion::OnBitmapButtonMotionCircularClick(wxCommandEvent& event)
{
}




void moObjectMotion::OnBitmapButtonScaCircularClick(wxCommandEvent& event)
{
    TextCtrlSx->SetValue( TextCtrlSx->GetValue() + _("*(0.5+0.25*cos(t))") );
    TextCtrlSy->SetValue( TextCtrlSy->GetValue() +_("*(0.5+0.25*sin(t))") );
}

void moObjectMotion::OnBitmapButtonRotCircularClick(wxCommandEvent& event)
{
    TextCtrlRx->SetValue( TextCtrlRx->GetValue() + _("*(0.5+0.25*cos(t))") );
    TextCtrlRy->SetValue( TextCtrlRy->GetValue() +_("*(0.5+0.25*sin(t))") );
    TextCtrlRz->SetValue( TextCtrlRz->GetValue() +_("*(0.5+0.25*tan(t))") );
}

