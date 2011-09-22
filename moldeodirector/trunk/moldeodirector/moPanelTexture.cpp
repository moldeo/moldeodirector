#include "moPanelTexture.h"

//(*InternalHeaders(moPanelTexture)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moPanelTexture)
const long moPanelTexture::ID_TEXTCTRLMEDIA = wxNewId();
const long moPanelTexture::ID_BUTTONIMPORT = wxNewId();
const long moPanelTexture::ID_IMPORTPANEL = wxNewId();
const long moPanelTexture::ID_IMAGEPANEL = wxNewId();
//*)
const long moPanelTexture::ID_SHADERCTRL = wxNewId();
const long moPanelTexture::ID_TEXTURESTREECTRL = wxNewId();



BEGIN_EVENT_TABLE(moPanelTexture,wxPanel)
	//(*EventTable(moPanelTexture)
	//*)
END_EVENT_TABLE()

moPanelTexture::moPanelTexture(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moPanelTexture)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(378,224), wxTAB_TRAVERSAL|wxCLIP_CHILDREN, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1 = new wxFlexGridSizer(3, 1, 1, 1);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer1->AddGrowableRow(2);
	ImportPanel = new wxPanel(this, ID_IMPORTPANEL, wxPoint(120,8), wxSize(264,80), wxTAB_TRAVERSAL, _T("ID_IMPORTPANEL"));
	ImportPanel->SetBackgroundColour(wxColour(0,0,0));
	TextCtrlMedia = new wxTextCtrl(ImportPanel, ID_TEXTCTRLMEDIA, wxEmptyString, wxPoint(66,0), wxSize(176,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLMEDIA"));
	ButtonImport = new wxButton(ImportPanel, ID_BUTTONIMPORT, _("Import"), wxPoint(2,0), wxSize(56,23), wxSIMPLE_BORDER|wxNO_BORDER, wxDefaultValidator, _T("ID_BUTTONIMPORT"));
	ButtonImport->SetForegroundColour(wxColour(255,255,255));
	ButtonImport->SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1->Add(ImportPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ImagePanel = new wxMoColourPanel(this, ID_IMAGEPANEL, wxDefaultPosition, wxSize(100,50), wxTAB_TRAVERSAL, _T("ID_IMAGEPANEL"));
	ImagePanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	FlexGridSizer1->Add(ImagePanel, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_TEXTCTRLMEDIA,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moPanelTexture::OnTextCtrlMediaText);
	Connect(ID_BUTTONIMPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPanelTexture::OnButtonImportClick);
	//*)

    m_pTreeMultiCtrl = NULL;

    m_pShaderCtrl = NULL;
    //m_pTexturesTreeCtrl = NULL;


    ImagePanel->SetColourValue( wxColour(255,255,255,255) );

    wxTreeMultiItem  details_id;
    wxTreeMultiItem  filters_id;
    m_pTreeMultiCtrl = new wxTreeMultiCtrl( this, wxID_ANY );
    m_pTreeMultiCtrl->SetForegroundColour( wxColour( 255, 255, 255) );
    m_pTreeMultiCtrl->SetBackgroundColour(wxColour(0,0,0));

    FlexGridSizer1->Add( m_pTreeMultiCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);


    if ( m_pTreeMultiCtrl ) {
      details_id = m_pTreeMultiCtrl->AddRoot( wxT( "Details" ) );
      filters_id = m_pTreeMultiCtrl->AddRoot( wxT( "Filters" ) );
    }


    m_pShaderCtrl = new moShaderCtrl( m_pTreeMultiCtrl, ID_SHADERCTRL );
    m_pTextDetails = new wxStaticText( m_pTreeMultiCtrl, wxID_ANY, wxT("-"), wxPoint(0,0), wxSize(300,60), wxBORDER_NONE | wxNO_BORDER );

    if (m_pTextDetails) {

      m_pTextDetails->SetForegroundColour( wxColour( 255, 255, 255) );
      m_pTextDetails->SetBackgroundColour(wxColour(0,0,0));

      m_pTreeMultiCtrl->AppendWindow( details_id, m_pTextDetails );
    }

    if (m_pShaderCtrl){
        m_pShaderCtrl->SetNextActionHandler( (moIDirectorActions*) this );
    }

    m_pTreeMultiCtrl->AppendWindow( filters_id, m_pShaderCtrl );

    m_pTreeMultiCtrl->Collapse( details_id, true );
    m_pTreeMultiCtrl->Collapse( filters_id, true );

/*
        if (TreeCtrlImages) {
            m_pTexturesTreeCtrl = new moTexturesTreeCtrl( this, ID_TEXTURESTREECTRL );
            m_pTexturesTreeCtrl->SetSize( TreeCtrlImages->GetPosition().x, TreeCtrlImages->GetPosition().y,
                                        TreeCtrlImages->GetSize().x, TreeCtrlImages->GetSize().y);
            m_pTexturesTreeCtrl->SetNextActionHandler( this );
            TreeCtrlImages->Destroy();
            FlexGridSizer2->Add(m_pTexturesTreeCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
        }
        */
    //TextCtrlMedia->Enable(false);


    m_pShaderCtrl->Enable(false);


}

moPanelTexture::~moPanelTexture()
{
	//(*Destroy(moPanelTexture)
	//*)
}

void
moPanelTexture::InitTexturesTree() {
/*
    if (m_pTexturesTreeCtrl)
        m_pTexturesTreeCtrl->InitDescriptors();
*/
}

void moPanelTexture::LoadImage() {

    //LOAD IMAGE....
    if (m_ValueDescriptor.GetValue().GetSubValueCount()>=1) {

        moText tname = m_ValueDescriptor.GetValue().GetSubValue(0).Text();

        if (tname.Length()>0) {

          moTextureDescriptor pTextDescriptor( tname );

              void* ptr = m_ValueDescriptor.GetValue().GetSubValue(0).Pointer();

              moTexture *pTex = reinterpret_cast<moTexture*>( ptr );


              if  (pTex ) {

                Log( pTex->GetName() );

                moText details;
                moMovie* pMovie = NULL;
                moVideoBuffer* pVideoBuffer = NULL;
                moCircularVideoBuffer* pCircularVideoBuffer = NULL;
                moTextureMultiple* pTextureMultiple = NULL;
                moTextureBuffer* pTextureBuffer = NULL;
                moTextureMemory* pTextureMemory = NULL;


                details = "Name: " + pTex->GetName();

                details+= "\nWidth: " + IntToStr(pTex->GetWidth());
                details+= " Height: " + IntToStr(pTex->GetHeight());
                if (pTex->GetHeight()>0) details+= " Proportion: " + FloatToStr( (float)pTex->GetWidth() / (float)pTex->GetHeight() );

                details+= "\nType: ";
                switch(pTex->GetType()) {
                    case MO_TYPE_TEXTURE:
                      details+= "texture";
                      break;
                    case MO_TYPE_TEXTUREBUFFER:
                      details+= "texture buffer";
                      pTextureBuffer = reinterpret_cast<moTextureBuffer*>( ptr );
                      if (pTextureBuffer) {
                        details+= "\nImages processed: " + IntToStr( pTextureBuffer->GetImagesProcessed() );
                        details+= " buffer format: " + pTextureBuffer->GetBufferFormat();
                      }
                      break;
                    case MO_TYPE_TEXTUREMEMORY:
                      details+= "texture memory";
                      pTextureMemory = reinterpret_cast<moTextureMemory*>( ptr );
                      break;
                    case MO_TYPE_TEXTURE_MULTIPLE:
                      details+= "texture multiple";
                      pTextureMultiple = reinterpret_cast<moTextureMultiple*>( ptr );
                      if (pTextureMultiple) {
                        details+= "\nFrames: " + IntToStr( pTextureMultiple->GetFrameCount() );
                      }
                      break;
                    case MO_TYPE_CIRCULARVIDEOBUFFER:
                      details+= "circular video buffer";
                      pCircularVideoBuffer = reinterpret_cast<moCircularVideoBuffer*>( ptr );
                      if (pCircularVideoBuffer) {
                        details+= "\nFrames: " + IntToStr( pCircularVideoBuffer->GetFrameCount() );
                      }
                      break;
                    case MO_TYPE_VIDEOBUFFER:
                      details+= "video buffer";
                      pVideoBuffer = reinterpret_cast<moVideoBuffer*>( ptr );
                      if (pVideoBuffer) {
                        details+= "\nFrames: " + IntToStr( pVideoBuffer->GetFrameCount() );
                      }
                      break;
                    case MO_TYPE_MOVIE:
                      details+= "movie/video";
                      pMovie = reinterpret_cast<moMovie*>( ptr );
                      if (pMovie) {
                        details+= "\nFrames: " + IntToStr( pMovie->GetFrameCount() );
                        details+= " fps: " + FloatToStr( pMovie->GetFramesPerSecond() );
                        MOlonglong dur = pMovie->GetFrameCount();
                        details+= "\nDuration: " + moVideoManager::FramesToTimecode(dur,pMovie->GetFramesPerSecond());
                      }
                      break;
                }

                wxString wxdetails;
                wxdetails = moText2Wx( details );


                m_pTextDetails->SetLabel( wxdetails );



                /** TODO: optimizar!!!!*/

                MOuchar *bits = NULL;

                bits = new MOuchar[ pTex->GetWidth() * pTex->GetHeight() * 4 ];
                pTex->GetBuffer( bits );

                wxImage* thumbImg =  new wxImage( pTex->GetWidth(), pTex->GetHeight(), false );
                if (thumbImg) {
                  thumbImg->InitAlpha();

                  for(int j=0; j< thumbImg->GetHeight(); j++) {
                    for(int i=0; i< thumbImg->GetWidth(); i++) {
                        thumbImg->SetRGB( i, j,
                                          bits[ (i + j*thumbImg->GetWidth() )*4 ],
                                          bits[ (i + j*thumbImg->GetWidth() )*4 + 1 ],
                                          bits[ (i + j*thumbImg->GetWidth() )*4 + 2 ] );
                        thumbImg->SetAlpha( i, j, bits[ (i + j*thumbImg->GetWidth() )*4 + 3 ] );

                    }
                  }


                  if (thumbImg->IsOk()) {
                    ImagePanel->SetBitmap( wxBitmap(*thumbImg) );

                  }

                  if (thumbImg)
                    delete thumbImg;




                }
                if (bits)
                   delete [] bits;

                /**FIN OPTIMIZAR*/
              }


          /*


          //ask to create thumbnail if necesarry
          pTextDescriptor.CreateThumbnail();

          pTextDescriptor = GetResourceDescriptor( pTextDescriptor );

          if ( pTextDescriptor.GetResourceDefinition().GetType() != MO_RESOURCETYPE_UNDEFINED ) {

            tname = pTextDescriptor.GetResourceDefinition().GetFileName();

            if (tname.Length()>0) {

              moText extension = tname;
              extension.Right(3);

              if (extension!=moText("tga")) {
                  wxFileName mFileName( moText2Wx(tname) );

                  wxBitmap NewBitmap;


                  if ( mFileName.FileExists() ) {
                      if (pTextDescriptor.GetType()==MO_TYPE_TEXTURE)
                        NewBitmap = wxBitmap(wxImage( moText2Wx(tname) ).Rescale( 128, 80 ));
                  } else {
                      NewBitmap = wxBitmap(wxImage(_T("../../art/icons/imageempty.png")).Rescale(128,80) );
                  }

                  StaticBitmapThumbnail->SetBitmap( NewBitmap );

              }
            }

          } else {
            LogError("PanelTexture:: Resource not found ");
          }
          */

        } else {
          LogError("PanelTexture::Empty string");
        }
    }

}

void
moPanelTexture::Inspect( moValueDescriptor p_ValueDescriptor ) {


    if ( (p_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()==MO_PARAM_TEXTURE ||
    p_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()==MO_PARAM_VIDEO) &&
    p_ValueDescriptor.GetValue().GetSubValueCount()>0 ) {

        m_ValueDescriptor = p_ValueDescriptor;

        TextCtrlMedia->ChangeValue( moText2Wx(m_ValueDescriptor.GetValue().GetSubValue(0).Text() ) );

        if (m_pShaderCtrl)
          m_pShaderCtrl->Inspect( m_ValueDescriptor );

        TextCtrlMedia->Enable();
        if (m_pShaderCtrl)
          m_pShaderCtrl->Enable();
        //m_pTexturesTreeCtrl->UpdateDescriptors();

        if (m_ValueDescriptor.GetValue().GetSubValueCount()>=1) {

            moTextureDescriptor pTextureDescriptor( m_ValueDescriptor.GetValue().GetSubValue(0).Text() );
            pTextureDescriptor = GetResourceDescriptor( pTextureDescriptor );

            /*

            moText texttype = moText("Type ");

            switch(pTextureDescriptor.GetType()) {
                    case MO_TYPE_TEXTURE:
                        texttype+= moText("Texture");
                        if (pTextureDescriptor.IsBuildedFromFile() )
                            texttype+= moText(" loaded from file");
                        else
                            texttype+= " (internal)";

                        break;
                    case MO_TYPE_MOVIE:
                        texttype+= moText("Movie Texture");
                        break;
                    case MO_TYPE_TEXTURE_MULTIPLE:
                        texttype+= moText("Texture Multiple");
                        break;
                    case MO_TYPE_VIDEOBUFFER:
                        texttype+= moText("Video buffer");
                        break;
                    case MO_TYPE_CIRCULARVIDEOBUFFER:
                        texttype+= moText("Circular Video buffer");
                        break;
            }
            StaticTextType->SetLabel(  moText2Wx(texttype) );


            moText textsize = moText("Size ") + IntToStr(pTextureDescriptor.GetWidth()) + moText(" x ") + IntToStr(pTextureDescriptor.GetHeight());
            StaticTextSize->SetLabel( moText2Wx( textsize ) );
            */
        }

        LoadImage();
    }
}

void moPanelTexture::OnButtonImportClick(wxCommandEvent& event)
{
    moProjectDescriptor ProjectDescriptor;
    ProjectDescriptor = m_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetProjectDescriptor();

    //making absolute path is mandatory (in linux) for passing directory to the open file dialog
    wxString relativepath = moText2Wx( ProjectDescriptor.GetConfigPath() );

    wxFileName ConfigPath = wxFileName::DirName( relativepath );

    wxFileName absname = wxFileName::DirName( relativepath );
    absname.MakeAbsolute();
    wxString absolutepath = absname.GetPath();


    wxFileDialog* pFileDialog = new wxFileDialog( this );

	if(pFileDialog) {

	    pFileDialog->SetDirectory( absolutepath );

        //beware, for the extensions capitalized in linux!!
		pFileDialog->SetWildcard(wxT("Image/Video files (*.jpg;*.tga;*.png;*.tif;*.xpm;*.avi;*.mov;*.mp4;*.ogg;*.mkv;*.mpg)|*.jpg;*.png;*.tga;*.tif;*.xpm;*.avi;*.mov;*.mp4;*.ogg;*.mkv;*.mpg;*.JPG;*.PNG;*.TGA;*.TIF;*.XPM;*.AVI;*.MOV;*.MP4;*.OGG;*.MKV;*.MPG|Image files(*.jpg;*.tga;*.png;*.tif;*.xpm;)|*.jpg;*.png;*.tga;*.tif;*.xpm;*.JPG;*.PNG;*.TGA;*.TIF;*.XPM;|Video files (*.avi;*.mov;*.mp4;*.ogg;*.mkv;*.mpg)|*.avi;*.mov;*.mp4;*.ogg;*.mkv;*.mpg;*.AVI;*.MOV;*.MP4;*.OGG;*.MKV;*.MPG|All files (*.*)|*.*"));

		if( pFileDialog->ShowModal() == wxID_OK ) {

			wxFileName	FileName( pFileDialog->GetPath() );
			wxFileName	FileNameToCopy( pFileDialog->GetPath() );

			bool samevolumeasconfig = FileName.MakeRelativeTo( relativepath );
			bool intoconfigpath = false;
			FileNameToCopy.MakeAbsolute();

            wxString path = FileName.GetPath();

            wxArrayString dirsconfig = ConfigPath.GetDirs();
            wxArrayString dirsfile = FileName.GetDirs();

            if (samevolumeasconfig ) {

                intoconfigpath = true;

                ///check if it is on a branch of the config folder
                for(int d=0; d<dirsfile.Count(); d++) {
                    if ( dirsfile[d] == _T("..") ) {
                        ///it is below our configpath...
                        intoconfigpath = false;
                    }
                    /*if (dirsconfig[d]==dirsfile[d]) {
                        intoconfigpath = true;
                    } else {
                        intoconfigpath = false;
                        break;
                    }*/
                }
            }

			if ( intoconfigpath ) {

			    ///ok it is on a branch so we just assign the path

                wxString pathrel = FileName.GetFullPath();
                const char *cnamerelative = (char*)pathrel.c_str();

                //ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );
                TextCtrlMedia->SetValue( pathrel );
                if(m_pShaderCtrl)
                  m_pShaderCtrl->Inspect(m_ValueDescriptor);

                //m_pTexturesTreeCtrl->UpdateDescriptors();
			} else {

			    ///not into a branch of the config folder, so we make a copy by default of the file on the root of the project folder
                FileName.MakeAbsolute();
                //ask if you want to import it ( copying it to local folder )
                moText filename_dest = moWx2Text( absname.GetPath() ) + moSlash + moWx2Text( FileName.GetFullName() );
                moText filename_src = moWx2Text( FileNameToCopy.GetFullPath() );
                if (moFileManager::CopyFile( filename_src, filename_dest )) {

                    wxFileName	FileName2( moText2Wx( filename_dest ) );
                    if (FileName2.MakeRelativeTo( relativepath )) {
                        wxString path = FileName2.GetFullPath();
                        TextCtrlMedia->SetValue( path );
                        //m_pTexturesTreeCtrl->UpdateDescriptors();
                    }

                } else {
                    ErrorMessage( moText("Copy error") );
                }

            }

		}

	}

}

void moPanelTexture::OnTextCtrlMediaText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)TextCtrlMedia->GetValue().c_str() ) );

    //fija los nuevos valores en la consola...
    SetValue( m_ValueDescriptor );

    if (m_pShaderCtrl)
      m_pShaderCtrl->Inspect( m_ValueDescriptor );

    LoadImage();


}

void moPanelTexture::OnBitmapButton1Click(wxCommandEvent& event)
{
    //m_pTexturesTreeCtrl->InitDescriptors();
}

void moPanelTexture::OnPanelDetailsPaint(wxPaintEvent& event)
{
}
