#include "moFontPanel.h"

//(*InternalHeaders(moFontPanel)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moFontPanel)
const long moFontPanel::ID_TEXTCTRL1 = wxNewId();
const long moFontPanel::ID_BITMAPBUTTONIMPORT = wxNewId();
//*)

BEGIN_EVENT_TABLE(moFontPanel,wxPanel)
	//(*EventTable(moFontPanel)
	//*)
END_EVENT_TABLE()

moFontPanel::moFontPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moFontPanel)
	Create(parent, id, wxDefaultPosition, wxSize(246,257), wxTAB_TRAVERSAL, _T("id"));
	TextCtrlFont = new wxTextCtrl(this, ID_TEXTCTRL1, _("sample"), wxPoint(8,8), wxSize(144,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont TextCtrlFontFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	TextCtrlFont->SetFont(TextCtrlFontFont);
	BitmapButtonImport = new wxBitmapButton(this, ID_BITMAPBUTTONIMPORT, wxBitmap(wxImage(_T("../../data/icons/import.png"))), wxPoint(160,16), wxSize(13,13), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONIMPORT"));
	BitmapButtonImport->SetDefault();
	
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moFontPanel::OnTextCtrlFontText);
	Connect(ID_BITMAPBUTTONIMPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moFontPanel::OnBitmapButton1Click);
	//*)
}

moFontPanel::~moFontPanel()
{
	//(*Destroy(moFontPanel)
	//*)
}


void moFontPanel::OnBitmapButton1Click(wxCommandEvent& event)
{



}

void moFontPanel::OnTextCtrlFontText(wxCommandEvent& event)
{
}
