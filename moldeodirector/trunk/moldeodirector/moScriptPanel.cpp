#include "moScriptPanel.h"

//(*InternalHeaders(moScriptPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moScriptPanel)
const long moScriptPanel::ID_COMPILEANDRUN = wxNewId();
const long moScriptPanel::ID_SCRIPTEXTCTRL = wxNewId();
const long moScriptPanel::ID_FILETEXTCTRL = wxNewId();
const long moScriptPanel::ID_BROWSESCRIPT = wxNewId();
const long moScriptPanel::ID_SAVEBUTTON = wxNewId();
//*)

BEGIN_EVENT_TABLE(moScriptPanel,wxPanel)
	//(*EventTable(moScriptPanel)
	//*)
END_EVENT_TABLE()

moScriptPanel::moScriptPanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(moScriptPanel)
	Create(parent, id, wxDefaultPosition, wxSize(596,258), wxTAB_TRAVERSAL, _T("id"));
	CompileButton = new wxButton(this, ID_COMPILEANDRUN, _("Compile & Run >"), wxPoint(104,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_COMPILEANDRUN"));
	ScriptTextCtrl = new wxTextCtrl(this, ID_SCRIPTEXTCTRL, _("--here comes the script for LUA"), wxPoint(0,24), wxSize(560,368), wxTE_AUTO_SCROLL|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_SCRIPTEXTCTRL"));
	ScriptFileTextCtrl = new wxTextCtrl(this, ID_FILETEXTCTRL, _("file..."), wxPoint(200,0), wxSize(216,21), 0, wxDefaultValidator, _T("ID_FILETEXTCTRL"));
	BrowseScript = new wxButton(this, ID_BROWSESCRIPT, _("..."), wxPoint(416,0), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BROWSESCRIPT"));
	SaveButton = new wxButton(this, ID_SAVEBUTTON, _("Save"), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_SAVEBUTTON"));

	Connect(ID_COMPILEANDRUN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moScriptPanel::OnCompileButtonClick);
	Connect(ID_FILETEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moScriptPanel::OnScriptFileTextCtrlText);
	Connect(ID_BROWSESCRIPT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moScriptPanel::OnBrowseScriptClick);
	Connect(ID_SAVEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moScriptPanel::OnSaveButtonClick);
	//*)
}

moScriptPanel::~moScriptPanel()
{
	//(*Destroy(moScriptPanel)
	//*)
}


void moScriptPanel::OnButton1Click(wxCommandEvent& event)
{
}

void moScriptPanel::OnCompileButtonClick(wxCommandEvent& event)
{

    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(0).SetText( moText("__compiling__.lua")  );

    SetValue( m_ValueDescriptor );

    rValue.GetSubValue(0).SetText(moWx2Text(ScriptFileTextCtrl->GetValue()));

    SetValue( m_ValueDescriptor );


}

void moScriptPanel::Inspect( moValueDescriptor p_ValueDescriptor ) {

    m_ValueDescriptor = p_ValueDescriptor;

    moProjectDescriptor ProjectDescriptor;
    ProjectDescriptor = m_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetProjectDescriptor();

    //making absolute path is mandatory (in linux) for passing directory to the open file dialog
    wxString relativepath = (wxChar*)(char*)ProjectDescriptor.GetConfigPath();
    wxFileName absname = wxFileName::DirName( relativepath );
    absname.MakeAbsolute();
    wxString absolutepath = absname.GetPath();

    if (m_ValueDescriptor.GetValue().GetSubValueCount()==1) {

        wxString scriptname( moText2Wx( m_ValueDescriptor.GetValue().GetSubValue(0).Text() ) );

        ScriptFileTextCtrl->SetValue( scriptname );

        ///load text from file!!!

        moValue& pValue( m_ValueDescriptor.GetValue() );

        ScriptTextCtrl->LoadFile( absolutepath + _("/") + scriptname );

    }

}

void moScriptPanel::OnBrowseScriptClick(wxCommandEvent& event)
{

    wxFileDialog* OpenD;


}

void moScriptPanel::OnScriptFileTextCtrlText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(0).SetText(moWx2Text(ScriptFileTextCtrl->GetValue()));

    SetValue( m_ValueDescriptor );
}

void moScriptPanel::OnSaveButtonClick(wxCommandEvent& event)
{
    moProjectDescriptor ProjectDescriptor;
    ProjectDescriptor = m_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetProjectDescriptor();

    //making absolute path is mandatory (in linux) for passing directory to the open file dialog
    wxString relativepath = (wxChar*)(char*)ProjectDescriptor.GetConfigPath();
    wxFileName absname = wxFileName::DirName( relativepath );
    absname.MakeAbsolute();
    wxString absolutepath = absname.GetPath();

    ScriptTextCtrl->SaveFile( absolutepath + _("/") + ScriptFileTextCtrl->GetValue() );


}
