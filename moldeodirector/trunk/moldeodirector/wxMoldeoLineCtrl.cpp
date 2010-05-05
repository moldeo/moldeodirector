#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoldeoLineCtrl.h"
#include <wx/dcbuffer.h>

DEFINE_EVENT_TYPE( wxEVT_MOLDEOLINE )
DEFINE_EVENT_TYPE( wxEVT_MOLDEOLINE_BEGINDRAGLEFT)
DEFINE_EVENT_TYPE( wxEVT_MOLDEOLINE_DRAGLEFT)
DEFINE_EVENT_TYPE( wxEVT_MOLDEOLINE_ENDDRAGLEFT)

const long wxMoldeoLineCtrl::MOLDEOLINETIMER_ID = 1;

BEGIN_EVENT_TABLE( wxMoldeoLineCtrl, wxControl )
    EVT_TIMER( wxMoldeoLineCtrl::MOLDEOLINETIMER_ID, wxMoldeoLineCtrl::OnTimer)
    EVT_PAINT( wxMoldeoLineCtrl::OnPaint )
    EVT_MOUSE_EVENTS( wxMoldeoLineCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoldeoLineCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoldeoLineCtrl::OnCaptureChangedEvent )
END_EVENT_TABLE()

wxMoldeoLineCtrl::wxMoldeoLineCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
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

    //m_timer.SetOwner( this, wxMoldeoLineCtrl::MOLDEOLINETIMER_ID);
	//m_timer.Start(30);

    wxSize screenSize = wxGetDisplaySize();
    bitmap = wxBitmap(screenSize.x, screenSize.y);

    wxScreenDC sdc;
    wxMemoryDC mdc;

    wxPoint AP = ClientToScreen(wxPoint(0,0));
    mdc.SelectObject(bitmap);
    mdc.Blit( 0, 0, screenSize.x, screenSize.y, &sdc, AP.x, AP.y);
    mdc.SelectObject(wxNullBitmap);

}

wxMoldeoLineCtrl::~wxMoldeoLineCtrl() {


}

void
wxMoldeoLineCtrl::OnTimer( wxTimerEvent &event) {

	//m_play_value = moGetTicks();
	//m_play_value = wxGetLocalTimeMillis();
	//Refresh();

}

void
wxMoldeoLineCtrl::OnPaint(wxPaintEvent& event) {

    //wxBufferedPaintDC dc(this);



    wxPoint PW = GetPosition();
    wxSize  SW = GetSize();






    //sdc.StartDrawingOnTop(this);

    //wxBufferedPaintDC dc(this);

    //wxPoint Triangle[3];
    //dc.Clear();
    //dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );

    //wxBitmap bmp(wxT(“toucan.png”), wxBITMAP_TYPE_PNG);


    wxBufferedPaintDC dc(this);
    dc.DrawBitmap(bitmap, 0, 0, true);


    //dc.DrawLine( ClientToScreen(PW).x, ClientToScreen(PW).y, ClientToScreen(PW).x+SW.x, ClientToScreen(PW).y+SW.y);
    dc.DrawLine( 0, 0, SW.x, SW.y);

    //sdc.EndDrawingOnTop();

    //wxBufferedPaintDC bdc(this);

    //bdc.DrawBitmap( bitmap, wxCoord(10), wxCoord(0) );

    ///background
    /*
    dc.SetPen( wxPen( wxColour(255,255,255), 0, wxTRANSPARENT ) );
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    dc.DrawRectangle( GetSize().x - 4, GetSize().y/2 - 2, 4 , 4 );
    */

    ///gauge
/*
    dc.SetBrush( wxBrush( wxColour(170,170,0), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    dc.DrawRectangle( 1, 1, SlidePosition()-2, GetSize().y-2 );
    */

    ///leftgrab
    /*
    if (m_bLeftSizeDragging) {
        dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    } else {
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    }*/
/*
    Triangle[0].x = 0;
    Triangle[0].y = 0;

    Triangle[1].x = 0;
    Triangle[1].y = GetSize().y;

    Triangle[2].x = 4;
    Triangle[2].y = GetSize().y/2;

    dc.DrawPolygon( 3, Triangle, 0, 0 );
*/
    ///rightgrab
    /*
    if (m_bRightSizeDragging) {
        dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    } else {
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    }
    */

/*
    Triangle[0].x = GetSize().x-1;
    Triangle[0].y = 0;

    Triangle[1].x = GetSize().x-1;
    Triangle[1].y = GetSize().y;

    Triangle[2].x = GetSize().x-5;
    Triangle[2].y = GetSize().y/2;

    dc.DrawPolygon( 3, Triangle, 0, 0 );
*/

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
    //wxString deb;
    //deb.Printf(GetName()+": %i",GetSize().GetX());
    //deb = this->GetLabelText();
    //dc.SetFont(wxFont( 8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ));
    //dc.DrawText(deb,4,4);

/*
    if ( m_bMovingDragging) {
        wxPoint PW = GetPosition();
        wxSize  SW = GetSize();
        //SetSize( GetParent()->ScreenToClient(wxGetMousePosition()).x-Px, GetParent()->ScreenToClient(wxGetMousePosition()).y-Py, SW.GetX(), SW.GetY() );
        dc.DrawLine( ScreenToClient(wxGetMousePosition()).x, ScreenToClient(wxGetMousePosition()).y, SW.GetX()-2, SW.GetY()/2 );
    }
    */

}


void wxMoldeoLineCtrl::SetRange( int min, int max ) {
    if ( min >= max ) {
        wxMessageBox(wxT("wxMoldeoLineCtrl error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void wxMoldeoLineCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
}


void wxMoldeoLineCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoldeoLineCtrl::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }

/*
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
*/

    if (event.LeftDown() && !m_bMovingDragging) {
        m_bMovingDragging = ( 3<event.GetX() && event.GetX()<=(GetSize().GetX()-3) ) && ( 3<event.GetY() && event.GetY()<=(GetSize().GetY()-3) );
        Px = event.GetX();
        Py = event.GetY();
        Refresh();
    }
    if (event.LeftUp() && m_bMovingDragging) {
        m_bMovingDragging = false;
        Refresh();
    }

/*
    if ((0<event.GetX() && event.GetX()<=3) ||
    ( (GetSize().GetX()-3)<event.GetX() && event.GetX()<=(GetSize().GetX()+2) )) {
        //
        //m_bRightSizeDragging = false;
        //m_bLeftSizeDragging = true;
        this->SetCursor( wxCursor(wxCURSOR_SIZEWE) );

    } else this->SetCursor( wxCursor() );

    */
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

    /*
    if (event.Button(wxMOUSE_BTN_RIGHT )) {
        SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.Button(wxMOUSE_BTN_LEFT )) {
        SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
        //moSetDuration( m_play_value );
        //moAbstract::MODebug2->Push( IntToStr(m_play_value) );
        Refresh();
    }*/

    if (event.Dragging()) {
        /*if (event.RightIsDown()) {

            (if (m_bStartDragging==false) {
                m_bStartDragging = true;
                wxWindow::CaptureMouse();
            }
            SetValue( SlideValue( event.GetX() ) );
            Refresh();
        }*/

        if (event.LeftIsDown()) {

            if (m_bStartDragging==false) {
                m_bStartDragging = true;
                //m_bRightSizeDragging = ( (GetSize().GetX()-3)<event.GetX() && event.GetX()<=GetSize().GetX() );
                //wxWindow::CaptureMouse();
                wxCommandEvent event( wxEVT_MOLDEOLINE_BEGINDRAGLEFT, m_windowId );
                event.SetClientData( NULL );
                event.SetEventObject( this );
                GetParent()->GetParent()->AddPendingEvent( event );
            }

            wxCommandEvent event( wxEVT_MOLDEOLINE_DRAGLEFT, m_windowId );
            event.SetClientData( NULL );
            event.SetEventObject( this );
            GetParent()->GetParent()->AddPendingEvent( event );

            wxPoint PW = GetPosition();
            wxSize  SW = GetSize();

/*
            if ( (SW.GetX()-event.GetX())>0 && m_bLeftSizeDragging) {
                SetSize( PW.x+event.GetX(), PW.y, SW.GetX()-event.GetX(), SW.GetY() );
            }
            if ( event.GetX()>0 && m_bRightSizeDragging) {
                SetSize( PW.x, PW.y, event.GetX(), SW.GetY() );
            }
            */
            //if ( m_bMovingDragging) {
                //SetSize( GetParent()->ScreenToClient(wxGetMousePosition()).x-Px, GetParent()->ScreenToClient(wxGetMousePosition()).y-Py, SW.GetX(), SW.GetY() );

            //}

            //SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
            //moSetDuration( m_play_value );
            Refresh();
        }
    }

    /*if (!event.Dragging()) {
        if (m_bStartDragging==true) {
            m_bStartDragging = false;
            wxCommandEvent event( wxEVT_MOLDEOLINE_ENDDRAGLEFT, m_windowId );
            event.SetClientData( NULL );
            event.SetEventObject( this );
            GetParent()->GetParent()->AddPendingEvent( event );
            //wxWindow::ReleaseMouse();
        }
    }*/


    event.Skip();
}

void wxMoldeoLineCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoldeoLineCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}





