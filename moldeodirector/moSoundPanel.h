#ifndef MOSOUNDPANEL_H
#define MOSOUNDPANEL_H

//(*Headers(moSoundPanel)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include <moIDirectorActions.h>

class moSoundPanel: public wxPanel, public moIDirectorActions
{
	public:

		moSoundPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moSoundPanel();
		void Inspect( moValueDescriptor p_ValueDescriptor );

		//(*Declarations(moSoundPanel)
		wxButton* ButtonImport;
		wxTextCtrl* TextCtrlSound;
		wxStaticText* m_pTextDetails;
		//*)


	protected:
    moValueDescriptor   m_ValueDescriptor;

		//(*Identifiers(moSoundPanel)
		static const long ID_TEXTCTRLSOUND;
		static const long ID_STATICTEXTDETAILS;
		static const long ID_BUTTONIMPORT;
		//*)

	private:

		//(*Handlers(moSoundPanel)
		void OnButtonImportClick(wxCommandEvent& event);
		void OnTextCtrlSoundText(wxCommandEvent& event);
		void OnButtonImportClick1(wxCommandEvent& event);
		//*)

    void LoadSound();


		DECLARE_EVENT_TABLE()
};

#endif

