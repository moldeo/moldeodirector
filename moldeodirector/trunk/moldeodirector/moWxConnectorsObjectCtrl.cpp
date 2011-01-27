#include "moWxConnectorsObjectCtrl.h"

BEGIN_EVENT_TABLE( moWxConnectorObjectCtrl, wxControl )
    EVT_PAINT( moWxConnectorObjectCtrl::OnPaint )
    EVT_MOUSE_EVENTS( moWxConnectorObjectCtrl::OnMouseEvent )
    EVT_MOUSE_CAPTURE_LOST( moWxConnectorObjectCtrl::OnCaptureLostEvent )
    EVT_MOUSE_CAPTURE_CHANGED( moWxConnectorObjectCtrl::OnCaptureChangedEvent )
END_EVENT_TABLE()

moWxConnectorObjectCtrl::moWxConnectorObjectCtrl( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxControl( parent, id,  pos, size, style | wxNO_BORDER | wxFULL_REPAINT_ON_RESIZE, validator, name ) {
    m_min = 0;
    m_max = 100;
    m_value = 50;
    m_bStartDragging = false;

}

moWxConnectorObjectCtrl::~moWxConnectorObjectCtrl() {


}

void
moWxConnectorObjectCtrl::OnPaint(wxPaintEvent& event) {

    wxPaintDC dc(this);

    dc.SetBrush( wxBrush( wxColour(120,120,120), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxSOLID) );

    //background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );

    //gauge
    dc.SetBrush( wxBrush( wxColour(220,220,220), wxSOLID) );
    dc.SetPen( wxPen( wxColour(140,140,140), 1, wxTRANSPARENT ) );
    dc.DrawRectangle( 0, 0, SlidePosition(), GetSize().y );

}


void moWxConnectorObjectCtrl::SetRange( int min, int max ) {
    if ( min >= max ) {
        wxMessageBox(wxT("moWxConnectorObjectCtrl error : min is inferior or equal to max"));
    }

    this->m_min = min;
    this->m_max = max;

}

void moWxConnectorObjectCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;
}

void moWxConnectorObjectCtrl::SetValue( int value ) {

    ChangeValue(value);

    wxCommandEvent event( MO_EVT_DIRECTOR_LEVEL, m_windowId );
    event.SetInt( GetValue() );
    event.SetEventObject( this );
    //ProcessCommand( event );
    ProcessEvent(event );
    //wxMessageBox("Set value: hi event");
}


int moWxConnectorObjectCtrl::GetValue( ) {

    return m_value;

}

//from value to x coord position
int moWxConnectorObjectCtrl::SlidePosition() {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;

    int gsx = GetSize().x;
    if (gsx==0) gsx = 1;

    int slideposition = (( m_value - m_min ) * gsx ) / pWidth;

    return slideposition;
}

//from x coord position to value
int moWxConnectorObjectCtrl::SlideValue( int pointerxposition ) {

    int pWidth = m_max - m_min;
    if (pWidth<=0) pWidth = 1;


    int value = (pointerxposition * pWidth ) / GetSize().x;

    if (value<=0) value = 0;
    if (value>pWidth) value = pWidth;

    value+=m_min;
    return value;
}

void moWxConnectorObjectCtrl::OnMouseEvent( wxMouseEvent & event ) {

    //wxMessageBox("moWxConnectorObjectCtrl::Mouse event");

    if ( event.Entering() ) {
        //SHINE!!!

    }
    if (event.Button(wxMOUSE_BTN_LEFT )) {
        SetValue( SlideValue( event.GetX() ) );
        Refresh();
    }

    if (event.Dragging()) {
        if (m_bStartDragging==false) {
            m_bStartDragging = true;
            wxWindow::CaptureMouse();
        }
        SetValue( SlideValue( event.GetX() ) );
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

void moWxConnectorObjectCtrl::OnCaptureLostEvent( wxMouseCaptureLostEvent& event ) {

    m_bStartDragging = false;

}

void moWxConnectorObjectCtrl::OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event ) {

    m_bStartDragging = false;

}

