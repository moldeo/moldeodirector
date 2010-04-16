#include "moProjectTreeCtrl.h"

BEGIN_EVENT_TABLE(moProjectTreeCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_ACTIVATED( -1, moProjectTreeCtrl::OnActivate )
END_EVENT_TABLE()


moProjectTreeCtrl::moProjectTreeCtrl( wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style ):
wxTreeCtrl( parent, id, pos, size, style ) {

	//SDL_Init( SDL_INIT_VIDEO );
	//SDL_SetVideoMode( 160, 100, 24, SDL_SWSURFACE );
//	p_s = SDL_CreateRGBSurface( 0, 160, 100, 24, 0, 0, 0, 0);

	/*
	wxTreeItemId root = this->AddRoot(wxT("Moldeo Project"));
	*/
	wxArrayTreeItemIds items;


	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
	this->AssignImageList(imglist);

	/*
	items.Add(this->AppendItem(root, wxT("PreEffects"), 0));
	items.Add(this->AppendItem(root, wxT("Effects"), 0));
	items.Add(this->AppendItem(root, wxT("PostEffects"), 0));
	items.Add(this->AppendItem(root, wxT("IODevices"), 0));
	items.Add(this->AppendItem(root, wxT("Misc"), 0));

	int i, count;
	for(i = 0, count = items.Count(); i < count; ++i)
	{
		wxTreeItemId id = items.Item(i);
		this->AppendItem(id, wxT("Subitem 1"), 1);
		this->AppendItem(id, wxT("Subitem 2"), 1);
		this->AppendItem(id, wxT("Subitem 3"), 1);
		this->AppendItem(id, wxT("Subitem 4"), 1);
		this->AppendItem(id, wxT("Subitem 5"), 1);
	}

	this->Expand(root);
	*/

}

void
moProjectTreeCtrl::OnActivate(wxTreeEvent &event) {

	moMobItemData* MobItemData = NULL;

	wxTreeItemId itemid = event.GetItem();

	if( itemid.IsOk() )
		MobItemData = (moMobItemData*) GetItemData(itemid);
    else
        m_pDirectorFrame->LogError("moProjectTreeCtrl::OnActivate Item id is invalid");

	if(MobItemData!=NULL) {
	    moMobDescriptor pMobDesc = MobItemData->GetMobDescriptor();
        m_pDirectorFrame->OpenMob( pMobDesc );
	} else m_pDirectorFrame->LogError("moProjectTreeCtrl::OnActivate No item data available");
	return;

}
