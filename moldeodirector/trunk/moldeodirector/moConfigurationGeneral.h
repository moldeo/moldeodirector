#ifndef MOCONFIGURATIONGENERAL_H
#define MOCONFIGURATIONGENERAL_H

//(*Headers(moConfigurationGeneral)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
//*)

class moConfigurationGeneral: public wxPanel
{
	public:

		moConfigurationGeneral(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moConfigurationGeneral();

		//(*Declarations(moConfigurationGeneral)
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrl2;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(moConfigurationGeneral)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		//*)

	private:

		//(*Handlers(moConfigurationGeneral)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
