#include "moPanelTexture.h"

//(*InternalHeaders(moPanelTexture)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moPanelTexture)
const long moPanelTexture::ID_STATICBOX1 = wxNewId();
const long moPanelTexture::ID_PANELFILTER = wxNewId();
const long moPanelTexture::ID_STATICTEXT6 = wxNewId();
const long moPanelTexture::ID_STATICTEXT7 = wxNewId();
const long moPanelTexture::ID_STATICTEXT1 = wxNewId();
const long moPanelTexture::ID_TEXTCTRLMEDIA = wxNewId();
const long moPanelTexture::ID_BUTTONIMPORT = wxNewId();
const long moPanelTexture::ID_STATICTEXT3 = wxNewId();
const long moPanelTexture::ID_PANEL4 = wxNewId();
const long moPanelTexture::ID_STATICBITMAPTHUMB = wxNewId();
const long moPanelTexture::ID_PANELPreview = wxNewId();
const long moPanelTexture::ID_STATICTEXT2 = wxNewId();
const long moPanelTexture::ID_STATICTEXTSIZE = wxNewId();
const long moPanelTexture::ID_BITMAPBUTTON1 = wxNewId();
const long moPanelTexture::ID_PANEL5 = wxNewId();
const long moPanelTexture::ID_TREECTRL1 = wxNewId();
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
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(402,285), wxTAB_TRAVERSAL|wxCLIP_CHILDREN, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(0,0,0));
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	Panel4 = new wxPanel(this, ID_PANEL4, wxPoint(120,8), wxSize(264,80), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	Panel4->SetBackgroundColour(wxColour(0,0,0));
	StaticBox1 = new wxStaticBox(Panel4, ID_STATICBOX1, _("Description"), wxPoint(8,16), wxSize(352,104), 0, _T("ID_STATICBOX1"));
	StaticBox1->SetForegroundColour(wxColour(255,255,255));
	PanelFilter = new wxPanel(Panel4, ID_PANELFILTER, wxPoint(48,48), wxSize(296,24), wxTAB_TRAVERSAL, _T("ID_PANELFILTER"));
	StaticText2 = new wxStaticText(Panel4, ID_STATICTEXT6, _("Level of filter %"), wxPoint(152,24), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText2->SetForegroundColour(wxColour(255,255,255));
	StaticText3 = new wxStaticText(Panel4, ID_STATICTEXT7, _("Filter"), wxPoint(16,56), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticText3->SetForegroundColour(wxColour(255,255,255));
	StaticText1 = new wxStaticText(Panel4, ID_STATICTEXT1, _("File"), wxPoint(16,88), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->SetForegroundColour(wxColour(255,255,255));
	TextCtrlMedia = new wxTextCtrl(Panel4, ID_TEXTCTRLMEDIA, wxEmptyString, wxPoint(48,88), wxSize(232,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLMEDIA"));
	ButtonImport = new wxButton(Panel4, ID_BUTTONIMPORT, _("Import"), wxPoint(288,88), wxSize(56,23), wxSIMPLE_BORDER|wxNO_BORDER, wxDefaultValidator, _T("ID_BUTTONIMPORT"));
	ButtonImport->SetForegroundColour(wxColour(255,255,255));
	ButtonImport->SetBackgroundColour(wxColour(0,0,0));
	StaticTextFiltered = new wxStaticText(Panel4, ID_STATICTEXT3, _("Destination texture"), wxPoint(248,24), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticTextFiltered->SetForegroundColour(wxColour(255,255,255));
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	FlexGridSizer2->AddGrowableRow(0);
	Panel5 = new wxPanel(this, ID_PANEL5, wxPoint(16,144), wxSize(180,208), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	Panel5->SetBackgroundColour(wxColour(0,0,0));
	PanelPreview = new wxPanel(Panel5, ID_PANELPreview, wxPoint(0,0), wxSize(144,96), wxTAB_TRAVERSAL, _T("ID_PANELPreview"));
	PanelPreview->SetBackgroundColour(wxColour(0,0,0));
	StaticBitmapThumbnail = new wxStaticBitmap(PanelPreview, ID_STATICBITMAPTHUMB, wxBitmap(wxImage(_T("../../doc/icons/imageempty.png")).Rescale(wxSize(128,80).GetWidth(),wxSize(128,80).GetHeight())), wxPoint(0,0), wxSize(128,80), 0, _T("ID_STATICBITMAPTHUMB"));
	StaticTextType = new wxStaticText(Panel5, ID_STATICTEXT2, _("Type"), wxPoint(0,104), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticTextType->SetForegroundColour(wxColour(255,255,255));
	StaticTextSize = new wxStaticText(Panel5, ID_STATICTEXTSIZE, _("Size"), wxPoint(0,128), wxDefaultSize, 0, _T("ID_STATICTEXTSIZE"));
	StaticTextSize->SetForegroundColour(wxColour(255,255,255));
	BitmapButton1 = new wxBitmapButton(Panel5, ID_BITMAPBUTTON1, wxNullBitmap, wxPoint(104,176), wxSize(40,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer2->Add(Panel5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TreeCtrlImages = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxSize(224,208), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	TreeCtrlImages->SetBackgroundColour(wxColour(255,255,255));
	FlexGridSizer2->Add(TreeCtrlImages, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_TEXTCTRLMEDIA,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moPanelTexture::OnTextCtrlMediaText);
	Connect(ID_BUTTONIMPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPanelTexture::OnButtonImportClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moPanelTexture::OnBitmapButton1Click);
	//*)

    m_pShaderCtrl = NULL;
    //m_pTexturesTreeCtrl = NULL;

    if (PanelFilter) {
        m_pShaderCtrl = new moShaderCtrl( Panel4, ID_SHADERCTRL, PanelFilter->GetPosition(), PanelFilter->GetSize() );
        if (m_pShaderCtrl){
            m_pShaderCtrl->SetNextActionHandler( (moIDirectorActions*) this );
            PanelFilter->Destroy();
        }
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
        TextCtrlMedia->Enable(false);
        m_pShaderCtrl->Enable(false);
    }

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

        TextCtrlMedia->ChangeValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(0).Text() );

        m_pShaderCtrl->Inspect( m_ValueDescriptor );

        TextCtrlMedia->Enable();
        m_pShaderCtrl->Enable();
        //m_pTexturesTreeCtrl->UpdateDescriptors();

        if (m_ValueDescriptor.GetValue().GetSubValueCount()>=1) {

            moTextureDescriptor pTextureDescriptor( m_ValueDescriptor.GetValue().GetSubValue(0).Text() );
            pTextureDescriptor = GetResourceDescriptor( pTextureDescriptor );

            moText texttype = moText("Type ");

            switch(pTextureDescriptor.GetType()) {
                    case MO_TYPE_TEXTURE:
                        texttype+= moText("Texture");
                        if (pTextureDescriptor.IsBuildedFromFile() )
                            texttype+= moText(" loaded from file");
                        else
                            texttype+= moText(" (internal)");

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
        }

        LoadImage();
    }
}

void moPanelTexture::OnButtonImportClick(wxCommandEvent& event)
{
    moProjectDescriptor ProjectDescriptor;
    ProjectDescriptor = m_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetProjectDescriptor();

    //making absolute path is mandatory (in linux) for passing directory to the open file dialog
    wxString relativepath = (wxChar*)(const char*)ProjectDescriptor.GetConfigPath();
    wxFileName absname = wxFileName::DirName( relativepath );
    absname.MakeAbsolute();
    wxString absolutepath = absname.GetPath();


    wxFileDialog* pFileDialog = new wxFileDialog( this );

	if(pFileDialog) {

	    pFileDialog->SetDirectory( absolutepath );

        //beware, for the extensions capitalized in linux!!
		pFileDialog->SetWildcard(wxT("Image files (*.jpg;*.tga;*.png;*.avi;*.mov;*.mpg)|*.jpg;*.png;*.tga;*.avi;*.mov;*.mpg;*.JPG;*.PNG;*.TGA;*.AVI;*.MOV;*.MPG|All files (*.*)|*.*"));

		if( pFileDialog->ShowModal() == wxID_OK ) {

			wxFileName	FileName( pFileDialog->GetPath() );

			if (FileName.MakeRelativeTo( relativepath )) {

                wxString path = FileName.GetFullPath();
                const char *cnamerelative = (char*)path.c_str();

                //ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );
                TextCtrlMedia->SetValue( path );
                //m_pShaderCtrl->Inspect(m_ValueDescriptor);

                //m_pTexturesTreeCtrl->UpdateDescriptors();
			} else {
                //ask if you want to import it ( copying it to local folder )
                moText filename_dest = moWx2Text( absname.GetPath() ) + moSlash + moWx2Text( FileName.GetFullName() );
                moText filename_src = moWx2Text( FileName.GetFullPath() );
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

    m_pShaderCtrl->Inspect( m_ValueDescriptor );

    LoadImage();


}

void moPanelTexture::OnBitmapButton1Click(wxCommandEvent& event)
{
    //m_pTexturesTreeCtrl->InitDescriptors();
}
