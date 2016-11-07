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

#include "gst/gst.h"

#include "moldeodirector.h"



// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution(it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type(i.e. MyApp and
// not wxApp)
//(*AppHeaders
#include <wx/image.h>
#include <wx/config.h>
#include <wx/stdpaths.h>

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


    guint major, minor, micro, nano;
    cout << "Gstreamer initializing..." << endl;
    gst_init(NULL,NULL);
    gst_version (&major, &minor, &micro, &nano);
    cout << "Gstreamer initialized" << " version: " << major << "." << minor << "." << micro << "." << nano << endl;


    //** SET WORKING PATH CORRECTLY **/
    #if wxMAJOR_VERSION<3
    wxStandardPaths StdPaths;
    #else
	wxStandardPaths StdPaths = wxStandardPaths::Get();
	#endif

	wxFileName exename(StdPaths.GetExecutablePath());
	exename.MakeAbsolute();

    //wxMessageBox(wxString("appdir:")+wxString(exename.GetPath()));
    wxSetWorkingDirectory( wxString(exename.GetPath()) );

    //** EVERYTHING OK!!!**//




	moDirectorCore*			m_pDirectorCore = NULL;
	moDirectorFrame*		m_pDirectorFrame = NULL;

	SetAppName(wxString(_("Moldeo Director "))  + moText2Wx(moGetVersionStr()) );

// Check only one instance running

  m_checker = NULL;
/*
	const wxString name = wxString::Format(wxT("MoldeoDirector-%s"),
            wxGetUserId().c_str()); // Use mb_str()
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
		m_pDirectorFrame = new moDirectorFrame(wxString(_("Moldeo Director "))  + moText2Wx(moGetVersionStr()));
		if (m_pDirectorFrame) {
			m_pDirectorFrame->SetIcon( wxIcon( wxIconLocation(wxT(MOLDEODATADIR "/icons/Moldeo32.ico")) ) );
    	m_pDirectorFrame->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));
	    m_pDirectorFrame->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
		} else {
			exit(1);
		}
    cout << "m_pDirectorFrame:" << (m_pDirectorFrame!=NULL) << endl;

    cout << "Director Core..." << endl;
	m_pDirectorCore = new moDirectorCore();
	cout << "m_pDirectorCore:" << (m_pDirectorCore!=NULL) << endl;

	cout << "Director Frame UI to Core..." << endl;
	m_pDirectorCore->SetUserInterface( m_pDirectorFrame );



	m_pDirectorCore->SetPaths(  moWx2Text(exename.GetPath()),
                                moWx2Text(StdPaths.GetUserDataDir()),
                                moWx2Text(wxString(wxT(MODULESDIR))),
                                moWx2Text(wxString(wxT(MOLDEODATADIR)))
                                );
	m_pDirectorCore->Init();



   //wxList   ImageHandlerList = wxImage::GetHandlers();
   cout << "appdir:" << moWx2Text( wxGetCwd() ) << endl;
   cout << "userdir:" << moWx2Text( StdPaths.GetUserDataDir() ) << endl;
   cout << "datadir:" << moWx2Text(wxString(_(MOLDEODATADIR))) << endl;
   cout << "modulesdir:" << moWx2Text(wxString(_(MODULESDIR))) << endl;

   cout << "Showing Frame..." << endl;
   m_pDirectorFrame->Show(true);
   cout << "Setting Top Window..." << endl;
   SetTopWindow(m_pDirectorFrame);

	m_pDirectorFrame->Maximize();
	m_pDirectorFrame->Init();
    cout << "Success!!! rock and roll!!" << endl;

    moText config;

    cout << "argc: " << argc << endl;

    /*minimo 2*/
   	while( argc >= 2 ) {
		--argc;

        wxString  arglast(argv[argc]);
        wxString  argprev;

        if (argc>0) argprev = argv[argc-1];

        wxString  arg0(argv[0]);

		cout <<  "Argument id" << (argc) << " : " << moWx2Text(arglast) << endl;

		if( argprev == wxString( _("-mol") ) )  {
		    config = moWx2Text( arglast );
		    cout << "Argument -mol found! : " << config << endl;
			--argc;
        } else if (  arglast == wxString(_("--help")) ) {
            cout << "Usage: " << moWx2Text(arg0) << " [-mol]" << endl;
		} else {
			cout << "Usage: " << moWx2Text(arg0) << " [-mol]" << endl;

			/*wxMessageBox(   wxString(wxT("Error opening:")) +
                            wxString(wxT(" argc:")) + // wxString(IntToStr(argc)) +
                            wxString(wxT(" argv[argc-1]:")) + argv[argc-1] +
                            wxString(wxT(" argv[0]:")) + wxString(argv[0]) +
                            wxString(wxT(" argv[1]:")) + wxString(argv[1]) +
                            wxString(wxT(" argv[2]:")) + wxString(argv[2]) );
            */


			//exit(0);
		}
    }


    if (config!=moText("")) {
        moProjectDescriptor ProjectDescriptor;
        wxFileName	FileName( moText2Wx(config) );
        wxString path = FileName.GetPath();
        #ifdef MO_WIN32
            path+= _T("\\");
        #else
            path+= _T("/");
        #endif
        wxString name = FileName.GetFullName();
        ProjectDescriptor.Set( moWx2Text(path), moWx2Text(name) );
        moDirectorStatus mStatus = m_pDirectorFrame->OpenProject( ProjectDescriptor );
    }



    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

int moDirectorApp::OnExit() {
    if (m_checker) {
      delete m_checker;
      m_checker = NULL;
    }
    return 0;
}

