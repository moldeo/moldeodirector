#ifndef MOCONFIGURATIONADVANCEDOUTPUT_H
#define MOCONFIGURATIONADVANCEDOUTPUT_H


#include "moIDirectorActions.h"

//(*Headers(moConfigurationAdvancedOutput)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

class moConfigurationAdvancedOutput: public wxFrame
{
	public:

		moConfigurationAdvancedOutput(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moConfigurationAdvancedOutput();

		//(*Declarations(moConfigurationAdvancedOutput)
		wxChoice* Display1;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxChoice* Choice3;
		wxButton* Button1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* Button2;
		wxPanel* Panel3;
		wxChoice* Choice4;
		wxPanel* Panel2;
		wxStaticText* StaticText4;
		wxChoice* Choice1;
		wxChoice* Choice2;
		//*)

	protected:

		//(*Identifiers(moConfigurationAdvancedOutput)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_CHOICE5;
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE2;
		static const long ID_CHOICE4;
		static const long ID_CHOICE3;
		static const long ID_PANEL4;
		//*)

	private:

		//(*Handlers(moConfigurationAdvancedOutput)
		void OnPanel2Paint(wxPaintEvent& event);
		void OnPanel1Paint(wxPaintEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
