#ifndef PREVIEWWINDOWSYSTEMMEM_H
#define PREVIEWWINDOWSYSTEMMEM_H

//(*Headers(PreviewWindowSystemMem)
#include <wx/panel.h>
//*)

#include  <wx/dcbuffer.h>
#include  <wx/image.h>




class PreviewWindowSystemMem: public wxPanel
{
	public:

		PreviewWindowSystemMem(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PreviewWindowSystemMem();

    wxImage*  pImage;
    wxBitmap*  pPattern;

		//(*Declarations(PreviewWindowSystemMem)
		//*)

	protected:

		//(*Identifiers(PreviewWindowSystemMem)
		//*)

	private:

		//(*Handlers(PreviewWindowSystemMem)
		void OnPaint(wxPaintEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

