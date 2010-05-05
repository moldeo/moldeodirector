#ifndef WXMOLEVELCTRL_H
#define WXMOLEVELCTRL_H

#ifdef WXMAKINGDLL_MOLEVELCTRL
    #define WXDLLIMPEXP_MOLEVELCTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOLEVELCTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOLEVELCTRL
#endif

#include <wx/control.h>

class wxMoLevelCtrl : public wxControl {

    public:
        wxMoLevelCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~wxMoLevelCtrl();


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
        int Px,Mx,Sx,Vx;

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );
        void OnKillFocus( wxFocusEvent& event);

        DECLARE_EVENT_TABLE()
};

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_MOLEVELCTRL, wxEVT_MOLEVELCTRL, 7777)
END_DECLARE_EVENT_TYPES()

#endif
