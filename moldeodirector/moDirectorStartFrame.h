/*******************************************************************************

                                moDirectorStartFrame.h

  ****************************************************************************
  *                                                                          *
  *   This source is free software; you can redistribute it and/or modify    *
  *   it under the terms of the GNU General Public License as published by   *
  *   the Free Software Foundation; either version 2 of the License, or      *
  *  (at your option) any later version.                                    *
  *                                                                          *
  *   This code is distributed in the hope that it will be useful, but       *
  *   WITHOUT ANY WARRANTY; without even the implied warranty of             *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
  *   General Public License for more details.                               *
  *                                                                          *
  *   A copy of the GNU General Public License is available on the World     *
  *   Wide Web at <http://www.gnu.org/copyleft/gpl.html>. You can also       *
  *   obtain it by writing to the Free Software Foundation,                  *
  *   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         *
  *                                                                          *
  ****************************************************************************

  Copyright(C) 2006 Fabricio Costa

  Authors:
  Fabricio Costa

  Description:
	MDI child frame

*******************************************************************************/

#ifndef _MO_DIRECTOR_START_FRAME_
#define _MO_DIRECTOR_START_FRAME_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include "wx/sysopt.h"
#include "wx/html/htmlwin.h"
#include "wx/fs_inet.h"
#include <wx/html/htmlwin.h>
#include <wx/html/htmlcell.h>


/*

// Define a new html window type: this is a wrapper for handling wxHtmlWindow events
class MyHtmlWindow : public wxHtmlWindow
{
public:
    MyHtmlWindow(wxWindow *parent) : wxHtmlWindow( parent ) { }

    virtual wxHtmlOpeningStatus OnOpeningURL(wxHtmlURLType WXUNUSED(type),
                                             const wxString& WXUNUSED(url),
                                             wxString *WXUNUSED(redirect)) const;

private:
    void OnClipboardEvent(wxClipboardTextEvent& event);

#if wxUSE_CLIPBOARD
    DECLARE_EVENT_TABLE()
#endif // wxUSE_CLIPBOARD
    DECLARE_NO_COPY_CLASS(MyHtmlWindow)
};
*/
class moDirectorStartFrame : public wxScrolledWindow , public moIDirectorActions
{

    public:
        moDirectorStartFrame( wxWindow* parent);
        virtual ~moDirectorStartFrame();

        MOboolean Init( moIDirectorActions* pActions );
        MOboolean Finish();

        void OnLinkClicked(wxHtmlLinkEvent& event);
        void OnSize(wxSizeEvent& event);

        wxHtmlWindow*   m_pHtmlWindow;
        //MyHtmlWindow *m_Html;
        //wxHtmlProcessor *m_Processor;

        DECLARE_EVENT_TABLE()
};

#endif

