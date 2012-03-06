#ifndef MOFUNCTIONPANEL_H
#define MOFUNCTIONPANEL_H

#include "moDirectorTypes.h"

//(*Headers(moFunctionPanel)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
//*)

#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

class moFunctionPanel: public wxPanel, public moIDirectorActions
{
	public:

		moFunctionPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moFunctionPanel();
		void Inspect( moValueDescriptor p_ValueDescriptor );

		//(*Declarations(moFunctionPanel)
		wxButton* ButtonCosSin;
		wxButton* ButtonLog;
		wxButton* ButtonSin;
		wxStaticBitmap* StaticBitmap1;
		wxMoLevelCtrl* SliderNumber;
		wxButton* ButtonExp;
		wxPanel* Panel1;
		wxTextCtrl* TextCtrlMin;
		wxStaticText* StaticText1;
		wxTextCtrl* FunctionTextCtrl;
		wxTextCtrl* TextCtrlMax;
		wxButton* ButtonTan;
		wxButton* Button1x;
		wxPanel* PanelPlot2d;
		wxButton* ButtonSqrt;
		wxButton* ButtonCos;
		wxButton* ButtonSqr;
		//*)

	protected:

		//(*Identifiers(moFunctionPanel)
		static const long ID_FUNCTIONTEXTCTRL;
		static const long ID_STATICBITMAP1;
		static const long ID_PANELPLOT2D;
		static const long ID_STATICTEXT1;
		static const long ID_SLIDERNUMBER;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRLMAX;
		static const long ID_BUTTON5;
		static const long ID_BUTTON1;
		static const long ID_BUTTON4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON7;
		static const long ID_BUTTON3;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_BUTTON6;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(moFunctionPanel)
		void OnFunctionTextCtrlText(wxCommandEvent& event);
		//*)

        void OnLevelNumber(wxCommandEvent& event);


        moValueDescriptor m_ValueDescriptor;

		DECLARE_EVENT_TABLE()
};

#endif
