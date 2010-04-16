
#include "moTreeObjectsLayerCtrl.h"



void
moTreeLayerCtrl::AddLayer( wxTreeMultiItem id, moItemLayerWindow* p_ObjectLayerCtrl ) {

    //add an object to the tree, must be a window two!!!

}

void
moTreeLayerCtrl::SetScrollPosition( int position ) {
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

                    pObj = (moItemLayerWindow*) LayerWindow->GetWindow();
                    if (pObj) {
                        pObj->SetScrollPosition(position);
                    }
                }

            }
        }

	}
}

void
moTreeLayerCtrl::SetSplitPosition( int position ) {

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

                    pObj = (moItemLayerWindow*) LayerWindow->GetWindow();
                    if (pObj) {
                        pObj->SetSashPosition(position);
                    }
                }

            }
        }

	}
}


moItemLayerWindow*
moTreeLayerCtrl::FindObjectByMob( moMobDescriptor p_MobDesc, TreeMultiItemNode *n ) {

    moItemLayerWindow* pObj;
    pObj = NULL;

    moItemLayerWindow* result = NULL;

    moMobDescriptor p_MobDesc1 = p_MobDesc;


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
            pObj = (moItemLayerWindow*) pWnd;

            if (pObj) {
                moMobDescriptor& p_MobDesc2(pObj->Get());
                int id1 = p_MobDesc1.GetMobDefinition().GetMoldeoId();
                int id2 = p_MobDesc2.GetMobDefinition().GetMoldeoId();

                //Comparamos por MoldeoId 's
                if ( id1 == id2 ) {
                    return pObj;
                }
            }

		}

		// if node, go deeper
		if(n->GetNode(i)->IsTreeMultiItemNode())
			result = FindObjectByMob( p_MobDesc1, (TreeMultiItemNode*)n->GetNode(i));

        if (result)
            return result;
	}

    return result;

}


moDirectorStatus
moTreeLayerCtrl::ValueUpdated( moValueDescriptor p_ValueDesc ) {

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
moTreeLayerCtrl::MobUpdated( moMobDescriptor p_MobDesc ) {

    //recorre los mobs y lo actualiza


    return MO_DIRECTOR_STATUS_OK;

}



/*
BEGIN_EVENT_TABLE( moLayersPanelCtrl, wxSplitterWindow )

END_EVENT_TABLE()


moLayersPanelCtrl::moLayersPanelCtrl( wxWindow *parent, wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style,
                const wxString& name ) : wxSplitterWindow(parent, id, pos, size, style, name) {

   / * wxFlexGridSizer *topsizer = new wxFlexGridSizer( 3 );
    topsizer->SetFlexibleDirection(wxBOTH);
    topsizer->AddGrowableCol(0);
    topsizer->AddGrowableCol(2);
    topsizer->AddGrowableRow(0);


    topsizer->Add( new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(300,300)),
                1, wxALL, 10 );

    //topsizer->AddSpacer(300);

    topsizer->AddStretchSpacer(20);

    //topsizer->AddSpacer(500);

    topsizer->Add( new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(300,300)),
                1, wxALL, 10  );


    SetSizer( topsizer );      // use the sizer for layout

    topsizer->Layout();

    //topsizer->SetSizeHints( this );
* /

}

*/


BEGIN_EVENT_TABLE( moLayersPanelCtrl, wxPanel )
    EVT_SCROLL( moLayersPanelCtrl::ScrollTimeline )
    EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, moLayersPanelCtrl::SashPosition )
    EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, moLayersPanelCtrl::SashChanged )
    EVT_SPLITTER_DCLICK(wxID_ANY, moLayersPanelCtrl::SashDClick)
END_EVENT_TABLE()


moLayersPanelCtrl::moLayersPanelCtrl( wxWindow *parent, wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style,
                const wxString& name ) : wxPanel(parent, id, pos, size, style, name) {

    wxFlexGridSizer *topsizer = new wxFlexGridSizer( 3, 1, 0, 0 );// 3 filas, 1 columna
    topsizer->SetFlexibleDirection(wxBOTH);
    topsizer->AddGrowableRow(1);
    topsizer->AddGrowableCol(0);


    TopSplitter = new wxSplitterWindow(this, wxID_ANY, wxPoint(0,0), wxSize(400,13), wxNO_BORDER );

    m_pLayersTopCtrl = new wxPanel(TopSplitter,wxID_ANY, wxDefaultPosition, wxSize(300,13), wxNO_BORDER);
    m_pLayersTopCtrl->SetForegroundColour(wxColour(120,120,120));
    m_pLayersTopCtrl->SetBackgroundColour( wxColour(70,70,70) );

    m_pTimelineRulerWindow = new wxWindow( TopSplitter, wxID_ANY, wxPoint(0,0), wxSize(400,13), wxNO_BORDER );
    m_pTimelineRuler = new moTimelineRuler( m_pTimelineRulerWindow, wxID_ANY, 0, 0, 480, wxPoint(0,0), wxSize(480,13), wxNO_BORDER );

    TopSplitter->SplitVertically( m_pLayersTopCtrl, m_pTimelineRulerWindow );


    m_pLayersTreeCtrl = new moTreeLayerCtrl( this, wxID_ANY, wxPoint(0,0), wxSize(500,100) );
    m_pLayersTreeCtrl->SetForegroundColour(wxColour(120,120,120));
    m_pLayersTreeCtrl->SetBackgroundColour( wxColour(70,70,70) );
    m_pLayersTreeCtrl->ShowScrollBars( false, true);
    //m_pLayersTreeCtrl->SetNextActionHandler( this );

    // 0 border in all borders, expand control, but fixed minsize
    //labels observer goes here
    //timeline, two
    topsizer->Add( TopSplitter, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE , 0 );

    // 0 border in all borders, expand control
    topsizer->Add( m_pLayersTreeCtrl, 1, wxALL | wxEXPAND, 0 );

    //topsizer->AddSpacer(500);

    BottomSplitter = new wxSplitterWindow(this, wxID_ANY, wxPoint(0,0), wxSize(400,15), wxNO_BORDER );

    ScrollBar = new wxScrollBar(BottomSplitter, wxID_ANY, wxPoint(4,0), wxSize(300,15), wxSB_HORIZONTAL);
    ScrollBar->SetForegroundColour(wxColour(170,170,170));
    ScrollBar->SetBackgroundColour( wxColour(60,60,60) );

    //edit, delete and duplicate control buttons goes HERE
    m_pLayersBottomCtrl = new wxPanel(BottomSplitter,wxID_ANY, wxPoint(0,0), wxSize(265,15), wxNO_BORDER);
    m_pLayersBottomCtrl->SetForegroundColour(wxColour(170,170,170));
    m_pLayersBottomCtrl->SetBackgroundColour( wxColour(60,60,60) );

    BottomSplitter->SplitVertically( m_pLayersBottomCtrl, ScrollBar );



    topsizer->Add( BottomSplitter, 1, wxTOP | wxEXPAND | wxFIXED_MINSIZE , 0  );
    SetSizer( topsizer );      // use the sizer for layout
    topsizer->Layout();
    //topsizer->SetSizeHints( this );

    TopSplitter->SetSashPosition(265);
    TopSplitter->SetSashSize(1);

    BottomSplitter->SetSashPosition(265);
    BottomSplitter->SetSashSize(1);
    ScrollBar->SetScrollbar(0, 1000/100, 480, 100, true);

}


void moLayersPanelCtrl::SashPosition( wxSplitterEvent& event ) {

    //wxMessageBox("position");

    int i = event.GetSashPosition();

    m_pLayersTreeCtrl->SetSplitPosition( i );
    BottomSplitter->SetSashPosition(i);
    TopSplitter->SetSashPosition(i);

}

void moLayersPanelCtrl::SashChanged( wxSplitterEvent& event ) {
    //donothing
    return;
}


void moLayersPanelCtrl::SashDClick( wxSplitterEvent& event ) {
    wxMessageBox(wxString(_("stop doing that!")));
}

void moLayersPanelCtrl::ScrollTimeline( wxScrollEvent& event ) {
    int i = event.GetPosition();
    m_pLayersTreeCtrl->SetScrollPosition( i );
    ScrollBar->SetScrollPos( 0, i, true );
    m_pTimelineRuler->SetSize( -i, 0, wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING );
}


