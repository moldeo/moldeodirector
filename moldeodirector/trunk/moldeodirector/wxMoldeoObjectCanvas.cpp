#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "wxMoldeoPinCtrl.h"
#include "wxMoldeoObjectCanvas.h"
#include <wx/dcbuffer.h>

DEFINE_EVENT_TYPE( wxEVT_MOLDEOOBJECT )

const long wxMoldeoObjectCanvas::TIMELINETIMER_ID = 1;

BEGIN_EVENT_TABLE( wxMoldeoObjectCanvas, wxPanel )
    EVT_TIMER( wxMoldeoObjectCanvas::TIMELINETIMER_ID, wxMoldeoObjectCanvas::OnTimer)
    EVT_PAINT( wxMoldeoObjectCanvas::OnPaint )
    EVT_MOUSE_EVENTS( wxMoldeoObjectCanvas::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( wxMoldeoObjectCanvas::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( wxMoldeoObjectCanvas::OnCaptureChangedEvent )
    //EVT_ERASE_BACKGROUND(wxMoldeoObjectCanvas::OnEraseBackground)
    EVT_COMMAND( -1, wxEVT_MOLDEOPIN_BEGINDRAGLEFT, wxMoldeoObjectCanvas::OnPinBeginDragLeft  )
    EVT_COMMAND( -1, wxEVT_MOLDEOPIN_DRAGLEFT, wxMoldeoObjectCanvas::OnPinDragLeft  )
    EVT_COMMAND( -1, wxEVT_MOLDEOPIN_ENDDRAGLEFT, wxMoldeoObjectCanvas::OnPinEndDragLeft  )
END_EVENT_TABLE()

wxMoldeoObjectCanvas::wxMoldeoObjectCanvas( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name  ) :
wxScrolledWindow( parent, id,  pos, size, style | wxNO_BORDER, name ) {

    m_bStartDragging = false;
    m_bLeftSizeDragging = false;
    m_bRightSizeDragging = false;
    m_bMovingDragging = false;

    m_bLineDrawing = false;
    pDrawingLine = NULL;
    Mx = 0;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM );
    SetBackgroundColour(parent->GetBackgroundColour());


    //m_timer.SetOwner( this, wxMoldeoObjectCanvas::TIMELINETIMER_ID);
	//m_timer.Start(30);

}

wxMoldeoObjectCanvas::~wxMoldeoObjectCanvas() {


}

void
wxMoldeoObjectCanvas::OnTimer( wxTimerEvent &event) {

	//m_play_value = moGetTicks();
	//m_play_value = wxGetLocalTimeMillis();
	//Refresh();

}
/*
void wxMoldeoObjectCanvas::OnEraseBackground(wxEraseEvent& event) {

}
*/

void wxMoldeoObjectCanvas::OnPinBeginDragLeft( wxCommandEvent& event ) {
    //wxMessageBox("test");

    event.GetEventObject();
    //LineStartX = event.GetClientData();
    LineStartX = ScreenToClient(wxGetMousePosition()).x;
    LineStartY = ScreenToClient(wxGetMousePosition()).y;
    LineEndX = 0;
    LineEndY = 0;
    m_bLineDrawing = true;

    //pDrawingLine = new wxMoldeoLineCtrl( this, -1, 0, 0, 0, wxPoint(LineStartX,LineStartY), wxSize(LineEndX,LineEndY) );

    //wxWindow::CaptureMouse();
}

void wxMoldeoObjectCanvas::OnPinDragLeft( wxCommandEvent& event ) {
    //wxMessageBox("drag");

    event.GetEventObject();
    //LineStartX = event.GetClientData();
    //LineStartX = 0;
    //LineStartY = 0;
    LineEndX = ScreenToClient(wxGetMousePosition()).x;
    LineEndY = ScreenToClient(wxGetMousePosition()).y;
    m_bLineDrawing = true;

    //wxWindow::CaptureMouse();
    Refresh();
}

void wxMoldeoObjectCanvas::OnPinEndDragLeft( wxCommandEvent& event ) {
    //wxMessageBox("end");

    //event.GetEventObject();
    //LineStartX = event.GetClientData();
    //LineStartX = 0;
    //LineStartY = 0;
    //LineEndX = 0;
    //LineEndY = 0;
    //m_bLineDrawing = false;

    //wxWindow::CaptureMouse();
}

void
wxMoldeoObjectCanvas::OnPaint(wxPaintEvent& event) {

    wxBufferedPaintDC dc(this);

    int x,y;
    GetVirtualSize(&x,&y);

    DoPrepareDC(dc);



    wxPoint Triangle[3];


    ///background
    dc.SetBrush( wxBrush( GetBackgroundColour(), wxSOLID ) );
    dc.SetPen( wxPen( GetForegroundColour(), 0, wxTRANSPARENT ) );

    dc.DrawRectangle( 0, 0, x, y );


    ///rounded rectangle
    /*
    dc.SetBrush( wxBrush( GetBackgroundColour(), wxSOLID ) );
    dc.SetPen( wxPen( GetForegroundColour(), 1, wxSOLID ) );
    dc.DrawRoundedRectangle( 0, 0, GetSize().x, GetSize().y,  10.0 );
    dc.DrawLine( 0, 18 , GetSize().x, 18);
    */

    for( int i=0; i<x; i+=52 ) {
        dc.SetPen( wxPen( wxColour(0,0,0), 1, wxSOLID ) );
        dc.DrawLine( i, 0, i, y );

    }

    for( int j=0; j<y; j+=52 ) {
        dc.SetPen( wxPen( wxColour(0,0,0), 1, wxSOLID ) );
        dc.DrawLine( 0, j, x, j );

    }

    wxString deb;
    //deb.Printf(GetName()+": %i",GetSize().GetX());
    deb = this->GetName();
    dc.SetFont(wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ));
    dc.DrawText(deb,10,4);

    wxScrolledWindow::OnPaint(event);

    if (m_bLineDrawing) {
        LineEndX = ScreenToClient(wxGetMousePosition()).x;
        LineEndY = ScreenToClient(wxGetMousePosition()).y;
        //pDrawingLine->SetSize(LineStartX, LineStartY, LineEndX - LineStartX, LineEndY-LineStartY);
        dc.SetPen( wxPen( wxColour(0,0,0), 1, wxSOLID ) );
        dc.DrawLine( LineStartX, LineStartY, LineEndX, LineEndY );

        deb.Printf(_T(" mx: %i"), ScreenToClient( wxGetMousePosition()).x  );
        dc.DrawText( deb, 0, 0 );
    }


}



void wxMoldeoObjectCanvas::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("wxMoldeoObjectCanvas::Mouse event");

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

            if (m_bLineDrawing) {
                LineEndX = PW.x;
                LineEndY = PW.y;
            }

            //SetPlayValue( GetSlideValueToPlayValue( SlideValue( event.GetX() ) ) );
            //moSetDuration( m_play_value );
            Refresh();
        }
    }

    if (!event.Dragging()) {
        if (m_bStartDragging==true) {
            m_bStartDragging = false;
            wxMessageBox(_T("release moving"));
            wxWindow::ReleaseMouse();
        }
        if (!event.LeftIsDown()) {
            if (m_bLineDrawing) {
                m_bLineDrawing = false;
                wxMessageBox(_T("release line drawing"));
                wxWindow::ReleaseMouse();
            }
        }
    }


    event.Skip();
}

void wxMoldeoObjectCanvas::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void wxMoldeoObjectCanvas::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

