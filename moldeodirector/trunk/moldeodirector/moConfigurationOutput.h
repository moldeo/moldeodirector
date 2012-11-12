#ifndef MOCONFIGURATIONOUTPUT_H
#define MOCONFIGURATIONOUTPUT_H

#include "moIDirectorActions.h"

//(*Headers(moConfigurationOutput)
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "moConfigurationAdvancedOutput.h"


class moConfigurationOutput: public wxPanel
{
	public:

		moConfigurationOutput(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moConfigurationOutput();

		//(*Declarations(moConfigurationOutput)
		wxButton* ButtonAdvancedOutput;
		wxSpinCtrl* SpinCtrl1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxSpinCtrl* SpinCtrl2;
		wxComboBox* ComboBox1;
		wxComboBox* ComboBox2;
		//*)

        moConfigurationAdvancedOutput* m_pAdvancedOutput;

	protected:

		//(*Identifiers(moConfigurationOutput)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICBOX2;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(moConfigurationOutput)
		void OnButtonAdvancedOutputClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

