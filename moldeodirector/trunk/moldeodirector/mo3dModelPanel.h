#ifndef MO3DMODELPANEL_H
#define MO3DMODELPANEL_H

#include "moIDirectorActions.h"

//(*Headers(mo3dModelPanel)
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

class mo3dModelPanel: public wxPanel, public moIDirectorActions
{
	public:

		mo3dModelPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~mo3dModelPanel();

        void Inspect( moValueDescriptor p_ValueDescriptor );

        void    Init3dModelsTree();

		//(*Declarations(mo3dModelPanel)
		wxListCtrl* ListCtrl3dModel;
		wxButton* ButtonImport;
		wxPanel* Panel3dModel;
		wxTextCtrl* TextCtrl3dModel;
		//*)

	protected:

		//(*Identifiers(mo3dModelPanel)
		static const long ID_TEXTCTRL3DMODEL;
		static const long ID_BUTTONIMPORT;
		static const long ID_PANEL3DMODEL;
		static const long ID_LISTCTRL3DMODEL;
		//*)

	private:

		//(*Handlers(mo3dModelPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
