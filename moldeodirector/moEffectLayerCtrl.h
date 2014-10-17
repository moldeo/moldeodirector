#ifndef MOEFFECTLAYERCTRL_H
#define MOEFFECTLAYERCTRL_H

#include "moDirectorTypes.h"

//(*Headers(moEffectLayerCtrl)
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/splitter.h>
#include <wx/timer.h>
#include <wx/image.h>
//*)

#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

class moItemLayerCtrl : public moIDirectorActions {

    public:

        moItemLayerCtrl() {}
        virtual ~moItemLayerCtrl() {}

        virtual void Set( moMobDescriptor   p_MobDescriptor );
        virtual moMobDescriptor& Get();

    public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc ) = 0;
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc ) = 0;

    protected:
        moMobDescriptor m_MobDescriptor;

        //void OnMouseEvent( wxMouseEvent& event );

        //DECLARE_EVENT_TABLE()
};

class moEffectLayerCtrl: public wxPanel, public moItemLayerCtrl
{
	public:

		moEffectLayerCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moEffectLayerCtrl();

		virtual void Set( moMobDescriptor p_MobDesc );

		//(*Declarations(moEffectLayerCtrl)
		wxCheckBox* CheckBoxOnOff;
		wxMoLevelCtrl* m_pLevelAlphaCtrl;
		wxTextCtrl* TextCtrlLabel;
		wxMoLevelCtrl* m_pLevelSpeedCtrl;
		wxMoLevelCtrl* m_pLevelTintCtrl;
		wxBitmapButton* BitmapButtonDelete;
		//*)

		//moWxLevelCtrl* m_pLevelAlphaCtrl;
		//moWxLevelCtrl* m_pLevelTintCtrl;
		//moWxLevelCtrl* m_pLevelSpeedCtrl;

    public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );

	protected:

		//(*Identifiers(moEffectLayerCtrl)
		static const long ID_TEXTCTRL1;
		static const long ID_SLIDERALPHA;
		static const long ID_SLIDERTINT;
		static const long ID_SLIDERTEMPO;
		static const long ID_CHECKBOXONOFF;
		static const long ID_BITMAPBUTTONDELETE;
		//*)

		static const long ID_LEVELALPHA;
		static const long ID_LEVELTINT;
		static const long ID_LEVELSPEED;

	private:

		//(*Handlers(moEffectLayerCtrl)
		void OnOnOffButtonToggle(wxCommandEvent& event);
		void OnCheckBoxOnOffClick(wxCommandEvent& event);
		void OnComboBoxPreConfigSelect(wxCommandEvent& event);
		void OnPanelVisibilityMouseMove(wxMouseEvent& event);
		void OnBitmapButtonVisibilityClick(wxCommandEvent& event);
		void OnBitmapButtonDeleteClick(wxCommandEvent& event);
		void OnPaint(wxPaintEvent& event);
		//*)

		void OnLevelAlpha(wxCommandEvent& event);
		void OnLevelTint(wxCommandEvent& event);
		void OnLevelSpeed(wxCommandEvent& event);

        void OnMouseEvent( wxMouseEvent& event );

		DECLARE_EVENT_TABLE()
};


class moEffectLayerTimelineCtrl : public moItemLayerCtrl, public wxPanel {

    public:
		moEffectLayerTimelineCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moEffectLayerTimelineCtrl();

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

//template class moDynamicArray<moEffectLayerCtrl*>;
//typedef  moDynamicArray<moEffectLayerCtrl*> moEffectLayerCtrls;



class moItemLayerWindow: public moItemLayerCtrl, public wxSplitterWindow
{
	public:

		moItemLayerWindow(wxWindow *parent, wxWindowID id,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxNO_BORDER,
                        const wxString& name = _("LayerPanel") );
		virtual ~moItemLayerWindow() {
        }

        moEffectLayerCtrl*  m_pFXControllers;

        wxPanel*            m_pFXControllersContainer;
        wxPanel*            m_pFXSelectors;

        wxWindow*   m_pWindow;
        moEffectLayerTimelineCtrl* m_pTimeline;


        virtual void Set( moMobDescriptor p_MobDesc );

        moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );

        void    SetScrollPosition( int position );


    DECLARE_EVENT_TABLE()
};


#endif
