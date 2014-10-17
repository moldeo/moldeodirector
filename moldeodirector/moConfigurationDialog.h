#ifndef MOCONFIGURATIONDIALOG_H
#define MOCONFIGURATIONDIALOG_H

#include "moIDirectorActions.h"

//(*Headers(moConfigurationDialog)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
//*)

#include <wx/treebook.h>

#include "moConfigurationOutput.h"
#include "moConfigurationGeneral.h"

class moConfigurationDialog: public wxDialog
{
	public:

		moConfigurationDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~moConfigurationDialog();

		//(*Declarations(moConfigurationDialog)
		wxNotebook* Treebook1;
		//*)

	protected:

		//(*Identifiers(moConfigurationDialog)
		static const long ID_TREEBOOK1;
		//*)

	private:

		//(*Handlers(moConfigurationDialog)
		//*)

        moConfigurationOutput*  m_pConfigurationOutput;
        moConfigurationGeneral*  m_pConfigurationGeneral;


		DECLARE_EVENT_TABLE()
};

#endif

