#include "mo3dModelPanel.h"

//(*InternalHeaders(mo3dModelPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(mo3dModelPanel)
const long mo3dModelPanel::ID_TEXTCTRL3DMODEL = wxNewId();
const long mo3dModelPanel::ID_BUTTONIMPORT = wxNewId();
const long mo3dModelPanel::ID_PANEL3DMODEL = wxNewId();
const long mo3dModelPanel::ID_LISTCTRL3DMODEL = wxNewId();
//*)


BEGIN_EVENT_TABLE(mo3dModelPanel,wxPanel)
	//(*EventTable(mo3dModelPanel)
	//*)
END_EVENT_TABLE()

mo3dModelPanel::mo3dModelPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(mo3dModelPanel)
	Create(parent, id, wxDefaultPosition, wxSize(240,303), wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(0,0,0));
	TextCtrl3dModel = new wxTextCtrl(this, ID_TEXTCTRL3DMODEL, wxEmptyString, wxPoint(88,48), wxSize(144,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3DMODEL"));
	ButtonImport = new wxButton(this, ID_BUTTONIMPORT, _("Import"), wxPoint(88,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONIMPORT"));
	Panel3dModel = new wxPanel(this, ID_PANEL3DMODEL, wxPoint(0,8), wxSize(80,64), wxTAB_TRAVERSAL, _T("ID_PANEL3DMODEL"));
	Panel3dModel->SetBackgroundColour(wxColour(0,0,255));
	ListCtrl3dModel = new wxListCtrl(this, ID_LISTCTRL3DMODEL, wxPoint(0,80), wxSize(232,200), 0, wxDefaultValidator, _T("ID_LISTCTRL3DMODEL"));
	//*)
}

mo3dModelPanel::~mo3dModelPanel()
{
	//(*Destroy(mo3dModelPanel)
	//*)
}

void
mo3dModelPanel::Inspect( moValueDescriptor p_ValueDescriptor ) {
    Log("3d model inspect");
}

void
mo3dModelPanel::Init3dModelsTree() {


}


