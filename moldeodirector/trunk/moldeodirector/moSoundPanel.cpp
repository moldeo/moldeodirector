#include "moSoundPanel.h"

//(*InternalHeaders(moSoundPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moSoundPanel)
const long moSoundPanel::ID_TEXTCTRLSOUND = wxNewId();
const long moSoundPanel::ID_STATICTEXTDETAILS = wxNewId();
const long moSoundPanel::ID_BUTTONIMPORT = wxNewId();
//*)

BEGIN_EVENT_TABLE(moSoundPanel,wxPanel)
	//(*EventTable(moSoundPanel)
	//*)
END_EVENT_TABLE()

moSoundPanel::moSoundPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moSoundPanel)
	Create(parent, id, wxDefaultPosition, wxSize(254,97), wxTAB_TRAVERSAL, _T("id"));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
	TextCtrlSound = new wxTextCtrl(this, ID_TEXTCTRLSOUND, wxEmptyString, wxPoint(104,8), wxSize(208,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLSOUND"));
	m_pTextDetails = new wxStaticText(this, ID_STATICTEXTDETAILS, _("Details:"), wxPoint(8,40), wxSize(256,112), 0, _T("ID_STATICTEXTDETAILS"));
	m_pTextDetails->SetForegroundColour(wxColour(255,255,255));
	m_pTextDetails->SetBackgroundColour(wxColour(0,0,0));
	ButtonImport = new wxButton(this, ID_BUTTONIMPORT, _("Import Sound"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONIMPORT"));
	ButtonImport->SetForegroundColour(wxColour(255,255,255));
	ButtonImport->SetBackgroundColour(wxColour(0,0,0));

	Connect(ID_TEXTCTRLSOUND,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moSoundPanel::OnTextCtrlSoundText);
	Connect(ID_BUTTONIMPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moSoundPanel::OnButtonImportClick);
	//*)
}

moSoundPanel::~moSoundPanel()
{
	//(*Destroy(moSoundPanel)
	//*)
}


void moSoundPanel::LoadSound() {

//LOAD IMAGE....
  if (m_ValueDescriptor.GetValue().GetSubValueCount()>=1) {

      moText tname = m_ValueDescriptor.GetValue().GetSubValue(0).Text();

      if (tname.Length()>0) {

        moSoundDescriptor pSoundDescriptor( tname );

        void* ptr = m_ValueDescriptor.GetValue().GetSubValue(0).Pointer();

        moSound *pSound = reinterpret_cast<moSound*>( ptr );


        if  (pSound ) {

          Log( pSound->GetName() );

          moText details;

          details = "Name: " + pSound->GetName();
          details+= "\nChannels: " + IntToStr(pSound->GetAudioFormat().m_Channels );
          details+= " Rate: " + IntToStr(pSound->GetAudioFormat().m_SampleRate );
          details+= "\nDuration: " + moVideoManager::NanosecondsToTimecode( pSound->GetDuration() );

          wxString wxdetails;
          wxdetails = moText2Wx( details );
          m_pTextDetails->SetLabel( wxdetails );

        }
      } else {
        LogError("SoundPanel::Empty string");
      }

    }


}

void
moSoundPanel::Inspect( moValueDescriptor p_ValueDescriptor ) {


    if ( (p_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()==MO_PARAM_SOUND) &&
    p_ValueDescriptor.GetValue().GetSubValueCount()>0 ) {

        m_ValueDescriptor = p_ValueDescriptor;

        TextCtrlSound->ChangeValue( moText2Wx(m_ValueDescriptor.GetValue().GetSubValue(0).Text() ) );


        TextCtrlSound->Enable();


        if (m_ValueDescriptor.GetValue().GetSubValueCount()>0) {

            moSoundDescriptor pSoundDescriptor( m_ValueDescriptor.GetValue().GetSubValue(0).Text() );
            pSoundDescriptor = GetResourceDescriptor( pSoundDescriptor );

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

        LoadSound();
    }
}

void moSoundPanel::OnButtonImportClick(wxCommandEvent& event)
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
		pFileDialog->SetWildcard(wxT("Sound files (*.mp3;*.wav;*.ogg;)|*.mp3;*.wav;*.ogg|All files (*.*)|*.*"));

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
                //const char *cnamerelative = (char*)pathrel.c_str();
                //ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );
                TextCtrlSound->SetValue( pathrel );


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
                        TextCtrlSound->SetValue( path );
                        //m_pTexturesTreeCtrl->UpdateDescriptors();
                    }

                } else {
                    ErrorMessage( moText("Copy error") );
                }

            }

		}

	}

}

void moSoundPanel::OnTextCtrlSoundText(wxCommandEvent& event)
{
    moValue& rValue( m_ValueDescriptor.GetValue() );

    rValue.GetSubValue(0).SetText( moWx2Text( TextCtrlSound->GetValue() ) );

    //fija los nuevos valores en la consola...
    SetValue( m_ValueDescriptor );


    LoadSound();
}

