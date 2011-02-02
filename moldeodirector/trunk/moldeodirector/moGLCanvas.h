/*******************************************************************************

                                moGLCanvas.h

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
	OpenGL Canvas for rendering consoles

*******************************************************************************/
#ifndef _MO_GLCANVAS_
#define _MO_GLCANVAS_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "moDirectorConsole.h"
#include <wx/glcanvas.h>
#include <wx/timer.h>


class moGLCanvas: public wxGLCanvas, public moIDirectorActions
{
public:

    moGLCanvas(wxWindow *parent,
        wxWindowID id = wxID_ANY,
        int* attribList = 0,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = wxT("TestGLCanvas"));

    moGLCanvas(wxWindow *parent,
        wxGLContext*    p_pGLContext,
        wxWindowID id = wxID_ANY,
        int* attribList = 0,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = wxT("TestGLCanvas"));

    moGLCanvas(wxWindow *parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = wxT("TestGLCanvas"));

    ~moGLCanvas();

	moGLCanvas*		Init( moIDirectorActions* pActionsHandler );
	void            Activate( wxEvtHandler* p_pHandler );


	MOboolean Finish();

	void Reset();

	void OnTimer(wxTimerEvent& event);

    void OnPaint(wxPaintEvent& event);
	void OnClose(wxCloseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    //void LoadLWO( const wxString &filename);
    void OnMouse( wxMouseEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	void OnKeyUp( wxKeyEvent& event );

    bool       block;

//MOIDRECTORACTIONS

    void ViewSwapBuffers( int glidprev = 0 );
    MO_HANDLE   GetHandle();

private:

	wxEvtHandler*		m_pHandler;

	bool   m_init;
	bool    m_active;
	wxTimer m_timer;

    DECLARE_EVENT_TABLE()
};
#endif
