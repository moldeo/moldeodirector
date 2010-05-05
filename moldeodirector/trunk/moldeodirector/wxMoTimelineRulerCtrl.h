#ifndef WXMOTIMELINERULERCTRL_H
#define WXMOTIMELINERULERCTRL_H


#ifdef WXMAKINGDLL_MOTIMELINERULERCTRL
    #define WXDLLIMPEXP_MOTIMELINERULERCTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOTIMELINERULERCTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOTIMELINERULERCTRL
#endif

#include "wx/timer.h"

class wxMoTimelineRulerCtrl : public wxControl {

    public:
        wxMoTimelineRulerCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~wxMoTimelineRulerCtrl();


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
        wxTimer m_timer;

    protected:

        static const long TIMELINETIMER_ID;

        void OnTimer(wxTimerEvent &event);

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );

        DECLARE_EVENT_TABLE()

};

DECLARE_EVENT_TYPE( wxEVT_MO_TIMELINEBAND, 8888 )


#endif
