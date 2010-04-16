#include "moShadersPanel.h"

//(*InternalHeaders(moShadersPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moShadersPanel)
const long moShadersPanel::ID_LISTCTRL1 = wxNewId();
const long moShadersPanel::ID_LISTCTRLFILTERS = wxNewId();
//*)

BEGIN_EVENT_TABLE(moShadersPanel,wxPanel)
	//(*EventTable(moShadersPanel)
	//*)
END_EVENT_TABLE()

moShadersPanel::moShadersPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moShadersPanel)
	Create(parent, id, wxDefaultPosition, wxSize(288,205), wxTAB_TRAVERSAL, _T("id"));
	ListCtrlShaders = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(0,0), wxSize(100,248), 0, wxDefaultValidator, _T("ID_LISTCTRL1"));
	ListCtrlFilters = new wxListCtrl(this, ID_LISTCTRLFILTERS, wxPoint(104,0), wxSize(224,248), 0, wxDefaultValidator, _T("ID_LISTCTRLFILTERS"));
	//*)

	if (ListCtrlFilters) {
        m_pTreeFiltersCtrl =  new wxTreeMultiCtrl( this, wxID_ANY, ListCtrlFilters->GetPosition(), ListCtrlFilters->GetSize() );
        ListCtrlFilters->Destroy();
    }
}

moShadersPanel::~moShadersPanel()
{
	//(*Destroy(moShadersPanel)
	//*)
}


void
moShadersPanel::Inspect( moValueDescriptor p_ValueDescriptor ) {

    m_ParamDescriptor = p_ValueDescriptor.GetParamDescriptor();

    InitShadersTree();

}

void
moShadersPanel::Inspect( moParameterDescriptor p_ParamDescriptor ) {

    m_ParamDescriptor = p_ParamDescriptor;

    InitShadersTree();

}

void
moShadersPanel::InitShadersTree() {

    if (m_ParamDescriptor.GetParamDefinition().GetType() == MO_PARAM_FILTER ) {

        m_pTreeFiltersCtrl->DeleteAllItems();
        m_pTreeFiltersCtrl->AddRoot( wxT("filters") );

        m_ValueDescriptors.Empty();

        m_ValueDescriptors = GetValueDescriptors( m_ParamDescriptor );

        for( int i = 0; i < m_ValueDescriptors.Count(); i++) {

                moValueDescriptor pVal =  m_ValueDescriptors[i];

                moShaderCtrl*   pShaderCtrl = NULL;
                pShaderCtrl = new moShaderCtrl( m_pTreeFiltersCtrl, wxID_ANY );
                pShaderCtrl->Inspect( pVal );

        }
    } else {
        LogError( moText("Inspection unattended: not a FILTER parameter! ") );
    }


}
