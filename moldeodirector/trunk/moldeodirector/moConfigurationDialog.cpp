#include "moConfigurationDialog.h"

//(*InternalHeaders(moConfigurationDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moConfigurationDialog)
const long moConfigurationDialog::ID_TREEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moConfigurationDialog,wxDialog)
	//(*EventTable(moConfigurationDialog)
	//*)
END_EVENT_TABLE()

moConfigurationDialog::moConfigurationDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(moConfigurationDialog)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Moldeo Director Configuration"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX, _T("id"));
	SetClientSize(wxSize(263,232));
	FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	Treebook1 = new wxNotebook(this, ID_TREEBOOK1, wxDefaultPosition, wxSize(372,312), 0, _T("ID_TREEBOOK1"));
	FlexGridSizer1->Add(Treebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	//*)

    m_pConfigurationOutput = new moConfigurationOutput(this);
    m_pConfigurationGeneral = new moConfigurationGeneral(this);

    Treebook1->AddPage( m_pConfigurationGeneral, wxString(_T("General")) );
    Treebook1->AddPage( m_pConfigurationOutput, wxString(_T("Output")) );

}

moConfigurationDialog::~moConfigurationDialog()
{
	//(*Destroy(moConfigurationDialog)
	//*)
}

