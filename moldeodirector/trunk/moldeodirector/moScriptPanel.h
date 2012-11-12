#ifndef MOSCRIPTPANEL_H
#define MOSCRIPTPANEL_H

#include "moIDirectorActions.h"

//(*Headers(moScriptPanel)
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "wxMoldeoControls.h"

class moScriptPanel: public wxPanel, public moIDirectorActions
{
	public:

		moScriptPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~moScriptPanel();
		void Inspect( moValueDescriptor p_ValueDescriptor );


		//(*Declarations(moScriptPanel)
		wxButton* BrowseScript;
		wxButton* CompileButton;
		wxTextCtrl* ScriptFileTextCtrl;
		wxTextCtrl* ScriptTextCtrl;
		wxButton* SaveButton;
		//*)

	protected:

		//(*Identifiers(moScriptPanel)
		static const long ID_COMPILEANDRUN;
		static const long ID_SCRIPTEXTCTRL;
		static const long ID_FILETEXTCTRL;
		static const long ID_BROWSESCRIPT;
		static const long ID_SAVEBUTTON;
		//*)

	private:

        moValueDescriptor   m_ValueDescriptor;

		//(*Handlers(moScriptPanel)
		void OnButton1Click(wxCommandEvent& event);
		void OnCompileButtonClick(wxCommandEvent& event);
		void OnBrowseScriptClick(wxCommandEvent& event);
		void OnScriptFileTextCtrlText(wxCommandEvent& event);
		void OnSaveButtonClick(wxCommandEvent& event);
		//*)

    bool Save();


		DECLARE_EVENT_TABLE()
};

#endif

