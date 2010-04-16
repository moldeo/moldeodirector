#ifndef MOFONTPANEL_H
#define MOFONTPANEL_H

//(*Headers(moFontPanel)
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

class moFontPanel: public wxPanel
{
	public:

		moFontPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moFontPanel();

		//(*Declarations(moFontPanel)
		wxTextCtrl* TextCtrlFont;
		wxBitmapButton* BitmapButtonImport;
		//*)

	protected:

		//(*Identifiers(moFontPanel)
		static const long ID_TEXTCTRL1;
		static const long ID_BITMAPBUTTONIMPORT;
		//*)

	private:

		//(*Handlers(moFontPanel)
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnTextCtrlFontText(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
