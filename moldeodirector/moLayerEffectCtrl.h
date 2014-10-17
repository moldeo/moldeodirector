#ifndef MOLAYEREFFECTCTRL_H
#define MOLAYEREFFECTCTRL_H

#include "moDirectorTypes.h"

//(*Headers(moLayerEffectCtrl)
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

/**
*
*/

class moItemLayerCtrl : public moIDirectorActions {

    public:

        moItemLayerCtrl() : moIDirectorActions() {}
        virtual ~moItemLayerCtrl() {}

        virtual void Inspect( moMobDescriptor   p_MobDescriptor ) = 0;
        virtual moMobDescriptor& Get();

    protected:
        moMobDescriptor m_MobDescriptor;

        //void OnMouseEvent( wxMouseEvent& event );

        //DECLARE_EVENT_TABLE()
};

class moLayerEffectCtrl: public wxPanel, public moItemLayerCtrl
{
	public:

		moLayerEffectCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moLayerEffectCtrl();

		void Inspect( moMobDescriptor p_MobDescriptor );


		//(*Declarations(moLayerEffectCtrl)
		wxMoColourPanel* ColourPanel;
		wxMoColourPanel* ColourPanelFinal;
		wxMoRotaryCtrl* m_pLevelSpeedCtrl;
		wxCheckBox* CheckBoxOnOff;
		wxBitmapButton* BitmapButtonView;
		wxMoColourLevelCtrl* m_pLevelAlphaCtrl;
		wxBitmapButton* BitmapButtonPlay;
		wxTextCtrl* TextCtrlLabel;
		wxBitmapButton* BitmapButtonStop;
		wxMoColourLevelCtrl* SliderHue;
		wxBitmapButton* BitmapButtonPause;
		wxTextCtrl* TextCtrlTimecode;
		wxMoColourLevelCtrl* m_pLevelTintCtrl;
		wxMoColourLevelCtrl* SliderSaturation;
		//*)

    public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    ParameterUpdated( moParameterDescriptor p_ParameterDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    SetMob( moMobDescriptor p_MobDesc );

	protected:

		//(*Identifiers(moLayerEffectCtrl)
		static const long ID_TEXTCTRL_LABEL;
		static const long ID_TEXTCTRL_TIMECODE;
		static const long ID_SLIDERHUE;
		static const long ID_SLIDERSATURATION;
		static const long ID_SLIDERALPHA;
		static const long ID_SLIDERTINT;
		static const long ID_SLIDERTEMPO;
		static const long ID_CHECKBOXONOFF;
		static const long ID_BITMAPBUTTONVIEW;
		static const long ID_COLOURPANELFINAL;
		static const long ID_COLOURPANEL;
		static const long ID_BITMAPBUTTON_FXPLAY;
		static const long ID_BITMAPBUTTON_FXSTOP;
		static const long ID_BITMAPBUTTON_FXPAUSE;
		//*)

		static const long ID_LEVELALPHA;
		static const long ID_LEVELTINT;
		static const long ID_LEVELSPEED;

	private:

		//(*Handlers(moLayerEffectCtrl)
		void OnOnOffButtonToggle(wxCommandEvent& event);
		void OnCheckBoxOnOffClick(wxCommandEvent& event);
		void OnComboBoxPreConfigSelect(wxCommandEvent& event);
		void OnPanelVisibilityMouseMove(wxMouseEvent& event);
		void OnBitmapButtonVisibilityClick(wxCommandEvent& event);
		void OnBitmapButtonDeleteClick(wxCommandEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnBitmapButtonPlay(wxCommandEvent& event);
		void OnBitmapButtonPauseClick(wxCommandEvent& event);
		void OnBitmapButtonStopClick(wxCommandEvent& event);
		//*)

		void OnLevelAlpha(wxCommandEvent& event);
		void OnLevelTint(wxCommandEvent& event);
		void OnLevelHue(wxCommandEvent& event);
		void OnLevelSaturation(wxCommandEvent& event);

		void OnLevelSpeed(wxCommandEvent& event);

    void OnMouseEvent( wxMouseEvent& event );

    void Update( const moEffectState& effect_state );

    wxBitmap  m_BitmapViewOn;
    wxBitmap  m_BitmapViewOff;

    moValueDescriptor m_TexValueDescriptor;
    moTextureDescriptor m_TextureDescriptor;

		DECLARE_EVENT_TABLE()
};


class moEffectLayerTimelineCtrl : public moItemLayerCtrl, public wxPanel {

    public:
		moEffectLayerTimelineCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moEffectLayerTimelineCtrl();
		void Inspect( moMobDescriptor p_MobDescriptor );

   public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );

    protected:

        wxImage    m_BackgroundImage;
        moText     m_BackgroundName;


        void OnPaint( wxPaintEvent& event );
        void OnMouseEvent( wxMouseEvent& event );


		DECLARE_EVENT_TABLE()
};

//template class moDynamicArray<moLayerEffectCtrl*>;
//typedef  moDynamicArray<moLayerEffectCtrl*> moLayerEffectCtrls;



class moItemLayerWindow: public moItemLayerCtrl, public wxPanel
{
	public:

		moItemLayerWindow(wxWindow *parent, wxWindowID id,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxNO_BORDER,
                        const wxString& name = _("LayerPanel") );
		virtual ~moItemLayerWindow() {
        }

        moLayerEffectCtrl*  m_pFXControllers;

        wxPanel*            m_pFXControllersContainer;
        wxPanel*            m_pFXSelectors;

        wxWindow*   m_pWindow;
        moEffectLayerTimelineCtrl* m_pTimeline;


        virtual void Inspect( moMobDescriptor p_MobDesc );

    public:
        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    ParameterUpdated( moParameterDescriptor p_ParameterDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    SetMob( moMobDescriptor p_MobDesc );

        void    SetScrollPosition( int position );



    DECLARE_EVENT_TABLE()
};


#endif

