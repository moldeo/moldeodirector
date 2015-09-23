#include "moDirectorChildFrame.h"
#include "moValueCtrl.h"

#include "moArray.h"

moDefineDynamicArray( moValueTreeItemList )
moDefineDynamicArray( moParamTreeItemList )


BEGIN_EVENT_TABLE(moDirectorChildFrame, wxPanel)
	EVT_CLOSE( moDirectorChildFrame::OnClose )
	EVT_SET_FOCUS(moDirectorChildFrame::OnFocus)
	EVT_SIZE( moDirectorChildFrame::OnSize )
END_EVENT_TABLE()

moDirectorChildFrame::moDirectorChildFrame( wxWindow* parent, const wxString& title)
       : wxPanel((wxWindow*)parent, wxID_ANY, wxDefaultPosition, wxSize(640,480),
                         wxBORDER_NONE, _T("child frame") )
{

    m_cForeground = wxColour(255,255,255);
    m_cBackground = wxColour(0,0,0);

    //my_children.Append(this);

	//wxFlexGridSizer* sizer = new wxFlexGridSizer(2,1,0,0);
	//sizer->AddGrowableRow(1);
	//sizer->AddGrowableCol(0);
	//sizer->AddGrowableCol(1);

	//sizer->Add( new wxStaticText( this, wxID_ANY, title, wxPoint(0,0), wxSize(300,25)), 1, wxEXPAND | wxALL );
	m_pConfigNotebook = NULL;
/*
	m_pConfigNotebook = new moConfigNotebook( this , wxID_ANY, wxPoint(0,0),wxSize(300,300), wxNO_BORDER );
	m_pConfigNotebook->SetForegroundColour(m_cForeground);
    m_pConfigNotebook->SetBackgroundColour(m_cBackground);
*/
	//m_pConfigParameterFoldbar = new moConfigParameterFoldbar( m_pConfigNotebook , wxID_ANY );
	m_pParameterTree = new moParametersTree( this, wxID_ANY );
	m_pParameterTree->SetSpacingY(0);
	m_pParameterTree->SetForegroundColour(m_cForeground);
  m_pParameterTree->SetBackgroundColour(m_cBackground);

/*
	//		moConfigTextCodeCtrl(wxWindow* parent, wxWindowID idconst, wxString& value, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0 );
	m_pConfigTextCodeCtrl = new moConfigTextCodeCtrl( (wxWindow*)m_pConfigNotebook , (wxWindowID)wxID_ANY,  _T(""), wxPoint(0,0), wxSize(100,100), (long)(wxTE_MULTILINE | wxTE_DONTWRAP) );
	m_pConfigTextCodeCtrl->SetForegroundColour(m_cForeground);
    m_pConfigTextCodeCtrl->SetBackgroundColour(m_cBackground);

	m_pConnection = new wxPanel( m_pConfigNotebook, wxID_ANY );
	m_pConnection->SetForegroundColour(m_cForeground);
    m_pConnection->SetBackgroundColour(m_cBackground);

	m_pPreview = new wxPanel( m_pConfigNotebook, wxID_ANY );
	m_pPreview->SetForegroundColour(m_cForeground);
    m_pPreview->SetBackgroundColour(m_cBackground);
*/
	//m_pConfigNotebook->AddPage( m_pConfigParameterFoldbar, "Parameters" );
	if (m_pConfigNotebook) m_pConfigNotebook->AddPage( m_pParameterTree, wxT("Params") );
	//m_pConfigNotebook->AddPage( m_pConfigTextCodeCtrl, wxT("Code") );
	//m_pConfigNotebook->AddPage( m_pConnection, wxT("Connections") );
	//m_pConfigNotebook->AddPage( m_pPreview, wxT("Preview") );

	//sizer->Add(m_pConfigNotebook, 1, wxEXPAND | wxALL);


	//console relative:
	m_ConfigType = MO_OBJECT_UNDEFINED;
	m_nPosition = 0;

	if (m_pConfigNotebook) m_pConfigNotebook->SetSelection(0);

	// this should work for MDI frames as well as for normal ones
	//SetSizeHints( 200, 200);
	//sizer->SetFlexibleDirection(wxBOTH);
	//SetSizer( sizer );
    //sizer->SetSizeHints(this);
}

void moDirectorChildFrame::OnSize(wxSizeEvent& event) {

    //wxMessageBox("resize");
    int w,h;
    GetParent()->GetClientSize( &w, &h );
    //wxMessageBox( wxString("parent size:") + moText2Wx(IntToStr(w)) );
    if (m_pConfigNotebook) m_pConfigNotebook->SetSize( w, h );

    ///se agrego -15 para ajustar el tamaño correctamente al notebook
    if (m_pParameterTree) m_pParameterTree->SetSize( w, h-15 );
    event.Skip();

}

void
moDirectorChildFrame::Inspect( moValueDescriptor    p_ValueDescriptor, bool setselection ) {

    moDirectorFrame* pDirectorFrame = (moDirectorFrame*)m_pDirectorFrame;
    //check if MOB is OK
    if ( p_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetLabelName() == m_MobDescriptor.GetMobDefinition().GetLabelName() ) {
        //A OK!!!
        if (setselection) {
          ///guardamos el ultimo valor que se inspecciono
          m_ValueDescriptor = p_ValueDescriptor;
        }
        pDirectorFrame->Inspect( p_ValueDescriptor, setselection );
    } else {
        //Something is wrong
        LogError(moText("Couldn't inspect, MOB doesn't match"));
    }

}

void
moDirectorChildFrame::InspectAll() {

        moDirectorFrame* pDirectorFrame = (moDirectorFrame*)m_pDirectorFrame;

        for( int i=0; i<(int)m_ParamTreeItemList.Count(); i++) {
            moParamTreeItem& ParamItem( m_ParamTreeItemList[i] );
            /**
            * TODO: Optimize this!!! Changing tab selection on FilesBook freezes all
            */
            /**/
            /** Opcion activar unicamente el color y textura?? */
            //ParameterUpdated( ParamItem.GetParamDescriptor() );
            /** */
        }

        if ( m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().IsValid() ) {
          pDirectorFrame->Inspect( m_ValueDescriptor, true );
        }
}

MOboolean moDirectorChildFrame::Init( moDirectorFrame* pDirectorFrame, moMobDescriptor p_MobDescriptor ) {
	m_pDirectorFrame = pDirectorFrame;
	this->SetNextActionHandler((moIDirectorActions*)m_pDirectorFrame);
	m_MobDescriptor = p_MobDescriptor;
	return true;

}

moDirectorChildFrame::~moDirectorChildFrame()
{
	Finish();
}

MOboolean moDirectorChildFrame::Finish() {
    m_pDirectorFrame->CloseMob( m_MobDescriptor );//remove from child list
	return true;
}


void
moDirectorChildFrame::Save() {
    if (m_pDirectorFrame->SaveMob( m_MobDescriptor ) == MO_DIRECTOR_STATUS_OK) {
        ShowMessage( moText("\"") + moText(m_MobDescriptor.GetMobDefinition().GetLabelName()) + moText("\"") + moText(" object saved succesfully") );
    } else {
        ErrorMessage( moText("\"") + moText(m_MobDescriptor.GetMobDefinition().GetLabelName()) + moText("\"") + moText("Object Not Saved!!"));
    }
}

moDirectorStatus
moDirectorChildFrame::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {

    moParamTreeItem& ParamItem( m_ParamTreeItemList[ p_ParameterDesc.GetParamDefinition().GetIndex()] );

    if (ParamItem.GetParamDescriptor().GetParamDefinition().GetName() == p_ParameterDesc.GetParamDefinition().GetName() ) {

        moValueTreeItem ValueTreeItem;
/*
OPTIMIZE, why check every single value???
*/
        for( int i=0; i<(int)ParamItem.GetValueTreeItemList().Count(); i++) {

            //int i = p_ParameterDesc.GetIndexValue();
            ValueTreeItem = ParamItem.GetValueTreeItemList().GetRef(i);

            moValueCtrl* pValueCtrl = dynamic_cast<moValueCtrl*>(ValueTreeItem.GetWindow());

            if (pValueCtrl) {
                /** Only inspect the value selected....*/
                if ( p_ParameterDesc.GetIndexValue() == i) {
                    pValueCtrl->ParamToggleOn();
                    ParamItem.GetParamDescriptor().SetIndexValue(i);
                    Inspect( pValueCtrl->GetValueDescriptor(), false );
                } else {
                    /*toggling off is important...*/
                    pValueCtrl->ParamToggleOff();
                }
            }
            //Add( moValueTreeItem( p_ValueDesc, (wxWindow*)pValueCtrl ) );

        }

    }

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moDirectorChildFrame::DeleteValue( moValueDescriptor p_ValueDesc ) {

    if ( m_pDirectorFrame->DeleteValue(p_ValueDesc) == MO_DIRECTOR_STATUS_OK ) {

        //m_ParamTreeItemList.Remove( p_ValueDesc.GetValueIndex().m_ValueIndex );
        moParamTreeItem& ParamItem( m_ParamTreeItemList[ p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetIndex()] );

        moValueTreeItem ValueTreeItem = ParamItem.GetValueTreeItemList().Get( p_ValueDesc.GetValueIndex().m_ValueIndex );

        //moValueCtrl* pValueCtrl = (moValueCtrl*)ValueTreeItem.GetWindow();

        //if (pValueCtrl)
           // pValueCtrl->Destroy();

        wxTreeMultiItem vItem = ValueTreeItem.GetItem();
        //wxTreeMultiItem vItem = ParamItem.GetItem();

        m_pParameterTree->Delete( vItem );

        ParamItem.GetValueTreeItemList().Remove( p_ValueDesc.GetValueIndex().m_ValueIndex );

        for( int i=p_ValueDesc.GetValueIndex().m_ValueIndex; i<(int)ParamItem.GetValueTreeItemList().Count(); i++) {
            moValueTreeItem ValueTreeItem = ParamItem.GetValueTreeItemList().Get(i);
            moValueCtrl* pValueCtrl = dynamic_cast<moValueCtrl*>(ValueTreeItem.GetWindow());
            if (pValueCtrl) {
                    pValueCtrl->GetValueDescriptor().GetValueIndex().m_ValueIndex = i;
                    pValueCtrl->GetValueDescriptor().GetValueDefinition().SetIndex(i);
            }
        }

        if ( ParamItem.GetParamDescriptor().GetIndexValue() >= p_ValueDesc.GetValueIndex().m_ValueIndex ) {
            m_pDirectorFrame->Log( moText("m_ValueIndex:") + IntToStr(p_ValueDesc.GetValueIndex().m_ValueIndex) );
            m_pDirectorFrame->Log( moText("Param Index Value:") + IntToStr(ParamItem.GetParamDescriptor().GetIndexValue()) );

            ParamItem.GetParamDescriptor().SetIndexValue(max( 0, ParamItem.GetParamDescriptor().GetIndexValue() - 1 ));

            m_pDirectorFrame->SetParameter( ParamItem.GetParamDescriptor() );

        }

        return MO_DIRECTOR_STATUS_OK;

    }

    return MO_DIRECTOR_STATUS_ERROR;

}

moDirectorStatus
moDirectorChildFrame::EditParameter( moParameterDescriptor p_ParameterDesc ) {

    wxString ParamStr = moText2Wx(p_ParameterDesc.GetParamDefinition().GetName());

    if (m_pParameterTree) {
      //chequear que no exista el item, en otro caso no hacer nada
      wxTreeMultiItem item = m_pParameterTree->AddRoot( ParamStr );
      m_pParameterTree->Collapse( item, true );

      m_ParamTreeItemList.Add( moParamTreeItem( p_ParameterDesc, item ) );

      wxWindow* pWindow = m_pParameterTree->GetWindow(item);

      if (pWindow) {
          pWindow->SetForegroundColour(wxColour(255,255,255));
          pWindow->SetBackgroundColour(m_cBackground);
      } else return MO_DIRECTOR_STATUS_ERROR;

      this->SetForegroundColour(m_cForeground);
      this->SetBackgroundColour(m_cBackground);

      return MO_DIRECTOR_STATUS_OK;
    }

    return MO_DIRECTOR_STATUS_ERROR;
}

moDirectorStatus
moDirectorChildFrame::EditValue( moValueDescriptor p_ValueDesc ) {

    wxTreeMultiWindowInfo wndinfo(0,0,0);
    // indent a few
    wndinfo.Indent(0);

    moValueCtrl* pValueCtrl;

    pValueCtrl = new moValueCtrl( m_pParameterTree,0 , 0 );

    pValueCtrl->SetForegroundColour(m_cForeground);
    pValueCtrl->SetBackgroundColour(m_cBackground);

    pValueCtrl->Init( this, p_ValueDesc );

    moParameterDescriptor ParamDesc;
    ParamDesc = p_ValueDesc.GetParamDescriptor();

    moParamTreeItem& ParamItem( m_ParamTreeItemList[ ParamDesc.GetParamDefinition().GetIndex() ] );

    if (ParamItem.GetParamDescriptor().GetParamDefinition().GetName() == ParamDesc.GetParamDefinition().GetName() ) {
        wxTreeMultiItem vItem = m_pParameterTree->AppendWindow( ParamItem.GetItem(), pValueCtrl , wxT(""), wndinfo);
        ParamItem.GetValueTreeItemList().Add( moValueTreeItem( vItem, p_ValueDesc, (wxWindow*)pValueCtrl ) );
    }

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moDirectorChildFrame::ValueUpdated( moValueDescriptor p_ValueDesc ) {

    moParameterDescriptor ParamDesc;

    ParamDesc = p_ValueDesc.GetParamDescriptor();

    moParamTreeItem& ParamItem( m_ParamTreeItemList[ ParamDesc.GetParamDefinition().GetIndex() ] );

    if (ParamItem.GetParamDescriptor().GetParamDefinition().GetName() == ParamDesc.GetParamDefinition().GetName() ) {

        moValueTreeItemList& VT( ParamItem.GetValueTreeItemList() );

        moValueTreeItem& mValueTreeItem( VT[ p_ValueDesc.GetValueIndex().m_ValueIndex] );

        moValueCtrl* pValueCtrl = dynamic_cast<moValueCtrl*>( mValueTreeItem.GetWindow() );
        if (pValueCtrl) {
            pValueCtrl->Set( p_ValueDesc );
            return MO_DIRECTOR_STATUS_OK;
        }
    }

    return MO_DIRECTOR_STATUS_ERROR;
}


moDirectorStatus
moDirectorChildFrame::MobUpdated( moMobDescriptor p_MobDesc ) {

    m_MobDescriptor = p_MobDesc;

    SetLabel( moText2Wx( m_MobDescriptor.GetMobDefinition().GetLabelName() ) );

    return MO_DIRECTOR_STATUS_OK;

}



bool moDirectorChildFrame::IsMob( moMobDescriptor p_MobDescriptor ) {


	if ( p_MobDescriptor.GetMobDefinition().GetMoldeoId()==m_MobDescriptor.GetMobDefinition().GetMoldeoId() &&
		p_MobDescriptor.GetMobDefinition().GetMoldeoFatherId()==m_MobDescriptor.GetMobDefinition().GetMoldeoFatherId()) {
		return true;
	} else return false;
}

moMobDescriptor moDirectorChildFrame::GetMob() {

        return m_MobDescriptor;
}


void moDirectorChildFrame::OnFocus(wxFocusEvent& event) {

    //UpdateMob(); ???
    if ( event.GetWindow() != this && event.GetWindow()->GetParent() != this && event.GetWindow()->GetParent()->GetParent() != this) {
        for( int i=0; i<(int)m_ParamTreeItemList.Count(); i++) {
            moParamTreeItem& ParamItem( m_ParamTreeItemList[i] );
            ParameterUpdated( ParamItem.GetParamDescriptor() );
        }
    }
    event.Skip();
}

void moDirectorChildFrame::OnClose(wxCloseEvent& event)
{
    wxString tName = moText2Wx( m_MobDescriptor.GetMobDefinition().GetConfigName() );

    if( wxMessageBox(_T("Save before close \"")+tName+_T("\" ?"), _T("Please confirm"),
                      wxICON_QUESTION | wxYES_NO) != wxYES )
    {
        event.Veto();

        return;
    }

    event.Skip();
}

bool moDirectorChildFrame::Close() {

    wxString tName = moText2Wx( m_MobDescriptor.GetMobDefinition().GetConfigName() );

    int result = wxMessageBox(_T("Save before close \"")+tName+_T("\" ?"), _T("Please confirm"),
                      wxICON_QUESTION | wxYES_NO | wxCANCEL );
    switch(result) {
        case wxYES:
            //save before closing
            Save();
            return true;
            break;
        case wxNO:
            //do not save
            return true;
        case wxCANCEL:
            return false;
    }

    return false;

}

