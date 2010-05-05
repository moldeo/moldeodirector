#ifndef WXMOROTARYCTRL_H
#define WXMOROTARYCTRL_H


#ifdef WXMAKINGDLL_MOROTARYCTRL
    #define WXDLLIMPEXP_MOROTARYCTRL WXEXPORT
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_MOROTARYCTRL WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_MOROTARYCTRL
#endif


class wxMoRotaryCtrl : public wxControl {

    public:
        static const float PI;
        static const float PI2;

        wxMoRotaryCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxPanelNameStr );
        virtual ~wxMoRotaryCtrl();


        void SetRange( int min, int max );
        void SetRangeAngle( float angmin, float angmax );
        void SetValue( int value );
        void ChangeValue( int value );
        int GetValue();

        float SlideAngle();

        ///Mouse pointer position to value (min,max)
        /**
            Mouse is converted to an angle in radians corresponding to a base line between the pointer and
            the center of the control
            @return value between m_min and m_max
        */
        int SlideValue( int pointerx, int pointery );

        ///Mouse pointer position to value (min,max)
        /**
        */
        float AngleValue( int pointerx, int pointery );

        float ValueToAngle( int val );
        int AngleToValue( float angle );

    private:

        float m_angmin;
        float m_angmax;

        int m_min;
        int m_max;
        int m_value;

        float AngleClickPosition;
        float AngleValueWhenClicked;

        bool m_bStartDragging;

    protected:
        void OnPaint(wxPaintEvent& event);
        void OnMouseEvent( wxMouseEvent & event );
        void OnCaptureLostEvent( wxMouseCaptureLostEvent& event );
        void OnCaptureChangedEvent( wxMouseCaptureChangedEvent& event );
        void OnEraseBackground(wxEraseEvent& event);
        void OnKillFocus( wxFocusEvent& event);

        DECLARE_EVENT_TABLE()

};

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_MOROTARYCTRL, wxEVT_MOROTARYCTRL, 7777)
END_DECLARE_EVENT_TYPES()

#endif
