/////////////////////////////////////////////////////////////////////////////
// Name:        moldeodirector.cpp
// Author:      Fabricio Costa Alisedo
// Modified by:
// Created:     02/03/2006
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "moldeodirector.h"



// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution(it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type(i.e. MyApp and
// not wxApp)
//(*AppHeaders
#include <wx/image.h>
#include <wx/config.h>

//*)

IMPLEMENT_APP(moDirectorApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool moDirectorApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	//*)
	wxInitAllImageHandlers();
//  Check next line: Gustavo 05/20/2009
//	return wxsOK;



    //** SET WORKING PATH CORRECTLY **/
	wxStandardPaths StdPaths;

	wxFileName exename(StdPaths.GetExecutablePath());
	exename.MakeAbsolute();

    wxMessageBox(wxString(exename.GetPath()));
    wxSetWorkingDirectory( wxString(exename.GetPath()) );

    //** EVERYTHING OK!!!**//




	moDirectorCore*			m_pDirectorCore = NULL;
	moDirectorFrame*		m_pDirectorFrame = NULL;

	SetAppName("Moldeo Director");

// Check only one instance running

/*
	const wxString name = wxString::Format(wxT("MoldeoDirector-%s"),
            wxGetUserId().c_str());
    m_checker = new wxSingleInstanceChecker(name);
    if (m_checker->IsAnotherRunning())
        {
            wxLogError(_("Program already running, aborting."));
            return false;
        }
*/


    // Check configuration file
    /*
    wxString str;
    wxFileConfig configuration(wxT("MoldeoDirector"),wxT("Moldeo"),wxT(wxGetCwd()));

    configuration.Read(wxT("General/File1"), &str);
    wxMessageBox(wxT(str),wxT("Moldeo Director"));
    */
    // created initially)
   cout << "Image Handlers..." << endl;
#if wxUSE_SYSTEM_OPTIONS
    //wxSystemOptions::SetOption(wxT("no-maskblt"), 1);
#endif

    wxInitAllImageHandlers();
#if wxUSE_FS_INET && wxUSE_STREAMS && wxUSE_SOCKETS
    //wxFileSystem::AddHandler(new wxInternetFSHandler);
#endif

   wxImageHandler* hndPNG = wxImage::FindHandler((long)wxBITMAP_TYPE_PNG);
   if (!hndPNG)
    cout << "Warning: PNG Image handler not loaded..." << endl;

   wxImageHandler* hndJPEG = wxImage::FindHandler((long)wxBITMAP_TYPE_JPEG);
   if (!hndJPEG)
    cout << "Warning: JPEG Image handler not loaded..." << endl;

   wxImageHandler* hndTGA = wxImage::FindHandler((long)wxBITMAP_TYPE_TGA);
   if (!hndTGA)
    cout << "Warning: TGA Image handler not loaded..." << endl;

    // create the main application window

    cout << "Director Frame..." << endl;
    m_pDirectorFrame = new moDirectorFrame(_T("Moldeo Director"));
    m_pDirectorFrame->SetIcon( wxIcon( wxIconLocation(wxT("../../art/icons/Moldeo32.ico")) ) );
    m_pDirectorFrame->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));
    m_pDirectorFrame->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
    cout << "m_pDirectorFrame:" << (m_pDirectorFrame!=NULL) << endl;

    cout << "Director Core..." << endl;
	m_pDirectorCore = new moDirectorCore();
	cout << "m_pDirectorCore:" << (m_pDirectorCore!=NULL) << endl;

	cout << "Director Frame UI to Core..." << endl;
	m_pDirectorCore->SetUserInterface( m_pDirectorFrame );


    //wxMessageBox(StdPaths.GetAppDir());

	//wxFileName userdatadir( StdPaths.GetUserDataDir() );

	m_pDirectorCore->SetPaths( moWx2Text(exename.GetPath()) );
	m_pDirectorCore->Init();



   //wxList   ImageHandlerList = wxImage::GetHandlers();


   cout << "Showing Frame..." << endl;
   m_pDirectorFrame->Show(true);
   cout << "Setting Top Window..." << endl;
   SetTopWindow(m_pDirectorFrame);

	m_pDirectorFrame->Maximize();
	m_pDirectorFrame->Init();
    cout << "Success!!! rock and roll!!" << endl;

    moText config;

   	while( argc > 1 ) {
		--argc;
		if( argv[argc-1] &&(strcmp(argv[argc-1], "-mol") == 0) ) {
			config = argv[argc];
			--argc;
		} else {
			printf( "Usage: %s [-mol]\n", argv[0]);

			wxMessageBox(   wxString("Error opening:") +
                            wxString(" argc:") + wxString(IntToStr(argc)) +
                            wxString(" argv[argc-1]:") + argv[argc-1] +
                            wxString(" argv[0]:") + wxString(argv[0]) +
                            wxString(" argv[1]:") + wxString(argv[1]) +
                            wxString(" argv[2]:") + wxString(argv[2]) );


			exit(0);
		}
    }


    if (config!=moText("")) {
        moProjectDescriptor ProjectDescriptor;

        wxFileName	FileName( moText2Wx(config) );

        wxString path = FileName.GetPath();
        #ifdef MO_WIN32
            path+= "\\";
        #else
            path+= _T("/");
        #endif
        wxString name = FileName.GetFullName();
        const char *cfilepath = (char*)path.c_str();
        const char *cfilename = (char*)name.c_str();

        ProjectDescriptor.Set( moText((char*)cfilepath), moText((char*)cfilename) );

        moDirectorStatus mStatus = m_pDirectorFrame->OpenProject( ProjectDescriptor );


    }



    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

int moDirectorApp::OnExit() {
    delete m_checker;
    return 0;
}
