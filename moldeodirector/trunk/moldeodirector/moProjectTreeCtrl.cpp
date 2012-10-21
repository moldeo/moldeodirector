#include "moProjectTreeCtrl.h"
#include <wx/artprov.h>
#include <wx/imaglist.h>


BEGIN_EVENT_TABLE(moProjectTreeCtrl, wxTreeCtrl)
  EVT_TREE_ITEM_ACTIVATED( -1, moProjectTreeCtrl::OnActivate )
  EVT_TREE_ITEM_RIGHT_CLICK( -1, moProjectTreeCtrl::OnPopMenu )
  EVT_MENU( MODIRECTOR_DELETEMOB, moProjectTreeCtrl::OnDeleteMob )
  EVT_MENU( MODIRECTOR_DUPLICATEMOB, moProjectTreeCtrl::OnDuplicateMob )
  EVT_MENU( MODIRECTOR_MOVEUPMOB, moProjectTreeCtrl::OnMoveUpMob )
  EVT_MENU( MODIRECTOR_MOVEDOWNMOB, moProjectTreeCtrl::OnMoveDownMob )
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


	wxImageList* imglist = new wxImageList(16, 16 , true, 6);
	//imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(32,32)));
	//imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(32,32)));
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/server_16.png"))) );  //0
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/server_edit_16.png"))) ); //1
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/view_16.png"))) );//2
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/sitemap_16.png"))) );//3
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/settings_16.png"))) );//4
	imglist->Add( wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/relevance_16.png"))) );//5

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

	m_PopMenu.Append( MODIRECTOR_DELETEMOB, _T("&Delete\tAlt-R"), _T("Delete this object"));
	m_PopMenu.Append( MODIRECTOR_DUPLICATEMOB, _T("&Duplicate\tAlt-D"), _T("Duplicate this object"));
	m_PopMenu.Append( MODIRECTOR_MOVEUPMOB, _T("&Move Up\tAlt-U"), _T("Move up this object"));
	m_PopMenu.Append( MODIRECTOR_MOVEDOWNMOB, _T("&Move Down\tAlt-J"), _T("Move down this object"));

}

void
moProjectTreeCtrl::OnActivate(wxTreeEvent &event) {

	moMobItemData* MobItemData = NULL;

	wxTreeItemId itemid = event.GetItem();

	if( itemid.IsOk() )
		MobItemData = (moMobItemData*) GetItemData(itemid);
    else
        LogError("moProjectTreeCtrl::OnActivate Item id is invalid");

	if(MobItemData!=NULL) {

        moMobDescriptor pMobDesc = MobItemData->GetMobDescriptor();

        /// esto se pasa automáticamente al Core
        OpenMob( pMobDesc );

	} else LogError("moProjectTreeCtrl::OnActivate No item data available");
	return;

}


void
moProjectTreeCtrl::OnPopMenu( wxTreeEvent &event ) {

	moMobItemData* MobItemData = NULL;

  m_Popped.Unset();

	m_Popped = event.GetItem();

	if( m_Popped.IsOk() )
		MobItemData = (moMobItemData*) GetItemData(m_Popped);
  else
    LogError("moProjectTreeCtrl::OnPopMenu Item id is invalid");

	if(MobItemData!=NULL) {

        m_MobSelected = MobItemData->GetMobDescriptor();

        /// esto se pasa automáticamente al Core
        ///OpenMob( pMobDesc );
        if (m_MobSelected.IsValid()) {
          this->PopupMenu(&m_PopMenu);
        } else LogError("moProjectTreeCtrl::OnPopMenu Object Descriptor is invalid");

	} else LogError("moProjectTreeCtrl::OnPopMenu No item data available");
	return;

}

void
moProjectTreeCtrl::OnDeleteMob( wxCommandEvent& event ) {

  if ( m_MobSelected.IsValid() ) {

    if( wxMessageBox(_T("Really remove this object from the project?") + wxString(moText2Wx(m_MobSelected.GetMobDefinition().GetLabelName())), _T("Please confirm"),
                            wxICON_QUESTION | wxYES_NO) != wxYES )
      {
          return;
      } else {

          ///delete this object
          Log( moText("removing mob: ") + m_MobSelected.GetMobDefinition().GetLabelName() );
          this->DeleteMob( m_MobSelected );
          return;
      }



  } else LogError("moProjectTreeCtrl::OnDeleteMob Object Descriptor is invalid");

}

void
moProjectTreeCtrl::OnDuplicateMob( wxCommandEvent& event ) {
  if ( m_MobSelected.IsValid() ) {

    if( wxMessageBox(_T("Really duplicate this object from the project ?") + wxString(moText2Wx(m_MobSelected.GetMobDefinition().GetLabelName())), _T("Please confirm"),
                            wxICON_QUESTION | wxYES_NO) != wxYES )
      {
          return;
      } else {

          ///delete this object
          Log( moText("duplicating mob: ") + m_MobSelected.GetMobDefinition().GetLabelName() );
          this->DuplicateMob( m_MobSelected );
          return;
      }



  } else LogError("moProjectTreeCtrl::OnDeleteMob Object Descriptor is invalid");

}


void
moProjectTreeCtrl::OnMoveUpMob( wxCommandEvent& event ) {

  if ( m_MobSelected.IsValid() ) {
      ///delete this object
      Log( moText("Moving up mob: ") + m_MobSelected.GetMobDefinition().GetLabelName() );

      this->MoveMob( m_MobSelected, m_MobSelected.GetMobDefinition().GetMobIndex().GetValueIndex() - 1 );
      return;
  } else LogError("moProjectTreeCtrl::OnMoveUpMob Object Descriptor is invalid");

}


void
moProjectTreeCtrl::OnMoveDownMob( wxCommandEvent& event ) {

  if ( m_MobSelected.IsValid() ) {
      ///delete this object
      Log( moText("Moving down mob: ") + m_MobSelected.GetMobDefinition().GetLabelName() );

      this->MoveMob( m_MobSelected, m_MobSelected.GetMobDefinition().GetMobIndex().GetValueIndex() + 1 );
      return;

  } else LogError("moProjectTreeCtrl::OnMoveDownMob Object Descriptor is invalid");

}


void
moProjectTreeCtrl::ResetBaseTree( wxString p_treename) {

    ///reseteamos el control... (quizas sea mejor destruirlooooo....)
    DeleteAllItems();

    ///volvemos a asignar las ramas...
    rootid = AddRoot( p_treename );

    if (rootid>=-1) {
      mob_ids[ MO_OBJECT_CONSOLE ] = AppendItem( rootid, wxT("Console Config"), 0);
      mob_ids[ MO_OBJECT_PREEFFECT ] = AppendItem( rootid, wxT("PreEffects"), 2);
      mob_ids[ MO_OBJECT_EFFECT ] = AppendItem( rootid, wxT("Effects"), 2);
      mob_ids[ MO_OBJECT_POSTEFFECT ] = AppendItem( rootid, wxT("PostEffects"), 2);
      mob_ids[ MO_OBJECT_MASTEREFFECT ] = AppendItem( rootid, wxT("MasterEffects"), 2);

      mob_ids[ MO_OBJECT_IODEVICE ] = AppendItem(  rootid, moText2Wx( moText("IODevices") ), 3 );
      mob_ids[ MO_OBJECT_RESOURCE ] = AppendItem(  rootid, moText2Wx( moText("Resources") ), 4 );
    }

}

//===============================
// INTERFACE DIRECTOR ACTIONS
//===============================

moDirectorStatus
moProjectTreeCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {

  return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus
moProjectTreeCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {

  return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moProjectTreeCtrl::ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor ) {

    wxTreeItemId exid;
    wxString xitemname;
    moMobDescriptor MobDesc;

    DeleteAllItems();

    if ( p_ProjectDescriptor.GetState() == moProjectDescriptor::STATE_CLOSED ||
         p_ProjectDescriptor.GetState() == moProjectDescriptor::STATE_CLOSING ||
         p_ProjectDescriptor.GetState() == moProjectDescriptor::STATE_UNDEFINED ) {
      return MO_DIRECTOR_STATUS_OK;
    }

    ///pedimos la descripción completa de los mobs
    moMobDescriptors pMobDescriptors = GetMobDescriptors();

    ///recreamos el arbol
    ResetBaseTree( moText2Wx( moText("Project: ") + p_ProjectDescriptor.GetConfigName() ) );


    ///Ahora creamos los items correspondientes a cada mob

    for( MOuint i=0;  i < pMobDescriptors.Count(); i++) {

      moMobDescriptor pMobDescriptor = pMobDescriptors[i];
      moMobDefinition& MobDef( pMobDescriptor.GetMobDefinition() );

      //xitemname = wxString( moText2Wx( MobDef.GetName() )) + wxT(" > ");
      //xitemname+= wxString( moText2Wx( MobDef.GetConfigName() ) );

      xitemname = wxString( moText2Wx( MobDef.GetLabelName() )) + wxT(" (");
      xitemname+= wxString( moText2Wx( MobDef.GetConfigName() ) ) + wxT(".cfg [");
      xitemname+= wxString( moText2Wx( MobDef.GetName() )) + wxT("])");


      ///agregamos el item
      exid = AppendItem( mob_ids[ MobDef.GetType() ], xitemname , 1 );
			if (exid.IsOk()) SetItemData( exid, new moMobItemData( pMobDescriptor ));
			exid.Unset();
    }

    Expand(rootid);

  return MO_DIRECTOR_STATUS_OK;
}



