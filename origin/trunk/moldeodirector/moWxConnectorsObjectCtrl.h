#ifndef MOWXCONNECTORSOBJECTCTRL_H
#define MOWXCONNECTORSOBJECTCTRL_H

#include "moDirectorTypes.h"

#define MO_EVT_DIRECTOR_LEVEL 5970

class moWxConnectorObjectCtrl : public wxControl {

    public:
        moWxConnectorObjectCtrl( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~moWxConnectorObjectCtrl();


        void SetRange( int min, int max );
        void SetValue( int value );
        void ChangeValue( int value );
        int GetValue();
        int SlidePosition();
        int SlideValue( int pointerxposition );


    private:

        int m_min;
        int m_max;
        int m_value;

        bool m_bStartDragging;

    protected:
        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );

        DECLARE_EVENT_TABLE()

};


#endif
