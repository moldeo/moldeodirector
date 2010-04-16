#ifndef HTMLPANEL_H
#define HTMLPANEL_H

//(*Headers(HtmlPanel)
#include <wx/panel.h>
#include <wx/html/htmlwin.h>
//*)

class HtmlPanel: public wxPanel
{
	public:

		HtmlPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HtmlPanel();

		//(*Declarations(HtmlPanel)
		wxHtmlWindow* HtmlWindow1;
		//*)

	protected:

		//(*Identifiers(HtmlPanel)
		static const long ID_HTMLWINDOW1;
		//*)

	private:

		//(*Handlers(HtmlPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
