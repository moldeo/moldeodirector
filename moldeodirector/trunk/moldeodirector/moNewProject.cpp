#include "moNewProject.h"

#include <wx/dirdlg.h>

//(*InternalHeaders(moNewProject)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moNewProject)
const long moNewProject::ID_DIRTEXTCTRL = wxNewId();
const long moNewProject::ID_STATICTEXT1 = wxNewId();
const long moNewProject::ID_NEWPROJECT_BROWSE = wxNewId();
const long moNewProject::ID_STATICTEXT2 = wxNewId();
const long moNewProject::ID_NAMETEXTCTRL = wxNewId();
const long moNewProject::ID_NEWPROJECT_OK = wxNewId();
const long moNewProject::ID_NEWPROJECT_CANCEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(moNewProject,wxDialog)
	//(*EventTable(moNewProject)
	//*)
END_EVENT_TABLE()

moNewProject::moNewProject(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(moNewProject)
	Create(parent, id, _("New Project"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(364,181));
	DirTextCtrl = new wxTextCtrl(this, ID_DIRTEXTCTRL, wxEmptyString, wxPoint(8,32), wxSize(256,21), 0, wxDefaultValidator, _T("ID_DIRTEXTCTRL"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Directory"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	ButtonBrowse = new wxButton(this, ID_NEWPROJECT_BROWSE, _("Browse..."), wxPoint(272,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_NEWPROJECT_BROWSE"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Project Name"), wxPoint(8,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	ProjectNameTextCtrl = new wxTextCtrl(this, ID_NAMETEXTCTRL, wxEmptyString, wxPoint(8,96), wxSize(168,21), 0, wxDefaultValidator, _T("ID_NAMETEXTCTRL"));
	OkButton = new wxButton(this, ID_NEWPROJECT_OK, _("OK"), wxPoint(184,144), wxDefaultSize, 0, wxDefaultValidator, _T("ID_NEWPROJECT_OK"));
	CancelButton = new wxButton(this, ID_NEWPROJECT_CANCEL, _("Cancel"), wxPoint(272,144), wxDefaultSize, 0, wxDefaultValidator, _T("ID_NEWPROJECT_CANCEL"));
	
	Connect(ID_DIRTEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewProject::OnDirTextCtrlText);
	Connect(ID_NEWPROJECT_BROWSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewProject::OnBrowseClick);
	Connect(ID_NAMETEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewProject::OnProjectNameTextCtrlText);
	Connect(ID_NEWPROJECT_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewProject::OnOkClick);
	Connect(ID_NEWPROJECT_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewProject::OnCancelClick);
	//*)

	OkButton->Disable();

}

moNewProject::~moNewProject()
{
	//(*Destroy(moNewProject)
	//*)
}


void moNewProject::OnOkClick(wxCommandEvent& event)
{
    wxString path = DirTextCtrl->GetValue();
    wxString name = ProjectNameTextCtrl->GetValue();

    moText tbasepath(path.mb_str());
    moText tprojectname(name.mb_str());

    moText datapath = (moText)tbasepath + moSlash + (moText)tprojectname + moSlash;

    if ( !wxDirExists( DirTextCtrl->GetValue() + wxString(wxT("/")) + ProjectNameTextCtrl->GetValue() ) ) {
        wxFileName::Mkdir( DirTextCtrl->GetValue() + wxString(wxT("/")) + ProjectNameTextCtrl->GetValue() );
    }

    moText configname = (moText)tprojectname + moText(".mol");

    m_ProjectDescriptor = moProjectDescriptor( configname, datapath );


    EndModal( wxID_OK );
}

void moNewProject::OnCancelClick(wxCommandEvent& event)
{
    EndModal( wxID_CANCEL );
}

void moNewProject::OnBrowseClick(wxCommandEvent& event)
{
    wxDirDialog* pDirDialog = NULL;

    pDirDialog = new wxDirDialog(this,wxT("Choose a directory or create one"),wxT(""),wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (pDirDialog->ShowModal() == wxID_OK) {
        DirTextCtrl->SetValue( pDirDialog->GetPath() );
    }

}

void moNewProject::OnDirTextCtrlText(wxCommandEvent& event)
{
    if (DirTextCtrl->GetValue().IsEmpty()) {
        OkButton->Enable(false);
    } else if (!ProjectNameTextCtrl->GetValue().IsEmpty()) {
        OkButton->Enable(true);
    }
}

void moNewProject::OnProjectNameTextCtrlText(wxCommandEvent& event)
{
    if (ProjectNameTextCtrl->GetValue().IsEmpty()) {
        OkButton->Enable(false);
    } else if (!DirTextCtrl->GetValue().IsEmpty()) {
        OkButton->Enable(true);
    }
}
