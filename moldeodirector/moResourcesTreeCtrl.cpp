
#include "moResourcesTreeCtrl.h"



BEGIN_EVENT_TABLE( moResourcesTreeCtrl, wxTreeMultiCtrl )
//
END_EVENT_TABLE()

moResourcesTreeCtrl::moResourcesTreeCtrl( wxWindow* window, wxWindowID id) :
wxTreeMultiCtrl( window, id ) {
    SetSpacingY(0);

    EmptyBitmap = wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/imageempty.png")).Rescale(64,64) );
    SetForegroundColour( wxColour(255,255,255) );
    SetBackgroundColour( wxColour(0,0,0) );
}

moResourcesTreeCtrl::~moResourcesTreeCtrl() {

}

void moResourcesTreeCtrl::InitDescriptors() {

    this->DeleteAllItems();

    imgid = this->AddRoot( _T("Images"), _T("images"), NULL );
    videosid = this->AddRoot( _T("Videos"), _T("videos"), NULL );
    othersid = this->AddRoot( _T("Others"), _T("others"), NULL );

    m_ResourceDescriptors.Empty();

    m_ResourceDescriptors = GetResourceDescriptors( MO_RESOURCETYPE_TEXTURE );

    moTextureDescriptor pTextureDescriptor("empty");

    wxTreeMultiItem selid;

    for( int i =0; i<m_ResourceDescriptors.Count() ; i++) {

        pTextureDescriptor = m_ResourceDescriptors[i];

        switch(pTextureDescriptor.GetType()) {
            case MO_TYPE_MOVIE:
                pTextureDescriptor.CreateThumbnail();
                pTextureDescriptor = GetResourceDescriptor(pTextureDescriptor);
                selid = videosid;
                break;

            case MO_TYPE_TEXTURE:
                selid = imgid;
                pTextureDescriptor.CreateThumbnail();
                pTextureDescriptor = GetResourceDescriptor(pTextureDescriptor);
                if ( ! pTextureDescriptor.IsBuildedFromFile() ) {
                   selid =  othersid;
                }
                break;

            case MO_TYPE_TEXTURE_MULTIPLE:
            case MO_TYPE_VIDEOBUFFER:
            case MO_TYPE_CIRCULARVIDEOBUFFER:
                selid = videosid;
                break;
        }

        wxFileName mFileName( moText2Wx(pTextureDescriptor.GetResourceDefinition().GetFileName()) );

        moText extension = pTextureDescriptor.GetResourceDefinition().GetFileName();
        extension.Right(3);


        wxBitmap NewBitmap;

        if (extension==moText("tga")) {

            NewBitmap = EmptyBitmap;
        } else {
            if ( mFileName.FileExists() ) {
                NewBitmap = wxBitmap(wxImage( moText2Wx(pTextureDescriptor.GetResourceDefinition().GetFileName()) ).Rescale( 64, 64 ));
            } else {
                NewBitmap = EmptyBitmap;
            }
        }

        //m_ImageList.Add( NewBitmap );

        moTextureItemCtrl* pItemCtrl = new moTextureItemCtrl( this, wxID_ANY );

        if (pItemCtrl) {
            pItemCtrl->Init( pTextureDescriptor, NewBitmap  );
            this->AppendWindow( selid, pItemCtrl, _T("texture") );
        }


    }

}

void moResourcesTreeCtrl::UpdateDescriptors() {

    //recorrer de nuevo los existentes, para poder agregar el resto...
    moResourceDescriptors new_ResourceDescriptors;

    new_ResourceDescriptors = GetResourceDescriptors( MO_RESOURCETYPE_TEXTURE );

    moTextureDescriptor NewOne("empty");
    moTextureDescriptor OldOne("empty");

    wxTreeMultiItem selid;

    for( int i =0; i < new_ResourceDescriptors.Count() ; i++) {

        bool m_bInsertNewOne = false;
        bool m_bAddNewOne= false;

        NewOne = new_ResourceDescriptors[i];
        if ( i < m_ResourceDescriptors.Count() ) {
            OldOne = m_ResourceDescriptors[i];
            m_bInsertNewOne =  !( NewOne.GetResourceDefinition().GetName() == OldOne.GetResourceDefinition().GetName() );
        } else {
            m_bAddNewOne = true;
        }


        if (m_bInsertNewOne || m_bAddNewOne) {

            //try to add the image...
            moTextureDescriptor& pTextureDescriptor(NewOne);

            switch(pTextureDescriptor.GetType()) {
                case MO_TYPE_MOVIE:
                    pTextureDescriptor.CreateThumbnail();
                    pTextureDescriptor = GetResourceDescriptor(pTextureDescriptor);
                    selid = videosid;
                    NewOne = pTextureDescriptor;
                    break;

                case MO_TYPE_TEXTURE:
                    selid = imgid;
                    pTextureDescriptor.CreateThumbnail();
                    pTextureDescriptor = GetResourceDescriptor(pTextureDescriptor);
                    if ( ! pTextureDescriptor.IsBuildedFromFile() ) {
                       selid =  othersid;
                    }
                    NewOne = pTextureDescriptor;
                    break;

                case MO_TYPE_TEXTURE_MULTIPLE:
                case MO_TYPE_VIDEOBUFFER:
                case MO_TYPE_CIRCULARVIDEOBUFFER:
                    selid = videosid;
                    NewOne = pTextureDescriptor;
                    break;
                default:
                    NewOne = pTextureDescriptor;
                    break;
            }

            if (m_bInsertNewOne) m_ResourceDescriptors.Insert( i, NewOne );
            if (m_bAddNewOne) m_ResourceDescriptors.Add( NewOne );

            wxFileName mFileName( moText2Wx(NewOne.GetResourceDefinition().GetFileName()) );

            wxBitmap NewBitmap;

            if ( mFileName.FileExists() ) {
                NewBitmap = wxBitmap(wxImage( moText2Wx(NewOne.GetResourceDefinition().GetFileName()) ).Rescale( 64, 64 ));
            } else {
                NewBitmap = EmptyBitmap;
            }

            moTextureItemCtrl* pItemCtrl = new moTextureItemCtrl( this, wxID_ANY );

            if (pItemCtrl) {
                pItemCtrl->Init( NewOne, NewBitmap  );
                wxTreeMultiItem newitem = this->AppendWindow( selid, pItemCtrl, _T("texture") );
                this->Refresh();
                m_ResourceDescriptors[i].SetItemIndex( newitem.IsOk() );

            }
        }

    }



}

