#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoRotaryCtrl.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE( wxMoRotaryCtrl, wxControl )
    EVT_PAINT( wxMoRotaryCtrl::OnPaint )
    EVT_MOUSE_EVENTS( wxMoRotaryCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoRotaryCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoRotaryCtrl::OnCaptureChangedEvent )
    EVT_ERASE_BACKGROUND(wxMoRotaryCtrl::OnEraseBackground)
    EVT_KILL_FOCUS(wxMoRotaryCtrl::OnKillFocus)
END_EVENT_TABLE()

template<> const float wxMoRotaryCtrl::PI = (float)(4.0*atan(1.0));
template<> const float wxMoRotaryCtrl::PI2 = (float)(8.0*atan(1.0));

wxMoRotaryCtrl::wxMoRotaryCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxControl( parent, id,  pos, size, style | wxNO_BORDER, validator, name ) {
    m_min = minvalue;
    m_max = maxvalue;
    m_value = value;
    m_bStartDragging = false;
    SetBackgroundStyle(wxBG_STYLE_CUSTOM );
    SetBackgroundColour(parent->GetBackgroundColour());
    //SetBackgroundStyle(wxBG_STYLE_COLOUR);
    //SetForegroundColour(parent->GetForegroundColour());

    m_angmin = 0;
    m_angmax = 2*wxMoRotaryCtrl::PI; //2pi
    AngleClickPosition = 0.0;
    AngleValueWhenClicked = 0.0;

}

wxMoRotaryCtrl::~wxMoRotaryCtrl() {


}


void wxMoRotaryCtrl::OnEraseBackground(wxEraseEvent& event) {

}

void
wxMoRotaryCtrl::OnKillFocus( wxFocusEvent& event) {

    Refresh();
    event.Skip();
}

void
wxMoRotaryCtrl::OnPaint(wxPaintEvent& event) {

    wxBufferedPaintDC dc(this);


    dc.SetBrush( wxBrush( GetBackgroundColour(), wxSOLID ) );
    dc.SetPen( wxPen( GetForegroundColour(), 1, wxTRANSPARENT ) );

    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    float ra = wxMin(GetSize().x / 2,GetSize().y / 2) / 1;
    float ra2 = wxMin(GetSize().x / 2,GetSize().y / 2) / 1.8;
    float ra3 = wxMin(GetSize().x / 2,GetSize().y / 2) / 4;

    float xc = GetSize().x / 2.0;
    float yc = GetSize().y / 2.0;

    //float normalpos = (float)SlidePosition() / (float)m_max;

    float normalpos = (float)GetValue()/ (float)m_max;


    float angposition = m_angmin + (m_angmax-m_angmin)*normalpos ;

    ///CIRCULO MAXIMO
    dc.SetBrush( wxBrush( wxColour( 95, 95, 95 ), wxSOLID ) );

    if ( (this) == FindFocus() ) {
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    } else dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );


    dc.DrawCircle( xc, yc , ra+1 );

    dc.SetBrush( wxBrush( wxColour(0,0,0), wxSOLID ) );
    dc.DrawCircle( xc, yc , ra );

    //dc.DrawArc( xc-ra*sin(angposition), yc+ra*cos(angposition), xc-ra*sin(angmin), yc+ra*cos(angmin) , xc, yc );

    ///ARCO GAUGE
    dc.SetBrush( wxBrush( wxColour(0,200,0), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 0, wxTRANSPARENT ) );
    dc.DrawArc( xc-(ra-1)*sin(angposition), yc+(ra-1)*cos(angposition), xc-(ra-1)*sin(m_angmin), yc+(ra-1)*cos(m_angmin) , xc, yc );
    //dc.DrawArc( xc-ra*sin(angmax), yc+ra*cos(angmax) , xc-ra*sin(angposition), yc+ra*cos(angposition), xc, yc );

    //dc.DrawCircle( xc, yc, ra-1);

    ///CIRCULO CENTRAL
    dc.SetBrush( wxBrush( wxColour(115,115,115), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(115,55,55), 1, wxTRANSPARENT ) );
    dc.DrawCircle( xc, yc , ra2 );

    dc.SetBrush( wxBrush( wxColour(95,95,95), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(115,115,115), 1, wxSOLID ) );
    dc.DrawCircle( xc, yc , ra2*0.8 );



    ///MARCADOR (circular)
    float xb = xc - (ra2*0.8-(ra*0.1))*sin( angposition );
    float yb = yc + (ra2*0.8-(ra*0.1))*cos( angposition );
    dc.SetBrush( wxBrush( wxColour(255,0,0), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    dc.DrawCircle( xb, yb , ra*0.17 );


    //dc.SetFont(wxFont(7));
    ///TEXTO CENTRAL
    if (m_bStartDragging) {
        wxString s;
        s.Printf(_T("%4.2f"),normalpos);
        dc.SetFont(wxFont( 8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ));
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
        dc.SetTextForeground(wxColour(255,255,255));
        dc.DrawText( s , xc-10, yc );
    }
    ///ticks
    dc.SetBrush( wxBrush( wxColour(128,128,128), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    int nticks = 10;
    float dticks = ( (float)(m_angmax-m_angmin)/ (float)nticks );
    float ysize;
    float i_f;
    float ra_f,ra3_f;

    ra_f = ra;
    ra3_f = ra3;

    for(int i =0; i<nticks; i++ ) {
        ( i % 2 ) == 0 ? ysize = (ra_f-ra3_f) / 3.0f: ysize = (ra_f-ra3_f) / 5.0f;
        i_f = (float)i;
        dc.DrawLine( xc-ra_f*sin(m_angmin+i_f*dticks), yc+ra_f*cos(m_angmin+i_f*dticks), xc-(ra_f-ysize)*sin(m_angmin+i_f*dticks), yc+(ra_f-ysize)*cos(m_angmin+i_f*dticks) );
    }

/*
    dc.SetBrush( wxBrush( wxColour(80,80,80), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );

    ///background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    ///gauge
    dc.SetBrush( wxBrush( wxColour(0,200,50), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    //dc.DrawRectangle( 1, 1, SlidePosition()-2, GetSize().y-2 );
    wxRect Rgauge( 1, 1, SlidePosition()-2, GetSize().y-2 );
    dc.GradientFillLinear( Rgauge, wxColour(0,50,0), wxColour(0,200,0) );

    ///ticks
    dc.SetBrush( wxBrush( wxColour(128,128,128), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    int nticks = 5;
    int dticks = (GetSize().x / nticks );
    int ysize;

    for(int i =0; i<nticks; i++ ) {
        ( i % 3 ) == 0 ? ysize = GetSize().y / 2 : ysize = GetSize().y / 3;
        dc.DrawLine( i*dticks, ysize, i*dticks, GetSize().y );
    }
*/

}


void wxMoRotaryCtrl::SetRange( int min, int max ) {
    if ( min >= max ) {
        wxMessageBox(wxT("wxMoRotaryCtrl error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void wxMoRotaryCtrl::SetRangeAngle( float angmin, float angmax ) {

    this->m_angmin = wxMax(0.0,wxMin(angmin,wxMoRotaryCtrl::PI2) );
    this->m_angmax = wxMin( wxMax(angmax,angmin), wxMoRotaryCtrl::PI2);
    //this->m_angmin = angmin;
    //this->m_angmax = angmax;

}


void wxMoRotaryCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
    Refresh();
}

void wxMoRotaryCtrl::SetValue( int value ) {

    ChangeValue(value);

    wxCommandEvent event( wxEVT_MOROTARYCTRL, m_windowId );
    event.SetInt( GetValue() );
    event.SetEventObject( this );

    ProcessEvent(event );

}


int wxMoRotaryCtrl::GetValue( ) {

    return m_value;

}

float wxMoRotaryCtrl::ValueToAngle( int val ) {
    float ang = 0.0;

    ang = m_angmin + val * ( m_angmax - m_angmin ) / (float)m_max ;

    return ang;
}


int wxMoRotaryCtrl::AngleToValue( float angle ) {
    int val = m_value;
    if ( angle > m_angmin && angle < m_angmax ) {
        val = ( angle - m_angmin) * (float)m_max / ( m_angmax - m_angmin );
    }

    return val;

}

//from value to x coord position
float wxMoRotaryCtrl::SlideAngle() {

    return ValueToAngle( m_value );
}


float wxMoRotaryCtrl::AngleValue( int pointerx, int pointery ) {

    float xc = GetSize().x / 2.0;
    float yc = GetSize().y / 2.0;
    float vx = pointerx - xc;
    float vy = pointery - yc;
    float radv = sqrt(vx*vx+vy*vy);

    float angv = 0.0;

    if (vx<0)
        angv = atan2( -vx, vy );
    else
        angv = (2*wxMoRotaryCtrl::PI)-atan2( vx, vy );

    return angv;

}


//from x coord position to value
int wxMoRotaryCtrl::SlideValue( int pointerx, int pointery ) {

    float angv = AngleValue( pointerx, pointery);

    int val = m_value; //hacer funcion

    if ( angv > m_angmin && angv < m_angmax ) {
        val = ( angv - m_angmin) * (float)m_max / ( m_angmax - m_angmin );
    }

    return (int)val;
}


void wxMoRotaryCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoRotaryCtrl::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }

    if (event.ButtonDClick(wxMOUSE_BTN_LEFT )) {
        SetValue( SlideValue( event.GetX(), event.GetY()));
        Refresh();
    }

    if (event.GetWheelDelta()>0) {
        SetValue( GetValue()+event.GetWheelRotation()/50 );
        Refresh();
    }

    if (event.LeftDown() && AngleClickPosition==0.0) {
        AngleClickPosition = AngleValue( event.GetX(), event.GetY());
        AngleValueWhenClicked = SlideAngle();
        Refresh();
    }
    if (event.LeftUp()) {
        AngleClickPosition = 0.0;
        AngleValueWhenClicked = 0.0;
        Refresh();
    }

    if (event.Dragging()) {
        if (m_bStartDragging==false) {
            m_bStartDragging = true;
            wxWindow::CaptureMouse();
        }
        float AngNew = AngleValue( event.GetX(), event.GetY());
        float AngAct = AngleValueWhenClicked + (AngNew - AngleClickPosition);
        SetValue( AngleToValue( AngAct ) );
        Refresh();
    }

    if (!event.Dragging()) {
        if (m_bStartDragging==true) {
            m_bStartDragging = false;
            wxWindow::ReleaseMouse();
        }
    }

    event.Skip();
}

void wxMoRotaryCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoRotaryCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

DEFINE_EVENT_TYPE(wxEVT_MOROTARYCTRL)
