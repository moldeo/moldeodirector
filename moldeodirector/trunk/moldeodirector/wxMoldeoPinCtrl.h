#ifndef WXMOLDEOPINCTRL_H
#define WXMOLDEOPINCTRL_H


#ifdef WXMAKINGDLL_MOLDEOPINCTRL
    #define WXDLLIMPEXP_MOLDEOPINCTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOLDEOPINCTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOLDEOPINCTRL
#endif

#include "wx/timer.h"
#include "wx/dnd.h"

class wxPinDropTarget : public wxTextDropTarget {

  public:

        wxPinDropTarget() {}
        virtual ~wxPinDropTarget(){}


        virtual bool OnDropText(wxCoord, wxCoord, const wxString&);



};

class wxMoldeoPinCtrl : public wxControl, public wxTextDataObject {

    public:
        wxMoldeoPinCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~wxMoldeoPinCtrl();


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

    protected:

        static const long MOLDEOPINTIMER_ID;

        void OnTimer(wxTimerEvent &event);

        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );

        void OnEnter(wxCoord x, wxCoord y, wxDragResult def);
        void OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
        void OnDrop(wxCoord x, wxCoord y, wxDragResult def);

        DECLARE_EVENT_TABLE()

};


DECLARE_EVENT_TYPE( wxEVT_MOLDEOPIN, 8888 )
DECLARE_EVENT_TYPE( wxEVT_MOLDEOPIN_BEGINDRAGLEFT, 8888 )
DECLARE_EVENT_TYPE( wxEVT_MOLDEOPIN_DRAGLEFT, 8888)
DECLARE_EVENT_TYPE( wxEVT_MOLDEOPIN_ENDDRAGLEFT, 8888)

#endif
