#include "PreviewWindowSystemMem.h"

//(*InternalHeaders(PreviewWindowSystemMem)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PreviewWindowSystemMem)
//*)

BEGIN_EVENT_TABLE(PreviewWindowSystemMem,wxPanel)
	//(*EventTable(PreviewWindowSystemMem)
	//*)
END_EVENT_TABLE()

PreviewWindowSystemMem::PreviewWindowSystemMem(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PreviewWindowSystemMem)
	Create(parent, id, wxDefaultPosition, wxSize(322,244), wxTAB_TRAVERSAL, _T("id"));

	Connect(wxID_ANY,wxEVT_PAINT,(wxObjectEventFunction)&PreviewWindowSystemMem::OnPaint);
	Connect(wxID_ANY,wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&PreviewWindowSystemMem::OnEraseBackground);
	//*)
	pImage = NULL;
}

PreviewWindowSystemMem::~PreviewWindowSystemMem()
{
	//(*Destroy(PreviewWindowSystemMem)
	//*)
}


void PreviewWindowSystemMem::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);


    wxImage copy1;

    int w, h;
    GetClientSize(&w, &h);

    /*if (m_Pattern.IsOk()) {
      UpdatePattern();
      dc.DrawBitmap( m_Pattern,  0, 0, true );
    }
    */

    //dc.SetClippingRegion(0,0,400,300);
    //dc.SetBrush( wxBrush( wxColour(80,0,0), wxSOLID) );
    //dc.DrawRectangle( 0, 0, 400, 300);

  if (pImage) {
      if (pImage->IsOk()) {
        //ImagePanel->SetBitmap( wxBitmap(*thumbImg) );
        //wxSize sz(320,240);
        //wxImage& copy( pImage->Resize( sz,wxPoint(0,0) ));

        wxImage& copy( pImage->Rescale( w, h ));
        //copy.Mirror( false );
        //wxImage* copy2 = copy1->Mirror(false);
        //dc.DrawBitmap( wxBitmap(*pImage),  0, 0, true );
        dc.DrawBitmap( wxBitmap(pImage->Mirror(false)),  0, 0, true );
      }

  }


}

void PreviewWindowSystemMem::OnEraseBackground(wxEraseEvent& event)
{
}
