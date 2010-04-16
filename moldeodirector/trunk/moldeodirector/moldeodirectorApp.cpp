/***************************************************************
 * Name:      testwxApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2008-11-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "moldeodirectorApp.h"


#include "moDirectorFrame.h"

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(moldeodirectorApp);

bool moldeodirectorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    //*)

    if ( wxsOK )
    {
    	//testwxFrame* Frame = new testwxFrame(0);
    	//Frame->Show();
    	//SetTopWindow(Frame);
	moDirectorCore*			m_pDirectorCore = NULL;
	moDirectorFrame*		m_pDirectorFrame = NULL;

    m_pDirectorFrame = new moDirectorFrame(_T("Moldeo Director"));
    m_pDirectorFrame->SetIcon( wxIcon( wxIconLocation(wxT("../../art/icons/Moldeo32.ico")) ) );
    m_pDirectorFrame->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));
    m_pDirectorFrame->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));


    cout << "Director Core..." << endl;
	m_pDirectorCore = new moDirectorCore();
	cout << "m_pDirectorCore:" << (m_pDirectorCore!=NULL) << endl;

	cout << "Director Frame UI to Core..." << endl;
	m_pDirectorCore->SetUserInterface( m_pDirectorFrame );

	wxStandardPaths StdPaths;

	wxFileName exename(StdPaths.GetExecutablePath());
	//exename = StdPaths.GetDataDir();
	//moWx2Text(exename.GetPath())
	exename.MakeAbsolute();

	//wxFileName userdatadir( StdPaths.GetUserDataDir() );

	m_pDirectorCore->SetPaths( moFileManager::GetWorkPath() );
	m_pDirectorCore->Init();



   //wxList   ImageHandlerList = wxImage::GetHandlers();


   cout << "Showing Frame..." << endl;
   m_pDirectorFrame->Show(true);
   cout << "Setting Top Window..." << endl;
   SetTopWindow(m_pDirectorFrame);

	m_pDirectorFrame->Init();
    cout << "Success!!! rock and roll!!" << endl;

    }

    return wxsOK;

}
