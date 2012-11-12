#ifndef MOCOLORMOTION_H
#define MOCOLORMOTION_H

#include "moIDirectorActions.h"

//(*Headers(moColorMotion)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
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
		wxStaticText* StaticText10;
		wxMoColourPanel* ColourPanel;
		wxStaticText* StaticText9;
		wxTextCtrl* TextHtmlColourCtrl;
		wxStaticText* StaticText2;
		wxMoColourLevelCtrl* SliderGreen;
		wxBitmapButton* BitmapButtonPickColor;
		wxStaticText* StaticText6;
		wxComboBox* ComboBoxMotionColorPresets;
		wxTextCtrl* TextCtrlGreen;
		wxMoColourLevelCtrl* SliderValue;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxMoColourLevelCtrl* SliderHue;
		wxTextCtrl* TextCtrlBlue;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxTextCtrl* TextCtrlAlpha;
		wxTextCtrl* TextCtrlRed;
		wxMoColourLevelCtrl* SliderRed;
		wxPanel* Panel2;
		wxMoColourLevelCtrl* SliderBlue;
		wxStaticText* StaticText4;
		wxMoColourLevelCtrl* SliderAlpha;
		wxMoColourLevelCtrl* SliderSaturation;
		//*)

	protected:

		//(*Identifiers(moColorMotion)
		static const long ID_SLIDERVALUE;
		static const long ID_SLIDERSATURATION;
		static const long ID_SLIDERHUE;
		static const long ID_SLIDERRED;
		static const long ID_SLIDERGREEN;
		static const long ID_SLIDERBLUE;
		static const long ID_SLIDERALPHA;
		static const long ID_BITMAPBUTTONPICKCOLOR;
		static const long ID_PANELCOLOR;
		static const long ID_TEXTCTRLRED;
		static const long ID_TEXTCTRLGREEN;
		static const long ID_TEXTCTRLBLUE;
		static const long ID_TEXTHTMLCOLOURCTRL;
		static const long ID_TEXTCTRLALPHA;
		static const long ID_COMBOBOXCOLORPRESETS;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT1;
		static const long ID_PANEL2;
		//*)

	private:

		//(*Handlers(moColorMotion)
		void OnTextCtrlRedText(wxCommandEvent& event);
		void OnTextCtrlGreenText(wxCommandEvent& event);
		void OnTextCtrlBlueText(wxCommandEvent& event);
		void OnTextCtrlAlphaText(wxCommandEvent& event);
		void OnButtonPickColorClick(wxCommandEvent& event);
		void OnComboBoxMotionColorPresetsSelect(wxCommandEvent& event);
		void OnTextHtmlColourCtrlText(wxCommandEvent& event);
		//*)

    void OnLevelRed(wxCommandEvent& event);
    void OnLevelGreen(wxCommandEvent& event);
    void OnLevelBlue(wxCommandEvent& event);
    void OnLevelAlpha(wxCommandEvent& event);
    void OnLevelHue(wxCommandEvent& event);
    void OnLevelSaturation(wxCommandEvent& event);
    void OnLevelValue(wxCommandEvent& event);

    void OnMouseEvent( wxMouseEvent& event );

    /**
    * Actualiza el color a partir de un dato único de color
    * en el format (r,g,b) (0..255,0.255,0..255)
    */
    void UpdateColour( wxColour pColour );

    /**
    * Actualiza el color a partir de la expresión de cada color como texto
    * este texto luego será interpretado por libmoldeo como función
    */
    void UpdateColour( moText red, moText green, moText blue, moText alpha );

    moValueDescriptor   m_ValueDescriptor;
    wxColour            m_ActualColour;

		DECLARE_EVENT_TABLE()
};

#endif

