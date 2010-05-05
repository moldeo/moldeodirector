#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoldeoObjectCtrl.h"
#include <wx/dcbuffer.h>

DEFINE_EVENT_TYPE( wxEVT_MOLDEOOBJECT )

const long wxMoldeoObjectCtrl::TIMELINETIMER_ID = 1;

BEGIN_EVENT_TABLE( wxMoldeoObjectCtrl, wxPanel )
    EVT_TIMER( wxMoldeoObjectCtrl::TIMELINETIMER_ID, wxMoldeoObjectCtrl::OnTimer)
    EVT_PAINT( wxMoldeoObjectCtrl::OnPaint )
    EVT_MOUSE_EVENTS( wxMoldeoObjectCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoldeoObjectCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoldeoObjectCtrl::OnCaptureChangedEvent )
    EVT_ERASE_BACKGROUND(wxMoldeoObjectCtrl::OnEraseBackground)
END_EVENT_TABLE()

wxMoldeoObjectCtrl::wxMoldeoObjectCtrl( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name  ) :
wxPanel( parent, id,  pos, size, style | wxNO_BORDER, name ) {

    m_bStartDragging = false;
    m_bLeftSizeDragging = false;
    m_bRightSizeDragging = false;
    m_bMovingDragging = false;
    Mx = 0;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM );
    SetBackgroundColour(parent->GetBackgroundColour());

    //m_timer.SetOwner( this, wxMoldeoObjectCtrl::TIMELINETIMER_ID);
	//m_timer.Start(30);

}

wxMoldeoObjectCtrl::~wxMoldeoObjectCtrl() {


}

void
wxMoldeoObjectCtrl::OnTimer( wxTimerEvent &event) {

	//m_play_value = moGetTicks();
	//m_play_value = wxGetLocalTimeMillis();
	//Refresh();

}

void wxMoldeoObjectCtrl::OnEraseBackground(wxEraseEvent& event) {

}

void
wxMoldeoObjectCtrl::OnPaint(wxPaintEvent& event) {


    wxBufferedPaintDC dc(this);

    wxPoint Triangle[3];


    ///background
    dc.SetBrush( wxBrush( GetBackgroundColour(), wxSOLID ) );
    dc.SetPen( wxPen( GetForegroundColour(), 0, wxTRANSPARENT ) );

    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );
    //dc.DrawBitmap(bg.GetSubBitmap(self.GetRect()), 0, 0);


    ///rounded rectangle
    dc.SetBrush( wxBrush( wxColour(128,128,128), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    dc.DrawRoundedRectangle( 0, 0, GetSize().x, GetSize().y,  10.0 );
    dc.DrawLine( 0, 18 , GetSize().x, 18);

    ///gauge

    ///rightgrab
    if (m_bRightSizeDragging) {
        dc.SetBrush( wxBrush( wxColour(0,255,0), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    } else {
        dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
    }

    Triangle[0].x = GetSize().x-1;
    Triangle[0].y = GetSize().y-9;

    Triangle[1].x = GetSize().x-1;
    Triangle[1].y = GetSize().y-1;

    Triangle[2].x = GetSize().x-9;
    Triangle[2].y = GetSize().y-1;

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
    //deb.Printf(GetName()+": %i",GetSize().GetX());
    deb = this->GetName();
    dc.SetFont(wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ));
    dc.DrawText(deb,10,4);
}



void wxMoldeoObjectCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoldeoObjectCtrl::Mouse event");

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
*/

    if (event.LeftDown() && !m_bRightSizeDragging) {
        m_bRightSizeDragging = ( (GetSize().GetX()-8)<event.GetX() && event.GetX()<=(GetSize().GetX()+2) )
                                && ( (GetSize().GetY()-8)<event.GetY() && event.GetY()<=(GetSize().GetY()+2) );
        Refresh();
    }
    if (event.LeftUp() && m_bRightSizeDragging) {
        m_bRightSizeDragging = false;
        Refresh();
    }


    if (event.LeftDown() && !m_bMovingDragging) {
        m_bMovingDragging = ( 3<event.GetX() && event.GetX()<=(GetSize().GetX()-8) ) && ( 3<event.GetY() && event.GetY()<=(GetSize().GetY()-8) );
        Px = event.GetX();
        Py = event.GetY();
        Refresh();
    }
    if (event.LeftUp() && m_bMovingDragging) {
        m_bMovingDragging = false;
        Refresh();
    }


    if (( (GetSize().GetX()-8)<event.GetX() && event.GetX()<=(GetSize().GetX()+2) )
                                && ( (GetSize().GetY()-8)<event.GetY() && event.GetY()<=(GetSize().GetY()+2) )) {
        //
        //m_bRightSizeDragging = false;
        //m_bLeftSizeDragging = true;
        this->SetCursor( wxCursor(wxCURSOR_SIZENWSE) );
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
        //SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.Button(wxMOUSE_BTN_LEFT )) {
        //SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
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
            //SetValue( SlideValue( event.GetX() ) );
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

            /*
            if ( (SW.GetX()-event.GetX())>0 && m_bLeftSizeDragging) {
                SetSize( PW.x+event.GetX(), PW.y, SW.GetX()-event.GetX(), SW.GetY() );
            }
            */
            if ( event.GetX()>0 && m_bRightSizeDragging) {
                SetSize( PW.x, PW.y, event.GetX(), event.GetY() );
            }
            if ( m_bMovingDragging) {
                SetSize( GetParent()->ScreenToClient(wxGetMousePosition()).x-Px, GetParent()->ScreenToClient(wxGetMousePosition()).y-Py, SW.GetX(), SW.GetY() );
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

void wxMoldeoObjectCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoldeoObjectCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

