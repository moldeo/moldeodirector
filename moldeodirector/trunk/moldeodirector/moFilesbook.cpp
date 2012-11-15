
#include "moFilesbook.h"

moFilesbookPage::moFilesbookPage( wxWindow* parent, wxWindowID id, moDirectorChildFrame* childframe ) : wxAuiNotebookPage() {
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
	EVT_AUINOTEBOOK_PAGE_CHANGED( -1, moFilesbook::OnPageChange )
END_EVENT_TABLE()


void
moFilesbook::OnPageChange( wxAuiNotebookEvent &event ) {

	wxWindow* fpage;
	wxAuiNotebookPage* AuiPage;
	fpage = GetPage( event.GetSelection() );

  //wxMessageBox( fpage->GetName());
  if (fpage) {
    //AuiPage = (wxAuiNotebookPage*) fpage;
    if (fpage->GetName()!=wxT("Start page")) {

        moDirectorChildFrame* pChild =dynamic_cast<moDirectorChildFrame*>(fpage);
        if (pChild) {
            moMobDescriptor p_MobDescriptor;
            p_MobDescriptor = pChild->GetMob();

           //now that we founded it run the iterative Inspector...
            //this->Inspect( p_MobDescriptor );
            pChild->InspectAll();
        }

    }
  }

	event.Skip();
}

