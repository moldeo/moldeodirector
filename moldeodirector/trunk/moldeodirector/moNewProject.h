#ifndef MONEWPROJECT_H
#define MONEWPROJECT_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

//(*Headers(moNewProject)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class moNewProject: public wxDialog
{
	public:

		moNewProject(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~moNewProject();
		const moProjectDescriptor& GetProjectDescriptor() {
            return m_ProjectDescriptor;
        }

		//(*Declarations(moNewProject)
		wxTextCtrl* DirTextCtrl;
		wxStaticText* StaticText2;
		wxButton* ButtonBrowse;
		wxStaticText* StaticText1;
		wxButton* OkButton;
		wxTextCtrl* ProjectNameTextCtrl;
		wxButton* CancelButton;
		//*)

	protected:

		//(*Identifiers(moNewProject)
		static const long ID_DIRTEXTCTRL;
		static const long ID_STATICTEXT1;
		static const long ID_NEWPROJECT_BROWSE;
		static const long ID_STATICTEXT2;
		static const long ID_NAMETEXTCTRL;
		static const long ID_NEWPROJECT_OK;
		static const long ID_NEWPROJECT_CANCEL;
		//*)

	private:

		//(*Handlers(moNewProject)
		void OnOkClick(wxCommandEvent& event);
		void OnCancelClick(wxCommandEvent& event);
		void OnBrowseClick(wxCommandEvent& event);
		void OnDirTextCtrlText(wxCommandEvent& event);
		void OnProjectNameTextCtrlText(wxCommandEvent& event);
		//*)

        moProjectDescriptor m_ProjectDescriptor;

		DECLARE_EVENT_TABLE()
};

#endif
