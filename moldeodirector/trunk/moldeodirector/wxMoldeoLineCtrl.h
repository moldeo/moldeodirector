#ifndef WXMOLDEOLINECTRL_H
#define WXMOLDEOLINECTRL_H


#ifdef WXMAKINGDLL_MOLDEOLINECTRL
    #define WXDLLIMPEXP_MOLDEOLINECTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOLDEOLINECTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOLDEOLINECTRL
#endif

#include "wx/timer.h"
#include "wx/bitmap.h"

class wxMoldeoLineCtrl : public wxControl {

    public:
        wxMoldeoLineCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~wxMoldeoLineCtrl();


        void SetRange( int min, int max );
        void SetValue( int value );
        void ChangeValue( int value );
        int GetValue();
        int SlidePosition();
        int SlideValue( int pointerxposition );


        int PlayValueToSlidePosition( int value_ms );

        /***

        TIMELINE SPECIFIC

        */
        void SetMaxPlayValue( int value );
        void SetPlayValue( int value );

        int GetMaxPlayValue();
        int GetPlayValueToSlideValue( int playvalue );
        int GetSlideValueToPlayValue( int slidevalue );
        int GetPlayValue();

        void SetPixelInterval( int pixelinterval );///miliseconds per pixel
        int GetPixelInterval();///get miliseconds per pixel

        void SetPlayIn( int value );
        int GetPlayIn();

        void SetPlayOut( int value );
        int GetPlayOut();

        void SetRenderIn( int value );
        int GetRenderIn();

        void SetRenderOut( int value );
        int GetRenderOut();

    private:

        int m_min;
        int m_max;
        int m_value;

        int m_play_value;
        int m_max_play_value;
        int m_pixel_interval;


        int m_play_in;
        int m_play_out;

        int m_render_in;
        int m_render_out;

        bool m_bStartDragging;
        bool m_bLeftSizeDragging;
        bool m_bRightSizeDragging;
        bool m_bMovingDragging;

        int Mx;
        int My;

        int Px;
        int Py;

        wxTimer m_timer;

        wxList    m_ConnectedPins;

        wxBitmap   bitmap;

    protected:

        static const long MOLDEOLINETIMER_ID;

        void OnTimer(wxTimerEvent &event);

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );

        DECLARE_EVENT_TABLE()

};


DECLARE_EVENT_TYPE( wxEVT_MOLDEOLINE, 8888 )
DECLARE_EVENT_TYPE( wxEVT_MOLDEOLINE_BEGINDRAGLEFT, 8888 )
DECLARE_EVENT_TYPE( wxEVT_MOLDEOLINE_DRAGLEFT, 8888)
DECLARE_EVENT_TYPE( wxEVT_MOLDEOLINE_ENDDRAGLEFT, 8888)

#endif
