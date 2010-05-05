#ifndef WXMOLDEOOBJECTCANVAS_H
#define WXMOLDEOOBJECTCANVAS_H


#ifdef WXMAKINGDLL_MOLDEOOBJECTCANVAS
    #define WXDLLIMPEXP_MOLDEOOBJECTCANVAS WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOLDEOOBJECTCANVAS WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOLDEOOBJECTCANVAS
#endif

#include "wx/timer.h"
#include "wx/scrolwin.h"

#include "wxMoldeoLineCtrl.h"
class wxMoldeoObjectCanvas : public wxScrolledWindow {

    public:
        wxMoldeoObjectCanvas( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = wxPanelNameStr );
        virtual ~wxMoldeoObjectCanvas();

    private:

        bool m_bStartDragging;
        bool m_bLeftSizeDragging;
        bool m_bRightSizeDragging;
        bool m_bMovingDragging;

        bool m_bLineDrawing;

        int Mx;
        int My;

        int Px;
        int Py;

        int LineStartX;
        int LineStartY;

        int LineEndX;
        int LineEndY;

        wxTimer m_timer;

        wxMoldeoLineCtrl* pDrawingLine;

    protected:

        static const long TIMELINETIMER_ID;

        void OnTimer(wxTimerEvent &event);

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );
        //void OnEraseBackground(wxEraseEvent& event);


        void OnPinBeginDragLeft( wxCommandEvent& event );
        void OnPinDragLeft( wxCommandEvent& event );
        void OnPinEndDragLeft( wxCommandEvent& event );

        DECLARE_EVENT_TABLE()

};


DECLARE_EVENT_TYPE( wxEVT_MO_TIMELINERULER, 8888 )

#endif
