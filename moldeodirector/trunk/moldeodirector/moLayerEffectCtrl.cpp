#include "moLayerEffectCtrl.h"

//(*InternalHeaders(moLayerEffectCtrl)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include <wx/dcbuffer.h>

//(*IdInit(moLayerEffectCtrl)
const long moLayerEffectCtrl::ID_TEXTCTRL_LABEL = wxNewId();
const long moLayerEffectCtrl::ID_TEXTCTRL_TIMECODE = wxNewId();
const long moLayerEffectCtrl::ID_SLIDERHUE = wxNewId();
const long moLayerEffectCtrl::ID_SLIDERSATURATION = wxNewId();
const long moLayerEffectCtrl::ID_SLIDERALPHA = wxNewId();
const long moLayerEffectCtrl::ID_SLIDERTINT = wxNewId();
const long moLayerEffectCtrl::ID_SLIDERTEMPO = wxNewId();
const long moLayerEffectCtrl::ID_CHECKBOXONOFF = wxNewId();
const long moLayerEffectCtrl::ID_BITMAPBUTTONVIEW = wxNewId();
const long moLayerEffectCtrl::ID_COLOURPANELFINAL = wxNewId();
const long moLayerEffectCtrl::ID_COLOURPANEL = wxNewId();
const long moLayerEffectCtrl::ID_BITMAPBUTTON_FXPLAY = wxNewId();
const long moLayerEffectCtrl::ID_BITMAPBUTTON_FXSTOP = wxNewId();
const long moLayerEffectCtrl::ID_BITMAPBUTTON_FXPAUSE = wxNewId();
//*)

const long moLayerEffectCtrl::ID_LEVELALPHA = wxNewId();
const long moLayerEffectCtrl::ID_LEVELTINT = wxNewId();
const long moLayerEffectCtrl::ID_LEVELSPEED = wxNewId();

BEGIN_EVENT_TABLE(moLayerEffectCtrl,wxPanel)
	//(*EventTable(moLayerEffectCtrl)
	//*)
	EVT_MOUSE_EVENTS( moLayerEffectCtrl::OnMouseEvent )
END_EVENT_TABLE()

moLayerEffectCtrl::moLayerEffectCtrl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moLayerEffectCtrl)
	Create(parent, wxID_ANY, wxPoint(0,0), wxSize(388,44), 0, _T("wxID_ANY"));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	SetForegroundColour(wxColour(255,255,255));
	TextCtrlLabel = new wxTextCtrl(this, ID_TEXTCTRL_LABEL, _("Text"), wxPoint(0,32), wxSize(144,12), wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_TEXTCTRL_LABEL"));
	TextCtrlLabel->Hide();
	TextCtrlLabel->SetForegroundColour(wxColour(255,255,255));
	TextCtrlLabel->SetBackgroundColour(wxColour(0,0,0));
	wxFont TextCtrlLabelFont(6,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Terminal"),wxFONTENCODING_DEFAULT);
	TextCtrlLabel->SetFont(TextCtrlLabelFont);
	TextCtrlLabel->SetEditable( false );
	TextCtrlTimecode = new wxTextCtrl(this, ID_TEXTCTRL_TIMECODE, _("Timecode"), wxPoint(312,24), wxSize(72,20), wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_TEXTCTRL_TIMECODE"));
	TextCtrlTimecode->Hide();
	TextCtrlTimecode->SetForegroundColour(wxColour(255,255,255));
	TextCtrlTimecode->SetBackgroundColour(wxColour(0,0,0));
	wxFont TextCtrlTimecodeFont(6,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Terminal"),wxFONTENCODING_DEFAULT);
	TextCtrlTimecode->SetFont(TextCtrlTimecodeFont);
	TextCtrlLabel->SetEditable( false );
	SliderHue = new wxMoColourLevelCtrl(this, ID_SLIDERHUE, 0, 0, 100, wxPoint(176,4), wxSize(88,8), 0, wxDefaultValidator, _T("ID_SLIDERHUE"));
	Connect(ID_SLIDERHUE, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moLayerEffectCtrl::OnLevelHue );
	SliderHue->Init( wxMoColorLevelCtrl::HUE );
	SliderSaturation = new wxMoColourLevelCtrl(this, ID_SLIDERSATURATION, 0, 0, 100, wxPoint(176,16), wxSize(88,8), 0, wxDefaultValidator, _T("ID_SLIDERSATURATION"));
	Connect(ID_SLIDERSATURATION, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moLayerEffectCtrl::OnLevelSaturation );
	SliderSaturation->Init( wxMoColorLevelCtrl::SATURATION );
	m_pLevelAlphaCtrl = new wxMoColourLevelCtrl(this, ID_SLIDERALPHA, 0, 0, 100, wxPoint(80,4), wxSize(88,8), 0, wxDefaultValidator, _T("ID_SLIDERALPHA"));
	Connect(ID_SLIDERALPHA, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moLayerEffectCtrl::OnLevelAlpha );
	m_pLevelAlphaCtrl->Init( wxMoColorLevelCtrl::ALPHA );
	m_pLevelTintCtrl = new wxMoColourLevelCtrl(this, ID_SLIDERTINT, 0, 0, 100, wxPoint(80,16), wxSize(88,8), 0, wxDefaultValidator, _T("ID_SLIDERTINT"));
	Connect(ID_SLIDERTINT, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moLayerEffectCtrl::OnLevelTint );
	m_pLevelTintCtrl->Init( wxMoColorLevelCtrl::VALUE );
	m_pLevelSpeedCtrl = new wxMoRotaryCtrl(this, ID_SLIDERTEMPO, 0, 0, 100, wxPoint(280,0), wxSize(24,24), 0, wxDefaultValidator, _T("ID_SLIDERTEMPO"));
	m_pLevelSpeedCtrl->SetBackgroundColour(wxColour(0,0,0));
	Connect(ID_SLIDERTEMPO,wxEVT_MOROTARYCTRL, (wxObjectEventFunction)&moLayerEffectCtrl::OnLevelSpeed );
	CheckBoxOnOff = new wxCheckBox(this, ID_CHECKBOXONOFF, wxEmptyString, wxPoint(280,24), wxSize(16,21), 0, wxDefaultValidator, _T("ID_CHECKBOXONOFF"));
	CheckBoxOnOff->SetValue(false);
	CheckBoxOnOff->Hide();
	BitmapButtonView = new wxBitmapButton(this, ID_BITMAPBUTTONVIEW, wxBitmap(wxImage(_T("../../data/icons/view_16.png"))), wxPoint(0,2), wxSize(24,24), wxNO_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTONVIEW"));
	BitmapButtonView->SetBackgroundColour(wxColour(0,0,0));
	BitmapButtonView->SetToolTip(_("on/off"));
	ColourPanelFinal = new wxMoColourPanel(this, ID_COLOURPANELFINAL, wxPoint(28,2), wxSize(24,24), wxTAB_TRAVERSAL, _T("ID_COLOURPANELFINAL"));
	ColourPanel = new wxMoColourPanel(this, ID_COLOURPANEL, wxPoint(56,2), wxSize(24,24), wxTAB_TRAVERSAL, _T("ID_COLOURPANEL"));
	BitmapButtonPlay = new wxBitmapButton(this, ID_BITMAPBUTTON_FXPLAY, wxBitmap(wxImage(_T("../../data/icons/play32.png"))), wxPoint(312,0), wxSize(24,24), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FXPLAY"));
	BitmapButtonPlay->SetToolTip(_("Play"));
	BitmapButtonStop = new wxBitmapButton(this, ID_BITMAPBUTTON_FXSTOP, wxBitmap(wxImage(_T("../../data/icons/stop32.png"))), wxPoint(360,0), wxSize(24,24), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FXSTOP"));
	BitmapButtonStop->SetToolTip(_("Stop"));
	BitmapButtonPause = new wxBitmapButton(this, ID_BITMAPBUTTON_FXPAUSE, wxBitmap(wxImage(_T("../../data/icons/pause32.png"))), wxPoint(336,0), wxSize(24,24), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FXPAUSE"));
	BitmapButtonPause->SetToolTip(_("Pause"));

	Connect(ID_CHECKBOXONOFF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&moLayerEffectCtrl::OnCheckBoxOnOffClick);
	Connect(ID_BITMAPBUTTONVIEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moLayerEffectCtrl::OnBitmapButtonVisibilityClick);
	Connect(ID_BITMAPBUTTON_FXPLAY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moLayerEffectCtrl::OnBitmapButtonPlay);
	Connect(ID_BITMAPBUTTON_FXPAUSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moLayerEffectCtrl::OnBitmapButtonPauseClick);
	Connect(ID_BITMAPBUTTON_FXSTOP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moLayerEffectCtrl::OnBitmapButtonStopClick);
	//*)

	m_pLevelAlphaCtrl->SetHSVColorComponents( SliderHue, SliderSaturation, m_pLevelTintCtrl );
	m_pLevelTintCtrl->SetRGBAColorComponents( NULL, NULL, NULL, m_pLevelAlphaCtrl );

  SliderHue->SetHSVColorComponents( NULL, SliderSaturation, m_pLevelTintCtrl );
  SliderHue->SetRGBAColorComponents( NULL, NULL, NULL, m_pLevelAlphaCtrl );

  SliderSaturation->SetHSVColorComponents( SliderHue, NULL, m_pLevelTintCtrl );
  SliderSaturation->SetRGBAColorComponents( NULL, NULL, NULL, m_pLevelAlphaCtrl );

	m_pLevelAlphaCtrl->SetColourPanel( ColourPanel );
	m_pLevelTintCtrl->SetColourPanel( ColourPanel );
	SliderHue->SetColourPanel( ColourPanel );
	SliderSaturation->SetColourPanel( ColourPanel );

  m_BitmapViewOn = wxBitmap( wxImage( _T(MOLDEODATADIR "/icons/view_16.png") ) );
  m_BitmapViewOff = wxBitmap( wxImage( _T(MOLDEODATADIR "/icons/view_16_off.png") ) );

}

moLayerEffectCtrl::~moLayerEffectCtrl()
{
	//(*Destroy(moLayerEffectCtrl)
	//*)
}

///ACTIVE!!!! propaga los cambios al CORE
void moLayerEffectCtrl::Update( const moEffectState& effect_state ) {

    moMobDescriptor p_MobDescriptor = m_MobDescriptor;

    ///GENERAMOS UNA COPIA...
    ///wxMessageBox( "test" );

    moMobDefinition &MobDefinition( p_MobDescriptor.GetMobDefinition() );
    moEffectState &EffectState( p_MobDescriptor.GetState().GetEffectState() );

    EffectState = effect_state;
    EffectState.CSV2RGB();
/*
    ShowMessage( "moLayerEffectCtrl::Update sync: " + IntToStr((int)effect_state.synchronized)
                +" tempo.on: " + IntToStr( (int)effect_state.tempo.Started() )
                +" tempo.pause_on: " + IntToStr( (int)effect_state.tempo.Paused())
                + " tempo.ticks: " + IntToStr( effect_state.tempo.ticks )
                + " tempo.ang: " + FloatToStr( effect_state.tempo.ang )
    );
*/
    ///enviamos el valor al CORE
    SetMob( p_MobDescriptor );

}


/// La funcion Inspect siempre debe ser pasiva. O sea no reflejar cambios al CORE
void moLayerEffectCtrl::Inspect( moMobDescriptor p_MobDesc ) {

    ///actualizamos el objeto con su estado en los controles de esta ventana
    MobUpdated( p_MobDesc );

    ///buscamos si tiene algun parametros texturizador???

    /*

    moParameterDescriptors ParamsDesc = GetParameterDescriptors( m_MobDescriptor );

    moValueIndex vindex;

    for( int i=0; i<ParamsDesc.Count(); i++) {

        moParameterDescriptor ParamDes = ParamsDesc[i];

        switch( ParamDes.GetParamDefinition().GetType() ) {

          case MO_PARAM_COLOR:
          case MO_PARAM_TEXTURE:

            vindex.m_ParamIndex = ParamDes.GetIndex();
            vindex.m_ValueIndex = ParamDes.GetIndexValue();

            moValueDescriptor ValueDes( ParamDes, vindex );

            ///PEDIMOS EL VALOR.... completo
            ValueDes = GetValue( ValueDes );

            ///auto actualizamos
            ValueUpdated( ValueDes );

            break;

        }

    }
*/

}


void moLayerEffectCtrl::OnCheckBoxOnOffClick(wxCommandEvent& event)
{
    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.on*= -1;

    ///tratamos de actualizar el valor
    Update( EffectState );
}


void moLayerEffectCtrl::OnLevelAlpha(wxCommandEvent& event) {

    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.alpha = (float) event.GetInt() / (float)255.0;

    ///tratamos de actualizar el valor
    Update( EffectState );
}


void moLayerEffectCtrl::OnLevelTint(wxCommandEvent& event) {

    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.tint = (float) event.GetInt() / (float)255.0;

    ///tratamos de actualizar el valor
    Update( EffectState );

}

void moLayerEffectCtrl::OnLevelHue(wxCommandEvent& event) {

    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.tintc = (float) event.GetInt() / (float)360.0;

    ///tratamos de actualizar el valor
    Update( EffectState );
}

void moLayerEffectCtrl::OnLevelSaturation(wxCommandEvent& event) {

    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.tints = (float) event.GetInt() / (float)255.0;

    ///tratamos de actualizar el valor
    Update( EffectState );
}


void moLayerEffectCtrl::OnLevelSpeed(wxCommandEvent& event) {

    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    EffectState.synchronized = MO_DEACTIVATED;
    EffectState.tempo.delta = (float) event.GetInt() / 50.0;

    ///tratamos de actualizar el valor
    Update( EffectState );

}

void moLayerEffectCtrl::OnComboBoxPreConfigSelect(wxCommandEvent& event)
{
}


void moLayerEffectCtrl::OnPanelVisibilityMouseMove(wxMouseEvent& event)
{
    wxMessageBox(wxT("hi there"));
    SetCursor( wxCursor(wxCURSOR_HAND ));
}

void moLayerEffectCtrl::OnBitmapButtonVisibilityClick(wxCommandEvent& event)
{
    ///copiamos el estado...
    moEffectState EffectState = m_MobDescriptor.GetState().GetEffectState();

    ///lo modificamos
    //EffectState.synchronized = MO_DEACTIVATED;
    EffectState.on*= -1;

    //ShowMessage( moText("visibility checked") );

    ///tratamos de actualizar el valor
    Update( EffectState );
}

void moLayerEffectCtrl::OnMouseEvent( wxMouseEvent& event ) {

    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        ///GetParent()->ProcessEvent(event);

        ///OpenMob( m_MobDescriptor );
    }
    event.Skip();

}


moDirectorStatus
moLayerEffectCtrl::SetMob( moMobDescriptor p_MobDesc ) {
  moMobIndex test = p_MobDesc.GetMobDefinition().GetMobIndex();
  if (m_pNextActionHandler)
    return m_pNextActionHandler->SetMob( p_MobDesc );
  else
    return MO_DIRECTOR_STATUS_NO_HANDLER;

}

moDirectorStatus
moLayerEffectCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {

    float r,g,b,a;
    float ang = 0;///EffectState.tempo.ang

    moText tname;
    moTextureDescriptor pTextureDescriptor;

    ///actualizamos el valor correspondiente al color y a la textura

    ///ATENCION ESTO NO FUNCIONA SI HAY MAS DE UN COLOR O TEXTURA!!!!
    ///que textura o que color son los supervisados por este control se debería definir
    ///en algun lado ( acive=1 o principal=1 o algo por el estilo... o simplemente que sea el primero... )
    ///bueno, y que definitivamente se llame COLOR y el otro se llame TEXTURE...???

    switch( p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetType() ) {

      case MO_PARAM_COLOR:

          if ( p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetName()==moText("color") ) {

              r = 255.0 * p_ValueDesc.GetValue().GetSubValue(MO_RED).Eval( ang );
              g = 255.0 * p_ValueDesc.GetValue().GetSubValue(MO_GREEN).Eval( ang );
              b = 255.0 * p_ValueDesc.GetValue().GetSubValue(MO_BLUE).Eval( ang );
              a = 255.0 * p_ValueDesc.GetValue().GetSubValue(MO_ALPHA).Eval( ang );

              if (ColourPanelFinal)
                ColourPanelFinal->SetColourValue( wxColour( r,g, b, a ) );
          }

          break;

      case MO_PARAM_TEXTURE:

          if ( p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetName()==moText("texture") ) {

            tname = p_ValueDesc.GetValue().GetSubValue(0).Text();

            pTextureDescriptor = GetResourceDescriptor( moTextureDescriptor( tname ) );

            ///en caso de no tener aun textura asignada, o en caso de ser distinta... aplicamos...
            if ( !m_TextureDescriptor.IsValid() ||
                  (moText)m_TextureDescriptor.GetResourceDefinition().GetName() != (moText)pTextureDescriptor.GetResourceDefinition().GetName()
            ) {

                ///guardamos el descriptor de esta textura... para proximas referencias...
                ///para no volver a pisar...
                m_TextureDescriptor = pTextureDescriptor;
                m_TexValueDescriptor = p_ValueDesc;

                void* ptr = p_ValueDesc.GetValue().GetSubValue(0).Pointer();

                moTexture *pTex = reinterpret_cast<moTexture*>( ptr );

                if  (pTex ) {

                  //Log( pTex->GetName() );

                  MOuchar *bits;

                  bits = new MOuchar[ pTex->GetWidth() * pTex->GetHeight() * 4 ];
                  pTex->GetBuffer( bits );

                  wxImage* thumbImg =  new wxImage( pTex->GetWidth(), pTex->GetHeight(), false );
                  if (thumbImg) {
                    thumbImg->InitAlpha();

                    for(int j=0; j< thumbImg->GetHeight(); j++) {
                      for(int i=0; i< thumbImg->GetWidth(); i++) {
                          thumbImg->SetRGB( i, j,
                                            bits[ (i + j*thumbImg->GetWidth() )*4 ],
                                            bits[ (i + j*thumbImg->GetWidth() )*4 + 1 ],
                                            bits[ (i + j*thumbImg->GetWidth() )*4 + 2 ] );
                          thumbImg->SetAlpha( i, j, bits[ (i + j*thumbImg->GetWidth() )*4 + 3 ] );

                      }
                    }


                    if (thumbImg->IsOk()) {
                      ColourPanelFinal->SetBitmap( wxBitmap(*thumbImg) );

                    }

                    if (thumbImg)
                      delete thumbImg;

                    ///el primero que encontramos que pudimos aplicar es suficiente.....
                    break;
                  }
                  if (bits)
                     delete [] bits;
                }


              }
          }
          break;

      default:
          ///nothing to do
          break;

    }

    return MO_DIRECTOR_STATUS_OK;

}


moDirectorStatus
moLayerEffectCtrl::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {

    moValueIndex vindex;

    ///solo actualizamos aquellos parametros que tienen textura y color...
    ///el nombre del parametro debe ser "color" o "texture"

    switch( p_ParameterDesc.GetParamDefinition().GetType() ) {

      case MO_PARAM_COLOR:
      case MO_PARAM_TEXTURE:

        if (  p_ParameterDesc.GetParamDefinition().GetName()==moText("color") ||
              p_ParameterDesc.GetParamDefinition().GetName()==moText("texture")
        ) {

          vindex.m_ParamIndex = p_ParameterDesc.GetIndex();
          vindex.m_ValueIndex = p_ParameterDesc.GetIndexValue();

          moValueDescriptor ValueDes( p_ParameterDesc, vindex );

          ///PEDIMOS EL VALOR.... completo
          ValueDes = GetValue( ValueDes );

          ///auto actualizamos
          ValueUpdated( ValueDes );
        }

        break;

    }

    return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus
moLayerEffectCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {

    ///asignamos los nuevos datos
    m_MobDescriptor = p_MobDesc;

    ///actualizamos los controles de esta ventana
    moMobDefinition &MobDefinition( m_MobDescriptor.GetMobDefinition() );
    moEffectState &EffectState( m_MobDescriptor.GetState().GetEffectState() );

    if (TextCtrlLabel)
      TextCtrlLabel->SetLabel( moText2Wx( MobDefinition.GetLabelName() ) );

    if (BitmapButtonView)
    switch( EffectState.on ) {
              case MO_OFF:
                  ///CheckBoxOnOff->SetValue(false);
                  BitmapButtonView->SetBitmapLabel( m_BitmapViewOff );

                  break;
              case MO_ON:
                  ///CheckBoxOnOff->SetValue(true);
                  BitmapButtonView->SetBitmapLabel( m_BitmapViewOn );
                  break;
      }

    float  alphaf = EffectState.alpha * 255.0;
    float tintf  = EffectState.tint * 255.0;
    double deltaf = EffectState.tempo.delta;

    float tintr  = EffectState.tintr * 255.0;
    float tintg  = EffectState.tintg * 255.0;
    float tintb  = EffectState.tintb * 255.0;


    wxColour m_actual_color;

    m_actual_color = wxColour( (int)tintr, (int)tintg, (int)tintb , (int)alphaf );

    if (m_pLevelAlphaCtrl)
      m_pLevelAlphaCtrl->SetColourValue( m_actual_color, true );

    /// deltaf, si es 1, va al medio (velocidad normal) -> 50
    float deltafr = deltaf * 50.0f;
    int deltav = (int) deltafr;

    if (m_pLevelSpeedCtrl)
      m_pLevelSpeedCtrl->ChangeValue( deltav );


    return MO_DIRECTOR_STATUS_OK;

}



void moLayerEffectCtrl::OnBitmapButtonDeleteClick(wxCommandEvent& event)
{
    if( wxMessageBox(_T("Really Delete this layer ?"), _T("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) == wxYES )
    {
        ///DeleteMob( m_MobDescriptor );
	}
}



void moLayerEffectCtrl::OnPaint(wxPaintEvent& event)
{



}


BEGIN_EVENT_TABLE(moEffectLayerTimelineCtrl,wxPanel)
    EVT_PAINT( moEffectLayerTimelineCtrl::OnPaint )
    EVT_MOUSE_EVENTS( moEffectLayerTimelineCtrl::OnMouseEvent )
END_EVENT_TABLE()

moEffectLayerTimelineCtrl::moEffectLayerTimelineCtrl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{

    Create(parent, wxID_ANY, wxPoint(0,0), wxSize(800,40), wxNO_BORDER, _T("wxID_ANY"));
    SetBackgroundColour( wxColour(0,9,117));

    m_BackgroundImage = wxImage( 800, 40, true ); //to black

    m_BackgroundName = moText("");

}

moEffectLayerTimelineCtrl::~moEffectLayerTimelineCtrl()
{

}

void moEffectLayerTimelineCtrl::Inspect( moMobDescriptor p_MobDescriptor ) {

  m_MobDescriptor = p_MobDescriptor;

}


void moEffectLayerTimelineCtrl::OnPaint( wxPaintEvent& event ) {

    wxBufferedPaintDC dc(this);

    int w,h;

    GetSize(&w,&h);

    wxBrush BackBrush( wxColour(70,70,70), wxSOLID );

    //draw background bitmap
    if (m_BackgroundImage.IsOk()) {
        dc.DrawBitmap( wxBitmap( m_BackgroundImage.Rescale(m_BackgroundImage.GetWidth(),h), -1 ), 0, 0, true );
        BackBrush.SetStipple( wxBitmap( m_BackgroundImage, -1 ) );
        BackBrush.SetStyle( wxSTIPPLE );
    }

    dc.SetBrush( BackBrush );
    dc.SetPen( wxPen( wxColour(75,75,75), 1, wxSOLID) );

    //background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );



    //gauge
    //dc.SetBrush( wxBrush( wxColour(220,220,220), wxSOLID) );
    //dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    //dc.DrawRectangle( 0, 0, SlidePosition(), GetSize().y );

    //ticks:
    dc.SetBrush( BackBrush );
    dc.SetPen( wxPen( wxColour(75,75,75), 1, wxSOLID) );

    int linedelta = m_MobDescriptor.GetState().GetEffectState().tempo.delta;

    for(int i =0; i<GetSize().x; i+= ( (GetSize().x / 40 ) * linedelta )) {
        dc.DrawLine( i, 0, i, GetSize().y );
    }

}

void moEffectLayerTimelineCtrl::OnMouseEvent( wxMouseEvent& event ) {

    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        GetParent()->ProcessEvent(event);

        OpenMob( m_MobDescriptor );

    }
    event.Skip();

}

moDirectorStatus
moEffectLayerTimelineCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {

    switch(p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetType() ) {
        case MO_PARAM_TEXTURE:
            //LOAD IMAGE....
            //Log("loading background");
            if ( p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetType()==MO_PARAM_TEXTURE
             && p_ValueDesc.GetValue().GetSubValueCount()>=1 ) {

                moText tname = p_ValueDesc.GetValue().GetSubValue(0).Text();

                if(tname!=m_BackgroundName) {

                    m_BackgroundName = tname;

                    moTextureDescriptor pTextDescriptor( GetResourceDescriptor( moTextureDescriptor( tname ) ) );

                    //m_BackgroundImage.LoadFile( moText2Wx( pTextDescriptor.GetResourceDefinition().GetFileName() ) );

                    Refresh();
                }
            }
            break;
        default:
            break;
    }

    return MO_DIRECTOR_STATUS_OK;

}


moDirectorStatus
moEffectLayerTimelineCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {


    return MO_DIRECTOR_STATUS_OK;

}



/*
BEGIN_EVENT_TABLE( moTreeObjectLayerCtrl, wxPanel)
        EVT_MOUSE_EVENTS( moTreeObjectLayerCtrl::OnMouseEvent )
END_EVENT_TABLE()
*/


moMobDescriptor&
moItemLayerCtrl::Get() {

    return m_MobDescriptor;

}
/*
void moTreeObjectLayerCtrl::OnMouseEvent( wxMouseEvent& event ) {

    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        GetParent()->ProcessEvent(event);
    }
    event.Skip();

}
*/
//=========================================

BEGIN_EVENT_TABLE( moItemLayerWindow, wxPanel )

END_EVENT_TABLE()

#include "wxTreeMultiCtrl.h"

moItemLayerWindow::moItemLayerWindow( wxWindow *parent, wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style,
                const wxString& name ) : wxPanel(parent, id, pos, size, style, name) {

                    ///Controladores y selectores... en un panel con un sizer
                    /*
                    wxFlexGridSizer *topsizer = new wxFlexGridSizer( 1, 2, 0, 0 );
                    topsizer->SetFlexibleDirection(wxBOTH);
                    topsizer->AddGrowableRow(0);
                    topsizer->AddGrowableCol(0);

                    int hh = size.GetHeight();

                    m_pFXControllersContainer = new wxPanel( this, wxID_ANY,  wxPoint(0,0), wxSize(265,hh) );

                    m_pFXSelectors = new wxPanel( m_pFXControllersContainer, wxID_ANY,  wxPoint(0,0), wxSize(45,hh) );
                    m_pFXSelectors->SetBackgroundColour(wxColour(90,90,90) );
*/
                    //m_pFXControllers = new moLayerEffectCtrl( m_pFXControllersContainer, wxID_ANY, wxPoint(0,0), wxSize(220,hh) );

                  /*
                    wxFlexGridSizer *topsizer = new wxFlexGridSizer( 2, 1, 0, 0 );
                    topsizer->SetFlexibleDirection(wxBOTH);
                    topsizer->AddGrowableRow(0);
                    topsizer->AddGrowableRow(1);
                    topsizer->AddGrowableCol(0);*/

                    m_pFXControllers = NULL;
                    m_pFXControllers = new moLayerEffectCtrl( this, wxID_ANY, wxPoint(20,0), size );
                    //topsizer->Add( m_pFXControllers, 1, wxALL | wxEXPAND, 0 );
                    //wxTreeMultiCtrl* tree = dynamic_cast<wxTreeMultiCtrl*>parent;


/*
                    wxTreeMultiCtrl* pMultiCtrls = new wxTreeMultiCtrl( this, wxID_ANY, wxPoint( 20,size.GetHeight()-20 ), size );
                    pMultiCtrls->SetBackgroundColour( wxColour(80,80,0) );

                    ///agregamos algunos parametros

                    ///info para agregar al MultiItemCtrl.... (spacing,indentation, etc...)

                    wxTreeMultiWindowInfo wndinfo( wxTMC_SPAN_WIDTH, 0, 0, false);
                    wndinfo.SetTopSpacing(0);
                    wndinfo.SetFrontSpacing(0);
                    wndinfo.Indent(0);

                    wxTreeMultiItem idparams = pMultiCtrls->AddRoot( wxT("params"), wxT("params"), NULL );

                    for(int i=0; i<10; i++) {
                      wxPanel* t = new wxPanel( pMultiCtrls, wxID_ANY, wxPoint(0,0), wxSize(200,10));
                      if ((i%2)==0) t->SetBackgroundColour( wxColour(190, 120, 0 ) );
                      if ((i%2)==1) t->SetBackgroundColour( wxColour(0, 190,1280) );
                      wxTreeMultiItem idparam = pMultiCtrls->AppendNode( idparams, wxT("param"),
                                                                          wxT("param") );

                      pMultiCtrls->AppendWindow( idparam, t, _(""), wndinfo);

                    }

                    topsizer->Add( pMultiCtrls, 1, wxALL | wxEXPAND, 0 );
                    */

                    //SetSizer( topsizer );
                    //topsizer->Layout();

                    m_pFXControllers->SetNextActionHandler(this);

                    /*

                    topsizer->Add( m_pFXControllers, 1, wxALL, 0 );
                    //topsizer->SetItemMinSize( m_pFXControllers, 45, 45 );

                    topsizer->Add( m_pFXSelectors, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE , 0 );
                    topsizer->SetItemMinSize( m_pFXSelectors, 45, hh );

                    m_pFXControllersContainer->SetSizer( topsizer );      // use the sizer for layout

                    topsizer->Layout();

                    ///El timeline, una ventana que contiene al timeline
                    m_pWindow = new wxWindow( this, wxID_ANY, wxPoint(0,0), wxSize(2000,hh) );
                    m_pTimeline = new moEffectLayerTimelineCtrl( m_pWindow, wxID_ANY, wxPoint(0,0), wxSize(2000,hh));

                    ///subdividimos Controles y Timeline
                    this->SplitVertically( m_pFXControllersContainer, m_pWindow );
                    this->SetSashPosition( 265, true );
                    this->SetSashSize(1);

*/
                    this->SetForegroundColour( wxColour(152,0,0) );
                    this->SetBackgroundColour( wxColour(0,80,0) );
                }


void
moItemLayerWindow::SetScrollPosition( int position ) {

    ///m_pTimeline->SetSize( -position, 0, wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING );

}


void moItemLayerWindow::Inspect( moMobDescriptor p_MobDesc ) {

    m_MobDescriptor = p_MobDesc;

    if (m_pFXControllers) {
        m_pFXControllers->SetNextActionHandler(this);
        m_pFXControllers->Inspect(p_MobDesc);
    }

}

moDirectorStatus
moItemLayerWindow::ValueUpdated( moValueDescriptor p_ValueDesc ) {

    if (m_pFXControllers)
      return m_pFXControllers->ValueUpdated( p_ValueDesc );
    else
      return MO_DIRECTOR_STATUS_ERROR;

}


moDirectorStatus
moItemLayerWindow::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {

    if (m_pFXControllers)
      return m_pFXControllers->ParameterUpdated( p_ParameterDesc );
    else
      return MO_DIRECTOR_STATUS_ERROR;


}



moDirectorStatus
moItemLayerWindow::MobUpdated( moMobDescriptor p_MobDesc ) {

    ///demasiadas herencias!!!!!! esto trae problemas de entendimiento general
    ///o se usa el inspect o se usa el MobUpdated , pienso que mejor solo usamos el MobUpdated!!!

    m_MobDescriptor = p_MobDesc;

    if (m_pFXControllers)
      return m_pFXControllers->MobUpdated( p_MobDesc );
    else
      return MO_DIRECTOR_STATUS_ERROR;

}

moDirectorStatus
moItemLayerWindow::SetMob( moMobDescriptor p_MobDesc ) {

  if (m_pNextActionHandler)
    return m_pNextActionHandler->SetMob( p_MobDesc );
  else
    return MO_DIRECTOR_STATUS_NO_HANDLER;

}

void moLayerEffectCtrl::OnBitmapButtonPlay(wxCommandEvent& event)
{
    moEffectState& EffectState( m_MobDescriptor.GetState().GetEffectState() );

    EffectState.synchronized = MO_DEACTIVATED;
    EffectState.tempo.Start();

    Update( EffectState );

}

void moLayerEffectCtrl::OnBitmapButtonPauseClick(wxCommandEvent& event)
{
    moEffectState& EffectState( m_MobDescriptor.GetState().GetEffectState() );

    EffectState.synchronized = MO_DEACTIVATED;
    EffectState.tempo.Pause();

    Update( EffectState );
}

void moLayerEffectCtrl::OnBitmapButtonStopClick(wxCommandEvent& event)
{
    moEffectState& EffectState( m_MobDescriptor.GetState().GetEffectState() );

    EffectState.synchronized = MO_DEACTIVATED;
    EffectState.tempo.Stop();

    Update( EffectState );
}
