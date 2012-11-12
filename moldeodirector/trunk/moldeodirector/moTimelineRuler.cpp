#include "moTimelineRuler.h"
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>

BEGIN_EVENT_TABLE( moTimelineRuler, wxControl )
    EVT_TIMER( TIMELINETICKS_ID, moTimelineRuler::OnTimer)
    EVT_PAINT( moTimelineRuler::OnPaint )
    EVT_MOUSE_EVENTS( moTimelineRuler::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( moTimelineRuler::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( moTimelineRuler::OnCaptureChangedEvent )
END_EVENT_TABLE()

moTimelineRuler::moTimelineRuler( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxControl( parent, id,  pos, size, style | wxNO_BORDER, validator, name ) {
    m_min = minvalue;
    m_max = maxvalue;
    m_value = value;
    m_bStartDragging = false;
    SetBackgroundStyle(wxBG_STYLE_CUSTOM );

    m_pixel_interval = 500;
    m_play_value = 0;
    m_play_in = 0;
    m_max_play_value = m_max * m_pixel_interval;
    m_play_out = m_max_play_value;
    m_render_in = m_play_in;
    m_render_out = m_play_out;

    m_timer.SetOwner( this, TIMELINETICKS_ID);
	m_timer.Start(30);

}

moTimelineRuler::~moTimelineRuler() {


}

void
moTimelineRuler::OnTimer( wxTimerEvent &event) {

	m_play_value = moGetTicks();
	Refresh();

}

void
moTimelineRuler::OnPaint(wxPaintEvent& event) {

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

    ///ticks
    dc.SetBrush( wxBrush( wxColour(128,128,128), wxTRANSPARENT ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    int nticks = 100;
    int dticks = (GetSize().x / nticks );
    int ysize;

    for(int i =0; i<nticks; i++ ) {
        ( i % 10 ) == 0 ? ysize = GetSize().y - 4 : ysize = GetSize().y / 2;
        dc.DrawLine( i*dticks, 0, i*dticks, ysize );
    }

    ///marks
    dc.SetBrush( wxBrush( wxColour(60,60,60), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    Triangle[0].x = SlidePosition();
    Triangle[0].y = GetSize().y / 3;
    Triangle[1].x = SlidePosition()-5;
    Triangle[1].y = GetSize().y;
    Triangle[2].x = SlidePosition()+5;
    Triangle[2].y = GetSize().y;
    dc.DrawPolygon( 3, Triangle, 0, 0 );

    ///PLAY mark
    dc.SetBrush( wxBrush( wxColour(255,60,60), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 2, wxSOLID ) );
    Triangle[0].x = PlayValueToSlidePosition( m_play_value );
    Triangle[0].y = GetSize().y / 3;
    Triangle[1].x = PlayValueToSlidePosition( m_play_value )-5;
    Triangle[1].y = GetSize().y;
    Triangle[2].x = PlayValueToSlidePosition( m_play_value )+5;
    Triangle[2].y = GetSize().y;
    dc.DrawPolygon( 3, Triangle, 0, 0 );

}


void moTimelineRuler::SetRange( int min, int max ) {
    if ( min >= max ) {
        wxMessageBox(wxT("moTimelineRuler error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void moTimelineRuler::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
}

void moTimelineRuler::SetValue( int value ) {

    ChangeValue(value);

    wxCommandEvent event( MO_EVT_DIRECTOR_TIMELINERULER, m_windowId );
    event.SetInt( GetValue() );
    event.SetEventObject( this );

    ProcessEvent(event );

}


int moTimelineRuler::GetValue( ) {

    return m_value;

}

//from value to x coord position
int moTimelineRuler::SlidePosition() {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( m_value - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from value to x coord position
int moTimelineRuler::PlayValueToSlidePosition( int value_ms ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( GetPlayValueToSlideValue( value_ms ) - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from x coord position to value
int moTimelineRuler::SlideValue( int pointerxposition ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;


    int value = (pointerxposition * pWidth ) / GetSize().x;

    if (value<=0) value = 0;
    if (value>pWidth) value = pWidth;

    value+=m_min;
    return value;
}

void moTimelineRuler::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("moTimelineRuler::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }
    if (event.Button(wxMOUSE_BTN_RIGHT )) {
        SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.Button(wxMOUSE_BTN_LEFT )) {
        SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
        moSetDuration( m_play_value );
        moAbstract::MODebug2->Push( IntToStr(m_play_value) );
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
                wxWindow::CaptureMouse();
            }
            SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
            moSetDuration( m_play_value );
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

void moTimelineRuler::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void moTimelineRuler::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

void moTimelineRuler::SetMaxPlayValue( int value ) {
        m_max_play_value = value;
}

void moTimelineRuler::SetPlayValue( int value ) {
        m_play_value = value;
}

int moTimelineRuler::GetMaxPlayValue() {
        return m_max_play_value;
}

int moTimelineRuler::GetPlayValueToSlideValue( int playvalue ) {
        return playvalue / m_pixel_interval;
}

int moTimelineRuler::GetSlideValueToPlayValue( int slidevalue ) {
        return slidevalue * m_pixel_interval;
}

int moTimelineRuler::GetPlayValue() {
        return m_play_value;
}

void moTimelineRuler::SetPixelInterval( int pixelinterval ) {

        m_pixel_interval = pixelinterval;

}///miliseconds per pixel
int moTimelineRuler::GetPixelInterval() {

    return m_pixel_interval;

}///get miliseconds per pixel

void moTimelineRuler::SetPlayIn( int value ) {
    m_play_in = value;
}

int moTimelineRuler::GetPlayIn() {
    return m_play_out;
}

void moTimelineRuler::SetPlayOut( int value ) {
    m_play_out = value;
}

int moTimelineRuler::GetPlayOut() {
    return m_play_out;
}

void moTimelineRuler::SetRenderIn( int value ) {

    m_render_in = value;

}

int moTimelineRuler::GetRenderIn() {
    return m_render_in;
}

void moTimelineRuler::SetRenderOut( int value ) {
    m_render_out = value;
}

int moTimelineRuler::GetRenderOut() {
    return m_render_out;
}

