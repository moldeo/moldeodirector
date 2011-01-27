#include "moEffectLayerCtrl.h"

//(*InternalHeaders(moEffectLayerCtrl)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/sizer.h>
//*)

#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>

//(*IdInit(moEffectLayerCtrl)
const long moEffectLayerCtrl::ID_TEXTCTRL1 = wxNewId();
const long moEffectLayerCtrl::ID_SLIDERALPHA = wxNewId();
const long moEffectLayerCtrl::ID_SLIDERTINT = wxNewId();
const long moEffectLayerCtrl::ID_SLIDERTEMPO = wxNewId();
const long moEffectLayerCtrl::ID_CHECKBOXONOFF = wxNewId();
const long moEffectLayerCtrl::ID_BITMAPBUTTONDELETE = wxNewId();
//*)

const long moEffectLayerCtrl::ID_LEVELALPHA = wxNewId();
const long moEffectLayerCtrl::ID_LEVELTINT = wxNewId();
const long moEffectLayerCtrl::ID_LEVELSPEED = wxNewId();

BEGIN_EVENT_TABLE(moEffectLayerCtrl,wxPanel)
	//(*EventTable(moEffectLayerCtrl)
	//*)
	EVT_MOUSE_EVENTS( moEffectLayerCtrl::OnMouseEvent )
END_EVENT_TABLE()

moEffectLayerCtrl::moEffectLayerCtrl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moEffectLayerCtrl)
	Create(parent, wxID_ANY, wxPoint(0,0), wxSize(265,40), 0, _T("wxID_ANY"));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(50,50,50));
	TextCtrlLabel = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(0,7), wxSize(96,7), wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrlLabel->SetForegroundColour(wxColour(255,255,255));
	TextCtrlLabel->SetBackgroundColour(wxColour(0,9,60));
	wxFont TextCtrlLabelFont(6,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Terminal"),wxFONTENCODING_DEFAULT);
	TextCtrlLabel->SetFont(TextCtrlLabelFont);
	TextCtrlLabel->SetEditable( false );
	m_pLevelAlphaCtrl = new wxMoLevelCtrl(this, ID_SLIDERALPHA, 0, 0, 100, wxPoint(0,24), wxSize(56,9), 0, wxDefaultValidator, _T("ID_SLIDERALPHA"));
	Connect(ID_SLIDERALPHA, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelAlpha );
	m_pLevelTintCtrl = new wxMoLevelCtrl(this, ID_SLIDERTINT, 0, 0, 100, wxPoint(65,24), wxSize(56,9), 0, wxDefaultValidator, _T("ID_SLIDERTINT"));
	Connect(ID_SLIDERTINT, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelTint );
	m_pLevelSpeedCtrl = new wxMoLevelCtrl(this, ID_SLIDERTEMPO, 0, 0, 100, wxPoint(128,24), wxSize(56,9), 0, wxDefaultValidator, _T("ID_SLIDERTEMPO"));
	Connect(ID_SLIDERTEMPO, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelSpeed );
	CheckBoxOnOff = new wxCheckBox(this, ID_CHECKBOXONOFF, wxEmptyString, wxPoint(224,6), wxSize(16,21), 0, wxDefaultValidator, _T("ID_CHECKBOXONOFF"));
	CheckBoxOnOff->SetValue(false);
	BitmapButtonDelete = new wxBitmapButton(this, ID_BITMAPBUTTONDELETE, wxBitmap(wxImage(_T("../../doc/icons/delete.png"))), wxPoint(240,12), wxSize(13,13), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONDELETE"));
	BitmapButtonDelete->SetDefault();

	Connect(ID_CHECKBOXONOFF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&moEffectLayerCtrl::OnCheckBoxOnOffClick);
	Connect(ID_BITMAPBUTTONDELETE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moEffectLayerCtrl::OnBitmapButtonDeleteClick);
	//*)

	//m_pLevelAlphaCtrl =  new moWxLevelCtrl(this, ID_LEVELALPHA, SliderAlpha->GetPosition(), SliderAlpha->GetSize(), 0, wxDefaultValidator, _T("ID_LEVELALPHA") );
    //Connect(ID_LEVELALPHA, MO_EVT_DIRECTOR_LEVEL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelAlpha );
	//if (SliderAlpha) SliderAlpha->Destroy();

	//m_pLevelTintCtrl =  new moWxLevelCtrl(this, ID_LEVELTINT, SliderTint->GetPosition(), SliderTint->GetSize(), 0, wxDefaultValidator, _T("ID_LEVELTINT") );
    //Connect(ID_LEVELTINT, MO_EVT_DIRECTOR_LEVEL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelTint );
	//if (SliderTint) SliderTint->Destroy();

	//m_pLevelSpeedCtrl =  new moWxLevelCtrl(this, ID_LEVELSPEED, SliderTempo->GetPosition(), SliderTempo->GetSize(), 0, wxDefaultValidator, _T("ID_LEVELSPEED") );
    //Connect(ID_LEVELSPEED, MO_EVT_DIRECTOR_LEVEL, (wxObjectEventFunction)&moEffectLayerCtrl::OnLevelSpeed );
	//if (SliderTempo) SliderTempo->Destroy();


}

moEffectLayerCtrl::~moEffectLayerCtrl()
{
	//(*Destroy(moEffectLayerCtrl)
	//*)
}

void moEffectLayerCtrl::Set( moMobDescriptor p_MobDesc ) {

    m_MobDescriptor = p_MobDesc;

    /*
    TextCtrlName->SetValue((wxChar*)(char*) m_MobDescriptor.GetMobDefinition().GetName());
    TextCtrlName->SetEditable(false);
*/

    TextCtrlLabel->SetLabel((wxChar*)(char*) m_MobDescriptor.GetMobDefinition().GetLabelName());
    //TextCtrlLabel->SetEditable(false);
    //TextCtrlLabel->SetForegroundColour( wxColour(255,255,255) );
	//TextCtrlLabel->SetBackgroundColour( wxColour(0,0,0) );
/*
    TextCtrlConfigName->SetValue((wxChar*)(char*) m_MobDescriptor.GetMobDefinition().GetConfigName());
    TextCtrlConfigName->SetEditable(false);
*/
    switch( p_MobDesc.GetState().GetEffectState().on ) {
            case MO_OFF:
                CheckBoxOnOff->SetValue(false);
                break;
            case MO_ON:
                CheckBoxOnOff->SetValue(true);
                break;
    }

    /*
    SliderAlpha->SetValue( (int)p_MobDesc.GetState().GetEffectState().alpha*100 );
    SliderTempo->SetValue( (int)p_MobDesc.GetState().GetEffectState().tempo.delta*50 );
    SliderTint->SetValue( (int)p_MobDesc.GetState().GetEffectState().tint*100 );
    */

    m_pLevelAlphaCtrl->ChangeValue( (int)p_MobDesc.GetState().GetEffectState().alpha*100 );
    m_pLevelSpeedCtrl->ChangeValue( (int)p_MobDesc.GetState().GetEffectState().tempo.delta*50 );
    m_pLevelTintCtrl->ChangeValue( (int)p_MobDesc.GetState().GetEffectState().tint*100 );


}


void moEffectLayerCtrl::OnCheckBoxOnOffClick(wxCommandEvent& event)
{
    moMobState MobState = m_MobDescriptor.GetState();

    MobState.GetEffectState().on*= -1;

    m_MobDescriptor.SetState(MobState);

    SetMob( m_MobDescriptor );
}


void moEffectLayerCtrl::OnLevelAlpha(wxCommandEvent& event) {

    moMobState MobState = m_MobDescriptor.GetState();

    MobState.GetEffectState().alpha = (float) event.GetInt() / 100.0;

    m_MobDescriptor.SetState(MobState);

    moItemLayerCtrl* h = (moItemLayerCtrl*)this;
    h->SetMob( m_MobDescriptor );

}


void moEffectLayerCtrl::OnLevelTint(wxCommandEvent& event) {

    moMobState MobState = m_MobDescriptor.GetState();

    MobState.GetEffectState().tint = (float) event.GetInt() / 100.0;

    m_MobDescriptor.SetState(MobState);

    moItemLayerCtrl* h = (moItemLayerCtrl*)this;
    h->SetMob( m_MobDescriptor );

}

void moEffectLayerCtrl::OnLevelSpeed(wxCommandEvent& event) {

    moMobState MobState = m_MobDescriptor.GetState();
    MobState.GetEffectState().synchronized = MO_DEACTIVATED;
    MobState.GetEffectState().tempo.delta = (float) event.GetInt() / 50.0;

    m_MobDescriptor.SetState(MobState);

    moItemLayerCtrl* h = (moItemLayerCtrl*)this;
    h->SetMob( m_MobDescriptor );

}

void moEffectLayerCtrl::OnComboBoxPreConfigSelect(wxCommandEvent& event)
{
}


void moEffectLayerCtrl::OnPanelVisibilityMouseMove(wxMouseEvent& event)
{
    wxMessageBox(wxT("hi there"));
    SetCursor( wxCursor(wxCURSOR_HAND ));
}

void moEffectLayerCtrl::OnBitmapButtonVisibilityClick(wxCommandEvent& event)
{
    moMobState MobState = m_MobDescriptor.GetState();

    MobState.GetEffectState().on*= -1;

    m_MobDescriptor.SetState(MobState);

    SetMob( m_MobDescriptor );
}

void moEffectLayerCtrl::OnMouseEvent( wxMouseEvent& event ) {

    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {

        GetParent()->ProcessEvent(event);

        OpenMob( m_MobDescriptor );
    }
    event.Skip();

}


moDirectorStatus
moEffectLayerCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {


    return MO_DIRECTOR_STATUS_OK;

}


moDirectorStatus
moEffectLayerCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {


    return MO_DIRECTOR_STATUS_OK;

}



void moEffectLayerCtrl::OnBitmapButtonDeleteClick(wxCommandEvent& event)
{
    if( wxMessageBox(_T("Really Delete this layer ?"), _T("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) == wxYES )
    {
        DeleteMob( m_MobDescriptor );
	}
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
void moItemLayerCtrl::Set( moMobDescriptor   p_MobDescriptor ) {

    m_MobDescriptor = p_MobDescriptor;

}

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

BEGIN_EVENT_TABLE( moItemLayerWindow, wxSplitterWindow )

END_EVENT_TABLE()


moItemLayerWindow::moItemLayerWindow( wxWindow *parent, wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style,
                const wxString& name ) : wxSplitterWindow(parent, id, pos, size, style, name) {

                    ///Controladores y selectores... en un panel con un sizer
                    wxFlexGridSizer *topsizer = new wxFlexGridSizer( 1, 2, 0, 0 );
                    topsizer->SetFlexibleDirection(wxBOTH);
                    topsizer->AddGrowableRow(0);
                    topsizer->AddGrowableCol(0);
                    m_pFXControllersContainer = new wxPanel( this, wxID_ANY,  wxPoint(0,0), wxSize(265,45) );

                    m_pFXSelectors = new wxPanel( m_pFXControllersContainer, wxID_ANY,  wxPoint(0,0), wxSize(45,45) );
                    m_pFXSelectors->SetBackgroundColour(wxColour(90,90,90) );
                    m_pFXControllers = new moEffectLayerCtrl( m_pFXControllersContainer, wxID_ANY, wxPoint(0,0), wxSize(220,45) );

                    topsizer->Add( m_pFXControllers, 1, wxALL, 0 );
                    //topsizer->SetItemMinSize( m_pFXControllers, 45, 45 );

                    topsizer->Add( m_pFXSelectors, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE , 0 );
                    topsizer->SetItemMinSize( m_pFXSelectors, 45, 45 );

                    m_pFXControllersContainer->SetSizer( topsizer );      // use the sizer for layout

                    topsizer->Layout();

                    ///El timeline, una ventana que contiene al timeline
                    m_pWindow = new wxWindow( this, wxID_ANY, wxPoint(0,0), wxSize(2000,45) );
                    m_pTimeline = new moEffectLayerTimelineCtrl( m_pWindow, wxID_ANY, wxPoint(0,0), wxSize(2000,45));

                    ///subdividimos Controles y Timeline
                    this->SplitVertically( m_pFXControllersContainer, m_pWindow );
                    this->SetSashPosition( 265, true );
                    this->SetSashSize(1);
                    this->SetForegroundColour( wxColour(152,152,152) );
                    this->SetBackgroundColour( wxColour(52,52,52) );

                }


void
moItemLayerWindow::SetScrollPosition( int position ) {

    m_pTimeline->SetSize( -position, 0, wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING );

}


void moItemLayerWindow::Set( moMobDescriptor p_MobDesc ) {

    m_MobDescriptor = p_MobDesc;

    if (m_pFXControllers) {
        m_pFXControllers->SetNextActionHandler(this);
        m_pFXControllers->Set(p_MobDesc);
    }

}

moDirectorStatus
moItemLayerWindow::ValueUpdated( moValueDescriptor p_ValueDesc ) {


    return m_pFXControllers->ValueUpdated( p_ValueDesc );

}


moDirectorStatus
moItemLayerWindow::MobUpdated( moMobDescriptor p_MobDesc ) {


    return m_pFXControllers->MobUpdated( p_MobDesc );

}




void moEffectLayerCtrl::OnPaint(wxPaintEvent& event)
{
}
