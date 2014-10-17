#include "HtmlPanel.h"

//(*InternalHeaders(HtmlPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HtmlPanel)
const long HtmlPanel::ID_HTMLWINDOW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HtmlPanel,wxPanel)
	//(*EventTable(HtmlPanel)
	//*)
END_EVENT_TABLE()

HtmlPanel::HtmlPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(HtmlPanel)
	Create(parent, id, wxDefaultPosition, wxSize(673,255), wxTAB_TRAVERSAL, _T("id"));
	HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxPoint(16,8), wxSize(568,208), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetPage(_("Hola Mundo"));
	//*)
}

HtmlPanel::~HtmlPanel()
{
	//(*Destroy(HtmlPanel)
	//*)
}

