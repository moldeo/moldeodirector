/***************************************************************
 * Name:      testwxMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2008-11-24
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TESTWXMAIN_H
#define TESTWXMAIN_H

#include "moIDirectorActions.h"


//(*Headers(testwxFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/slider.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class testwxFrame: public wxFrame
{
    public:

        testwxFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~testwxFrame();

    private:

        //(*Handlers(testwxFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(testwxFrame)
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(testwxFrame)
        wxSlider* Slider1;
        wxStaticText* StaticText1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TESTWXMAIN_H
