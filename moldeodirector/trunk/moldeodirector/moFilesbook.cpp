
#include "moFilesbook.h"

moFilesbookPage::moFilesbookPage( wxWindow* parent, wxWindowID id, moDirectorChildFrame* childframe ) : wxNotebookPage( parent, id) {
	m_pChildFrame = childframe;
}

moDirectorChildFrame*
moFilesbookPage::GetChildFrame() {
	return m_pChildFrame;
}

void
moFilesbookPage::Activate() {
	//m_pChildFrame->Activate();
}


BEGIN_EVENT_TABLE(moFilesbook, wxAuiNotebook)
	EVT_NOTEBOOK_PAGE_CHANGED( -1, moFilesbook::OnPageChange )
END_EVENT_TABLE()

void
moFilesbook::OnPageChange( wxNotebookEvent &event ) {

	//wxMessageBox( "Page change" );
	wxWindow* fpage;
	fpage = GetPage( event.GetSelection() );

    if (fpage->GetName()!=wxT("Start page")) {

        moDirectorChildFrame* fChild = (moDirectorChildFrame*)fpage;



    }

	event.Skip();
}

