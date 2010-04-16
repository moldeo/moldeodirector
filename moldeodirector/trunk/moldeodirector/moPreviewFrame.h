#ifndef MOPREVIEWFRAME_H
#define MOPREVIEWFRAME_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"


//(*Headers(moPreviewFrame)
#include <wx/toolbar.h>
#include <wx/frame.h>
//*)

class moGLCanvas;

class moPreviewFrame: public wxFrame, public moIDirectorActions
{
	public:

		moPreviewFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moPreviewFrame();

		//(*Declarations(moPreviewFrame)
		wxToolBar* ToolBar1;
		wxToolBarToolBase* ToolBarItem3;
		wxToolBarToolBase* ToolBarItem1;
		wxToolBarToolBase* ToolBarItem2;
		//*)

		moGLCanvas* m_pGLCanvas;

		void Init( moIDirectorActions* pActionsHandler, wxGLContext* p_pGLContext );

    public:
        moDirectorStatus FullScreen(bool force=false);

	protected:

		//(*Identifiers(moPreviewFrame)
		static const long TOOLPLAY;
		static const long TOOLPAUSE;
		static const long TOOLFULLSCREEN;
		static const long ID_TOOLBAR1;
		//*)

	private:

		//(*Handlers(moPreviewFrame)
		void OnClose(wxCloseEvent& event);
		//*)
		void OnToolClick( wxCommandEvent &event);
		//void OnSize(wxSizeEvent& event);

		DECLARE_EVENT_TABLE()
};

#include "moGLCanvas.h"

#endif
