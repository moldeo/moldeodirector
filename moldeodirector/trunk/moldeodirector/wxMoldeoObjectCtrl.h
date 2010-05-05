#ifndef WXMOLDEOOBJECTCTRL_H
#define WXMOLDEOOBJECTCTRL_H


#ifdef WXMAKINGDLL_MOLDEOOBJECTCTRL
    #define WXDLLIMPEXP_MOLDEOOBJECTCTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOLDEOOBJECTCTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOLDEOOBJECTCTRL
#endif

#include <wx/timer.h>
#include <wx/panel.h>

class wxMoldeoObjectCtrl : public wxPanel {

    public:
        wxMoldeoObjectCtrl( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr );
        virtual ~wxMoldeoObjectCtrl();


    private:


        bool m_bStartDragging;
        bool m_bLeftSizeDragging;
        bool m_bRightSizeDragging;
        bool m_bMovingDragging;

        int Mx;
        int My;

        int Px;
        int Py;

        wxTimer m_timer;

    protected:

        static const long TIMELINETIMER_ID;

        void OnTimer(wxTimerEvent &event);

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );
        void OnEraseBackground(wxEraseEvent& event);

    public:

        DECLARE_EVENT_TABLE()

};


DECLARE_EVENT_TYPE( wxEVT_MO_TIMELINERULER, 8888 )

#endif
