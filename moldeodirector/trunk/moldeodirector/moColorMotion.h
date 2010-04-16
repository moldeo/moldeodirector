#ifndef MOCOLORMOTION_H
#define MOCOLORMOTION_H

#include "moIDirectorActions.h"

//(*Headers(moColorMotion)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/statbmp.h>
#include <wx/combobox.h>
//*)

#include "wxMoldeoControls.h"

class moColorMotion: public wxPanel, public moIDirectorActions
{
	public:

		moColorMotion(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moColorMotion();
		void Inspect( moValueDescriptor p_ValueDescriptor );

		//(*Declarations(moColorMotion)
		wxStaticBitmap* StaticBitmap2;
		wxStaticBitmap* StaticBitmap1;
		wxSlider* SliderGreen;
		wxComboBox* ComboBoxMotionColorPresets;
		wxTextCtrl* TextCtrlGreen;
		wxPanel* PanelColor;
		wxSlider* SliderAlpha;
		wxSlider* SliderBlue;
		wxBitmapButton* BitmapButton1;
		wxPanel* Panel3;
		wxTextCtrl* TextCtrlBlue;
		wxTextCtrl* TextCtrlAlpha;
		wxTextCtrl* TextCtrlRed;
		wxPanel* Panel2;
		wxPanel* PanelTranslateCoords;
		wxSlider* SliderRed;
		//*)

		wxMoLevelCtrl* m_pLevelRedCtrl;
		wxMoLevelCtrl* m_pLevelGreenCtrl;
		wxMoLevelCtrl* m_pLevelBlueCtrl;
		wxMoLevelCtrl* m_pLevelAlphaCtrl;

	protected:

		//(*Identifiers(moColorMotion)
		static const long ID_STATICBITMAP1;
		static const long ID_PANEL5;
		static const long ID_SLIDERRED;
		static const long ID_SLIDERGREEN;
		static const long ID_SLIDERBLUE;
		static const long ID_SLIDERALPHA;
		static const long ID_BITMAPBUTTON1;
		static const long ID_PANELCOLOR;
		static const long ID_STATICBITMAP2;
		static const long ID_PANEL3;
		static const long ID_TEXTCTRLRED;
		static const long ID_TEXTCTRLGREEN;
		static const long ID_TEXTCTRLBLUE;
		static const long ID_TEXTCTRLALPHA;
		static const long ID_COMBOBOXCOLORPRESETS;
		static const long ID_PANEL2;
		//*)

        static const long ID_LEVELRED;
		static const long ID_LEVELGREEN;
		static const long ID_LEVELBLUE;
		static const long ID_LEVELALPHA;

	private:

		//(*Handlers(moColorMotion)
		void OnTextCtrlRedText(wxCommandEvent& event);
		void OnTextCtrlGreenText(wxCommandEvent& event);
		void OnTextCtrlBlueText(wxCommandEvent& event);
		void OnTextCtrlAlphaText(wxCommandEvent& event);
		void OnSliderRedCmdScroll(wxScrollEvent& event);
		void OnSliderGreenCmdScroll(wxScrollEvent& event);
		void OnSliderBlueCmdScroll(wxScrollEvent& event);
		void OnSliderAlphaCmdScroll(wxScrollEvent& event);
		void OnButtonPickColorClick(wxCommandEvent& event);
		void OnComboBoxMotionColorPresetsSelect(wxCommandEvent& event);
		//*)

        void OnLevelRed(wxCommandEvent& event);
        void OnLevelGreen(wxCommandEvent& event);
        void OnLevelBlue(wxCommandEvent& event);
        void OnLevelAlpha(wxCommandEvent& event);

        void OnMouseEvent( wxMouseEvent& event );

        moValueDescriptor   m_ValueDescriptor;

		DECLARE_EVENT_TABLE()
};

#endif
