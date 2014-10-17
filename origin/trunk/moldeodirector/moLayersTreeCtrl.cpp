
#include "moLayersTreeCtrl.h"



void
moLayersTreeCtrl::AddLayer( wxTreeMultiItem id, moItemLayerWindow* p_ObjectLayerCtrl ) {

    //add an object to the tree, must be a window two!!!

}

void
moLayersTreeCtrl::SetScrollPosition( int position ) {
    moItemLayerWindow* pObj;
    pObj = NULL;
/*
	// take root node if not assigned one
	TreeMultiItemNode *root = (TreeMultiItemNode *)&_root;


	TreeMultiItemWindow *LayerWindow;
	TreeMultiItemNode *PrincipalLayerNode;

	for(int i = 0; i < root->GetNodeCount(); i++)
	{
		// if window node
        if (root->GetNode(i)->IsTreeMultiItemNode()) {
            PrincipalLayerNode = (TreeMultiItemNode*) root->GetNode(i);
            for(int j = 0; j < PrincipalLayerNode->GetNodeCount(); j++)
            {
                LayerWindow = PrincipalLayerNode->GetNode(j)->IsTreeMultiItemWindow();

                if (LayerWindow) {

                    pObj = dynamic_cast<moItemLayerWindow*>( LayerWindow->GetWindow() );
                    if (pObj) {
                        pObj->SetScrollPosition(position);
                    }
                }

            }
        }

	}*/
}

void
moLayersTreeCtrl::SetSplitPosition( int position ) {
/*
    moItemLayerWindow* pObj;
    pObj = NULL;

	// take root node if not assigned one
	TreeMultiItemNode *root = (TreeMultiItemNode *)&_root;


	TreeMultiItemWindow *LayerWindow;
	TreeMultiItemNode *PrincipalLayerNode;

	for(int i = 0; i < root->GetNodeCount(); i++)
	{
		// if window node
        if (root->GetNode(i)->IsTreeMultiItemNode()) {
            PrincipalLayerNode = (TreeMultiItemNode*) root->GetNode(i);
            for(int j = 0; j < PrincipalLayerNode->GetNodeCount(); j++)
            {
                LayerWindow = PrincipalLayerNode->GetNode(j)->IsTreeMultiItemWindow();

                if (LayerWindow) {

                    pObj = dynamic_cast<moItemLayerWindow*>( LayerWindow->GetWindow() );
                    if (pObj) {
                        pObj->SetSashPosition(position);
                    }
                }

            }
        }

	}*/
}


moItemLayerWindow*
moLayersTreeCtrl::FindObjectByMob( moMobDescriptor p_MobDesc, TreeMultiItemNode *n ) {

    moItemLayerWindow* pObj;
    pObj = NULL;

    moItemLayerWindow* result = NULL;

    moMobDescriptor p_MobDesc1 = p_MobDesc;

    if (!p_MobDesc1.GetMobDefinition().IsValid()) {
      LogError( moText("moLayersTreeCtrl::FindObjectByMob:: Source > MobDefinition Invalid") );
      return NULL;
    }

	// take root node if not assigned one
	if(!n)
		n = (TreeMultiItemNode *)&_root;

	// check on this level for the wxWindow pointer

	TreeMultiItemWindow *w;

	for(int i = 0; i < n->GetNodeCount(); i++)
	{
		// if window node
		w = n->GetNode(i)->IsTreeMultiItemWindow();

		if(w) {
            wxWindow* pWnd  = w->GetWindow();
            pObj = dynamic_cast<moItemLayerWindow*>( pWnd );

            if (pObj) {
                moMobDescriptor& p_MobDesc2(pObj->Get());

                if (!p_MobDesc2.GetMobDefinition().IsValid()) {
                  LogError( moText("FindObjectByMob:: Destination > MobDefinition Invalid") );
                  return NULL;
                }

                int id1 = p_MobDesc1.GetMobDefinition().GetMoldeoId();
                int id2 = p_MobDesc2.GetMobDefinition().GetMoldeoId();


                //Comparamos por MoldeoId 's
                if ( id1 == id2) {
                    return pObj;
                }
            } else {
                //wxMessageBox("Error in moLayersTreeCtrl::FindObjectByMob - pObj not an moItemLayerWindow");
            }

		}

		// if node, go deeper
		if(n->GetNode(i)->IsTreeMultiItemNode())
			result = FindObjectByMob( p_MobDesc1, (TreeMultiItemNode*)n->GetNode(i)); //llamada recursiva

        if (result)
            return result;
	}

    return result;

}


moDirectorStatus
moLayersTreeCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {


    //recorre los mobs a ver a quien le pertenece!!! este valor y se lo pasa


    moItemLayerWindow* pLayerCtrl = FindObjectByMob( p_ValueDesc.GetParamDescriptor().GetMobDescriptor() );

    if (pLayerCtrl) {

            moMobDescriptor p_MobDesc = pLayerCtrl->Get();

            return pLayerCtrl->ValueUpdated( p_ValueDesc );

    } else if ( p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_IODEVICE
    || p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_RESOURCE
    || p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_MASTEREFFECT) {
        //skip...

    } else {
        LogError( moText("No layer object control founded!! ::") + (moText)p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetLabelName() );

        return MO_DIRECTOR_STATUS_ERROR;

    }


    return MO_DIRECTOR_STATUS_OK;

}

moDirectorStatus
moLayersTreeCtrl::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {

    moItemLayerWindow* pLayerCtrl = FindObjectByMob( p_ParameterDesc.GetMobDescriptor() );

    if (pLayerCtrl) {

            moMobDescriptor p_MobDesc = pLayerCtrl->Get();

            return pLayerCtrl->ParameterUpdated( p_ParameterDesc );

    } else if ( p_ParameterDesc.GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_IODEVICE
    || p_ParameterDesc.GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_RESOURCE
    || p_ParameterDesc.GetMobDescriptor().GetMobDefinition().GetType() == MO_OBJECT_MASTEREFFECT ) {
        //skip...

    } else {
        LogError( moText("No layer object control founded!! ::") + (moText)p_ParameterDesc.GetMobDescriptor().GetMobDefinition().GetLabelName() );

        return MO_DIRECTOR_STATUS_ERROR;

    }


    return MO_DIRECTOR_STATUS_OK;


}


moDirectorStatus
moLayersTreeCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {


    ///recorre los mobs y lo actualiza
    moItemLayerWindow* pLayerCtrl = FindObjectByMob( p_MobDesc );

    if (pLayerCtrl) {
      return pLayerCtrl->MobUpdated( p_MobDesc );
    } else {
        LogError( moText("No layer object control founded!! ::") + (moText)p_MobDesc.GetMobDefinition().GetLabelName() );
    }


    return MO_DIRECTOR_STATUS_ERROR;

}


moDirectorStatus
moLayersTreeCtrl::ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor ) {

    moItemLayerWindow* pobject = NULL;
    wxTreeMultiItem mitemid;

    ///intento de borrar unicamente los layers correspondientes...al final resolvimos borrar todo...mejor..
    ///esto lo usaremos para actualizar lo que querramos de cada layer
    this->Hide();

    DeleteAllItems();

    if (p_ProjectDescriptor.GetState()==moProjectDescriptor::STATE_CLOSED ||
        p_ProjectDescriptor.GetState()==moProjectDescriptor::STATE_CLOSING ||
        p_ProjectDescriptor.GetState()==moProjectDescriptor::STATE_UNDEFINED ) {
      this->Show();
      return MO_DIRECTOR_STATUS_OK;
    }

    mob_ids[MO_OBJECT_CONSOLE] = AddRoot( wxT("console"), wxT("console"), NULL );

		mob_ids[MO_OBJECT_PREEFFECT] = AddRoot( wxT("pre-fx"), wxT("pre-fx"), NULL );
		mob_ids[MO_OBJECT_EFFECT] = AddRoot( wxT("fx"), wxT("fx"), NULL );
		mob_ids[MO_OBJECT_POSTEFFECT] = AddRoot( wxT("post-fx"), wxT("post-fx"), NULL );
		mob_ids[MO_OBJECT_MASTEREFFECT] = AddRoot( wxT("master"), wxT("master"), NULL );

		mob_ids[MO_OBJECT_IODEVICE] = wxTreeMultiItem(NULL);
		mob_ids[MO_OBJECT_RESOURCE] = wxTreeMultiItem(NULL);



    SetSpacingY(0);

    ///info para agregar al MultiItemCtrl.... (spacing,indentation, etc...)
    wxTreeMultiWindowInfo wndinfo( wxTMC_SPAN_WIDTH, 0, 0, false);
    wndinfo.SetTopSpacing(0);
    wndinfo.SetFrontSpacing(0);
    wndinfo.Indent(0);

    ///pedimos la descripción completa de los mobs
    moMobDescriptors pMobDescriptors = GetMobDescriptors();

    ///Ahora creamos los items correspondientes a cada mob
    for( MOuint i=0;  i < pMobDescriptors.Count(); i++) {

      moMobDescriptor pMobDescriptor = pMobDescriptors[i];
      moMobDefinition MobDef = pMobDescriptor.GetMobDefinition();

      if ( MO_OBJECT_UNDEFINED<MobDef.GetType() && MobDef.GetType() <= MO_OBJECT_MASTEREFFECT ) {
        ///TEST SIN NADA
        /**
        wxPanel* t = new wxPanel( this, wxID_ANY, wxPoint(0,0), wxSize(200,100));
        if ((i%2)==0) t->SetBackgroundColour( wxColour(255,0,0) );
        if ((i%2)==1) t->SetBackgroundColour( wxColour(0,255,0) );
        AppendWindow( mob_ids[MobDef.GetType()], t, _(""), wndinfo);
        */

        wxTreeMultiItem id_effect = AppendNode( mob_ids[MobDef.GetType()], moText2Wx( MobDef.GetLabelName() ), moText2Wx( MobDef.GetName() ));

        pobject = new moItemLayerWindow( this , wxID_ANY, wxPoint(0,0), wxSize(900,28) );
        if ((i%2)==0) pobject->SetBackgroundColour( wxColour(50,50,50) );
        if ((i%2)==1) pobject->SetBackgroundColour( wxColour(0,0,0) );

        if (pobject) {
            pobject->SetNextActionHandler(this);
            pobject->Inspect( pMobDescriptor );
            //AppendWindow( mob_ids[MobDef.GetType()], pobject, _(""), wndinfo);
        }

        AppendWindow( id_effect, pobject, _(""), wndinfo);
/**
        wxTreeMultiItem idparams = AppendNode( id_effect, wxT("params"),
                                                              wxT("params") );

        ///info para agregar al MultiItemCtrl.... (spacing,indentation, etc...)

        wxTreeMultiWindowInfo wndinfo( wxTMC_SPAN_WIDTH, 0, 0, false);
        wndinfo.SetTopSpacing(0);
        wndinfo.SetFrontSpacing(0);
        wndinfo.Indent(0);

        for(int j=0; j<10; j++) {
          wxPanel* t = new wxPanel( this, wxID_ANY, wxPoint(0,0), wxSize(200,10));
          if ((j%2)==0) t->SetBackgroundColour( wxColour(190, 120, 0 ) );
          if ((j%2)==1) t->SetBackgroundColour( wxColour(0, 190,128) );
          wxTreeMultiItem idparam = AppendNode( idparams, wxT("param"),
                                                              wxT("param") );

          AppendWindow( idparam, t, _(""), wndinfo);

        }*/

        Collapse( id_effect, true );
      }

      /**
      /// no es necesario.... al menos que se haga un control específico....
      /// ver moDirectorConsole::SetMob
      if (MobDef.GetType()==MO_OBJECT_CONSOLE) {

        pobject = new moItemLayerWindow( this , wxID_ANY, wxPoint(0,0), wxSize(900,28) );
        if ((i%2)==0) pobject->SetBackgroundColour( wxColour(50,50,50) );
        if ((i%2)==1) pobject->SetBackgroundColour( wxColour(0,0,0) );

        if (pobject) {
            pobject->SetNextActionHandler(this);
            pobject->Inspect( pMobDescriptor );
            //AppendWindow( mob_ids[MobDef.GetType()], pobject, _(""), wndinfo);
        }

        AppendWindow( mob_ids[MO_OBJECT_CONSOLE], pobject, _(""), wndinfo);

      }*/

    }

    this->Show();
    return MO_DIRECTOR_STATUS_OK;

}


moDirectorStatus
moLayersTreeCtrl::SetMob( moMobDescriptor p_MobDesc ) {

    if (m_pNextActionHandler)
      return m_pNextActionHandler->SetMob( p_MobDesc );
    else
      return MO_DIRECTOR_STATUS_NO_HANDLER;
}

