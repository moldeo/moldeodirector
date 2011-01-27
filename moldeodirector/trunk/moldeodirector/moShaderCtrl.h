#ifndef MOSHADERCTRL_H
#define MOSHADERCTRL_H

#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

//(*Headers(moShaderCtrl)
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

class moShaderCtrl: public wxPanel, public moIDirectorActions
{
	public:

		moShaderCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moShaderCtrl();

		//(*Declarations(moShaderCtrl)
		wxBitmapButton* BitmapButtonShaderImport;
		wxCheckBox* CheckBoxOnOff;
		wxSlider* SliderShaderAlpha;
		wxBitmapButton* BitmapButtonShaderSelect;
		wxTextCtrl* TextCtrlDestination;
		wxTextCtrl* TextCtrlShaderCfg;
		//*)

		void Inspect( moValueDescriptor p_ValueDescriptor );

	protected:

		//(*Identifiers(moShaderCtrl)
		static const long ID_TEXTCTRLSHADERCFG;
		static const long ID_TEXTCTRLDESTINATION;
		static const long ID_CHECKBOXSHADERONOFF;
		static const long ID_BITMAPBUTTONSHADERSELECT;
		static const long ID_BITMAPBUTTONSHADERIMPORT;
		static const long ID_SLIDERSHADERALPHA;
		//*)
		static const long ID_LEVELSHADERALPHA;


	private:

		//(*Handlers(moShaderCtrl)
		void OnTextCtrlShaderCfgText(wxCommandEvent& event);
		void OnTextCtrlDestinationText(wxCommandEvent& event);
		void OnBitmapButtonShaderImportClick(wxCommandEvent& event);
		void OnBitmapButtonShaderSelectClick(wxCommandEvent& event);
		void OnCheckBoxOnOffClick(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

		void OnLevelShaderAlpha( wxCommandEvent& event );

		void ProcessShaderValues();

        moValueDescriptor   m_ValueDescriptor;
        wxMoLevelCtrl*      m_pLevelShaderAlphaCtrl;

		DECLARE_EVENT_TABLE()
};

#endif
