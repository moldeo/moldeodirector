#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoTimelineBandCtrl.h"
#include <wx/dcbuffer.h>

DEFINE_EVENT_TYPE( wxEVT_MO_TIMELINEBAND )

const long wxMoTimelineBandCtrl::TIMELINETIMER_ID = 1;

BEGIN_EVENT_TABLE( wxMoTimelineBandCtrl, wxControl )
    EVT_TIMER( wxMoTimelineBandCtrl::TIMELINETIMER_ID, wxMoTimelineBandCtrl::OnTimer)
    EVT_PAINT( wxMoTimelineBandCtrl::OnPaint )
    EVT_MOUSE_EVENTS( wxMoTimelineBandCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoTimelineBandCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoTimelineBandCtrl::OnCaptureChangedEvent )
END_EVENT_TABLE()

wxMoTimelineBandCtrl::wxMoTimelineBandCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxControl( parent, id,  pos, size, style | wxNO_BORDER, validator, name ) {
    m_min = minvalue;
    m_max = maxvalue;
    m_value = value;
    m_bStartDragging = false;
    m_bLeftSizeDragging = false;
    m_bRightSizeDragging = false;
    m_bMovingDragging = false;
    Mx = 0;
    SetBackgroundStyle(wxBG_STYLE_CUSTOM );

    m_pixel_interval = 500;
    m_play_value = 0;
    m_play_in = 0;
    m_max_play_value = m_max * m_pixel_interval;
    m_play_out = m_max_play_value;
    m_render_in = m_play_in;
    m_render_out = m_play_out;

    m_timer.SetOwner( this, wxMoTimelineBandCtrl::TIMELINETIMER_ID);
	m_timer.Start(30);

}

wxMoTimelineBandCtrl::~wxMoTimelineBandCtrl() {


}

void
wxMoTimelineBandCtrl::OnTimer( wxTimerEvent &event) {

	//m_play_value = moGetTicks();
	//m_play_value = wxGetLocalTimeMillis();
	//Refresh();

}

void
wxMoTimelineBandCtrl::OnPaint(wxPaintEvent& event) {

    wxBufferedPaintDC dc(this);

    wxPoint Triangle[3];

    dc.SetBrush( wxBrush( wxColour(128,128,128), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );

    ///background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    ///gauge
    dc.SetBrush( wxBrush( wxColour(170,170,0), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    dc.DrawRectangle( 1, 1, SlidePosition()-2, GetSize().y-2 );

    ///leftgrab
    if (m_bLeftSizeDragging) {
        dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    } else {
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    }

    Triangle[0].x = 0;
    Triangle[0].y = 0;

    Triangle[1].x = 0;
    Triangle[1].y = GetSize().y;

    Triangle[2].x = 4;
    Triangle[2].y = GetSize().y/2;

    dc.DrawPolygon( 3, Triangle, 0, 0 );

    ///rightgrab
    if (m_bRightSizeDragging) {
        dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    } else {
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    }

    Triangle[0].x = GetSize().x-1;
    Triangle[0].y = 0;

    Triangle[1].x = GetSize().x-1;
    Triangle[1].y = GetSize().y;

    Triangle[2].x = GetSize().x-5;
    Triangle[2].y = GetSize().y/2;

    dc.DrawPolygon( 3, Triangle, 0, 0 );


    ///ticks
    /*
        dc.SetBrush( wxBrush( wxColour(128,128,128), wxTRANSPARENT ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );

    int nticks = 100;
    float dticks = ((float)GetSize().x / (float)nticks );
    int ysize;

    for(int i =0; i<nticks; i++ ) {
        ( i % 10 ) == 0 ? ysize = GetSize().y - 4 : ysize = GetSize().y / 2;
        dc.DrawLine( i*dticks, 0, i*dticks, ysize );
    }
    */

    ///marks
/*    dc.SetBrush( wxBrush( wxColour(60,60,60), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    Triangle[0].x = SlidePosition();
    Triangle[0].y = GetSize().y / 3;
    Triangle[1].x = SlidePosition()-5;
    Triangle[1].y = GetSize().y;
    Triangle[2].x = SlidePosition()+5;
    Triangle[2].y = GetSize().y;
    dc.DrawPolygon( 3, Triangle, 0, 0 );
*/
    ///PLAY mark
/*
    dc.SetBrush( wxBrush( wxColour(255,60,60), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 2, wxSOLID ) );
    Triangle[0].x = PlayValueToSlidePosition( m_play_value );
    Triangle[0].y = GetSize().y / 3;
    Triangle[1].x = PlayValueToSlidePosition( m_play_value )-5;
    Triangle[1].y = GetSize().y;
    Triangle[2].x = PlayValueToSlidePosition( m_play_value )+5;
    Triangle[2].y = GetSize().y;
    dc.DrawPolygon( 3, Triangle, 0, 0 );
*/
    wxString deb;
    deb.Printf(GetName()+_T(": %i"),GetSize().GetX());
    dc.DrawText(deb,20,0);
}


void wxMoTimelineBandCtrl::SetRange( int min, int max ) {
    if ( min >= max ) {
        wxMessageBox(wxT("wxMoTimelineBandCtrl error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void wxMoTimelineBandCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
}

void wxMoTimelineBandCtrl::SetValue( int value ) {

    ChangeValue(value);

    wxCommandEvent event( wxEVT_MO_TIMELINEBAND, m_windowId );
    event.SetInt( GetValue() );
    event.SetEventObject( this );

    ProcessEvent(event );

}


int wxMoTimelineBandCtrl::GetValue( ) {

    return m_value;

}

//from value to x coord position
int wxMoTimelineBandCtrl::SlidePosition() {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( m_value - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from value to x coord position
int wxMoTimelineBandCtrl::PlayValueToSlidePosition( int value_ms ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( GetPlayValueToSlideValue( value_ms ) - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from x coord position to value
int wxMoTimelineBandCtrl::SlideValue( int pointerxposition ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;


    int value = (pointerxposition * pWidth ) / GetSize().x;

    if (value<=0) value = 0;
    if (value>pWidth) value = pWidth;

    value+=m_min;
    return value;
}

void wxMoTimelineBandCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoTimelineBandCtrl::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }

    if (event.LeftDown() && !m_bLeftSizeDragging) {
        m_bLeftSizeDragging = (-1<=event.GetX() && event.GetX()<=3);
        Refresh();
    }
    if (event.LeftUp() && m_bLeftSizeDragging) {
        m_bLeftSizeDragging = false;
        Refresh();
    }

    if (event.LeftDown() && !m_bRightSizeDragging) {
        m_bRightSizeDragging = ( (GetSize().GetX()-5)<event.GetX() && event.GetX()<=(GetSize().GetX()+2) );
        Refresh();
    }
    if (event.LeftUp() && m_bRightSizeDragging) {
        m_bRightSizeDragging = false;
        Refresh();
    }


    if (event.LeftDown() && !m_bMovingDragging) {
        m_bMovingDragging = ( 3<event.GetX() && event.GetX()<=(GetSize().GetX()-3) );
        Px = event.GetX();
        Refresh();
    }
    if (event.LeftUp() && m_bMovingDragging) {
        m_bMovingDragging = false;
        Refresh();
    }


    if ((0<event.GetX() && event.GetX()<=3) ||
    ( (GetSize().GetX()-3)<event.GetX() && event.GetX()<=(GetSize().GetX()+2) )) {
        //
        //m_bRightSizeDragging = false;
        //m_bLeftSizeDragging = true;
        this->SetCursor( wxCursor(wxCURSOR_SIZEWE) );
    } else this->SetCursor( wxCursor() );
    /* else if ( (GetSize().GetX()-3)<event.GetX() && event.GetX()<=GetSize().GetX() ) {
            m_bRightSizeDragging = true;
            m_bLeftSizeDragging = false;
    } else {
        m_bRightSizeDragging = false;
        m_bLeftSizeDragging = false;
    }*/

    /*if ( m_bLeftSizeDragging || m_bRightSizeDragging ) {
        this->SetCursor( wxCursor(wxCURSOR_SIZEWE) );
    } else this->SetCursor( wxCursor() );
*/
    if (event.Button(wxMOUSE_BTN_RIGHT )) {
        SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.Button(wxMOUSE_BTN_LEFT )) {
        SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
        //moSetDuration( m_play_value );
        //moAbstract::MODebug2->Push( IntToStr(m_play_value) );
        Refresh();
    }

    if (event.Dragging()) {
        if (event.RightIsDown()) {
            if (m_bStartDragging==false) {
                m_bStartDragging = true;
                wxWindow::CaptureMouse();
            }
            SetValue( SlideValue( event.GetX() ) );
            Refresh();
        }

        if (event.LeftIsDown()) {
            if (m_bStartDragging==false) {
                m_bStartDragging = true;
                //m_bRightSizeDragging = ( (GetSize().GetX()-3)<event.GetX() && event.GetX()<=GetSize().GetX() );
                wxWindow::CaptureMouse();
            }
            wxPoint PW = GetPosition();
            wxSize  SW = GetSize();

            if ( (SW.GetX()-event.GetX())>0 && m_bLeftSizeDragging) {
                SetSize( PW.x+event.GetX(), PW.y, SW.GetX()-event.GetX(), SW.GetY() );
            }
            if ( event.GetX()>0 && m_bRightSizeDragging) {
                SetSize( PW.x, PW.y, event.GetX(), SW.GetY() );
            }
            if ( m_bMovingDragging) {
                SetSize( GetParent()->ScreenToClient(wxGetMousePosition()).x-Px, PW.y, SW.GetX(), SW.GetY() );
            }

            //SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
            //moSetDuration( m_play_value );
            Refresh();
        }
    }

    if (!event.Dragging()) {
        if (m_bStartDragging==true) {
            m_bStartDragging = false;
            wxWindow::ReleaseMouse();
        }
    }

    event.Skip();
}

void wxMoTimelineBandCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoTimelineBandCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

void wxMoTimelineBandCtrl::SetMaxPlayValue( int value ) {
        m_max_play_value = value;
}

void wxMoTimelineBandCtrl::SetPlayValue( int value ) {
        m_play_value = value;
}

int wxMoTimelineBandCtrl::GetMaxPlayValue() {
        return m_max_play_value;
}

int wxMoTimelineBandCtrl::GetPlayValueToSlideValue( int playvalue ) {
        return playvalue / m_pixel_interval;
}

int wxMoTimelineBandCtrl::GetSlideValueToPlayValue( int slidevalue ) {
        return slidevalue * m_pixel_interval;
}

int wxMoTimelineBandCtrl::GetPlayValue() {
        return m_play_value;
}

void wxMoTimelineBandCtrl::SetPixelInterval( int pixelinterval ) {

        m_pixel_interval = pixelinterval;

}///miliseconds per pixel
int wxMoTimelineBandCtrl::GetPixelInterval() {

    return m_pixel_interval;

}///get miliseconds per pixel

void wxMoTimelineBandCtrl::SetPlayIn( int value ) {
    m_play_in = value;
}

int wxMoTimelineBandCtrl::GetPlayIn() {
    return m_play_out;
}

void wxMoTimelineBandCtrl::SetPlayOut( int value ) {
    m_play_out = value;
}

int wxMoTimelineBandCtrl::GetPlayOut() {
    return m_play_out;
}

void wxMoTimelineBandCtrl::SetRenderIn( int value ) {

    m_render_in = value;

}

int wxMoTimelineBandCtrl::GetRenderIn() {
    return m_render_in;
}

void wxMoTimelineBandCtrl::SetRenderOut( int value ) {
    m_render_out = value;
}

int wxMoTimelineBandCtrl::GetRenderOut() {
    return m_render_out;
}
