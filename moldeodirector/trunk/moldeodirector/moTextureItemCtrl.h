#ifndef MOTEXTUREITEMCTRL_H
#define MOTEXTUREITEMCTRL_H

#include "moIDirectorActions.h"

//(*Headers(moTextureItemCtrl)
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
//*)

class moTextureItemCtrl: public wxPanel
{
	public:

		moTextureItemCtrl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moTextureItemCtrl();

		void Init( moTextureDescriptor pTextureDescriptor, const wxBitmap& bitmap );


		//(*Declarations(moTextureItemCtrl)
		wxStaticText* StaticTextSize;
		wxPanel* PanelItem;
		wxStaticText* StaticTextName;
		wxStaticBitmap* StaticBitmapThumb;
		//*)

		bool m_bSelected;
		void Focus( bool focuson = true );


	protected:

		//(*Identifiers(moTextureItemCtrl)
		static const long ID_STATICBITMAPTHUMB;
		static const long ID_PANELITEM;
		static const long ID_STATICTEXTNAME;
		static const long ID_STATICTEXTSIZE;
		//*)

	private:

		//(*Handlers(moTextureItemCtrl)
		void OnSetFocus(wxFocusEvent& event);
		void OnMouseEnter(wxMouseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
