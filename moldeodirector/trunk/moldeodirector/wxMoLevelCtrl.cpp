#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoLevelCtrl.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE( wxMoLevelCtrl, wxControl )
    EVT_PAINT( wxMoLevelCtrl::OnPaint )
    EVT_MOUSE_EVENTS( wxMoLevelCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoLevelCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoLevelCtrl::OnCaptureChangedEvent )
    EVT_KILL_FOCUS(wxMoLevelCtrl::OnKillFocus)
END_EVENT_TABLE()

wxMoLevelCtrl::wxMoLevelCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxControl( parent, id,  pos, size, style | wxNO_BORDER, validator, name ) {
    m_min = minvalue;
    m_max = maxvalue;
    m_value = value;
    m_bStartDragging = false;
    SetBackgroundStyle(wxBG_STYLE_CUSTOM );
    Px = 0;
    Mx = 0;
    Sx = 0;
    Vx = 0;

}

wxMoLevelCtrl::~wxMoLevelCtrl() {


}

void
wxMoLevelCtrl::OnKillFocus( wxFocusEvent& event) {

    Refresh();
    event.Skip();
}


void
wxMoLevelCtrl::OnPaint(wxPaintEvent& event) {

    wxBufferedPaintDC dc(this);

    dc.SetBrush( wxBrush( wxColour(80,80,80), wxSOLID ) );

    if ( (this) == FindFocus() ) {
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    } else dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );

    ///background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    ///gauge
    dc.SetBrush( wxBrush( wxColour(0,200,50), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    //dc.DrawRectangle( 1, 1, SlidePosition()-2, GetSize().y-2 );
    wxRect Rgauge( 1, 1, SlidePosition()-2, GetSize().y-2 );
    dc.GradientFillLinear( Rgauge, wxColour(80,150,80), wxColour(0,255,0), wxBOTTOM );

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

    ///text
    if (m_bStartDragging) {

        //wxString s;

        //s.Printf( , m_value);

        //dc.SetFont(wxFont( 8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ));
        //dc.SetTextForeground(wxColour(255,255,255));
        //dc.DrawText(s,GetSize().x/2-15,0);
    }
}


void wxMoLevelCtrl::SetRange( int min, int max ) {
    if ( min >= max ) {
        //wxMessageBox(_T("wxMoLevelCtrl error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void wxMoLevelCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
    Refresh();
}

void wxMoLevelCtrl::SetValue( int value ) {

    ChangeValue(value);

    wxCommandEvent event( wxEVT_MOLEVELCTRL, m_windowId );
    event.SetInt( GetValue() );
    event.SetEventObject( this );

    ProcessEvent(event );

}


int wxMoLevelCtrl::GetValue( ) {

    return m_value;

}

//from value to x coord position
int wxMoLevelCtrl::SlidePosition() {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( m_value - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from x coord position to value
int wxMoLevelCtrl::SlideValue( int pointerxposition ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;


    int value = (pointerxposition * pWidth ) / GetSize().x;

    if (value<=0) value = 0;
    if (value>pWidth) value = pWidth;

    value+=m_min;
    return value;
}

void wxMoLevelCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoLevelCtrl::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }
    if (event.Button(wxMOUSE_BTN_LEFT )) {
        //SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.GetWheelDelta()>0) {
        SetValue( GetValue()+event.GetWheelRotation()/50 );
        Refresh();
    }

    if (event.ButtonDClick()) {
        SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.LeftDown() && Px==0) {
        Px = event.GetX();
        Vx = SlidePosition();
        Refresh();
    }
    if (event.LeftUp()) {
        Px = 0;
        Vx = 0;
        Refresh();
    }

    if (event.Dragging()) {
        if (m_bStartDragging==false) {
            m_bStartDragging = true;
            wxWindow::CaptureMouse();
        }
        Mx = event.GetX();
        Sx = Vx + Mx - Px;
        SetValue( SlideValue( Sx ) );
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

void wxMoLevelCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoLevelCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

DEFINE_EVENT_TYPE(wxEVT_MOLEVELCTRL)
