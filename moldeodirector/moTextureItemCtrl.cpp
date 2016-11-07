#include "moTextureItemCtrl.h"

//(*InternalHeaders(moTextureItemCtrl)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(moTextureItemCtrl)
const long moTextureItemCtrl::ID_STATICBITMAPTHUMB = wxNewId();
const long moTextureItemCtrl::ID_PANELITEM = wxNewId();
const long moTextureItemCtrl::ID_STATICTEXTNAME = wxNewId();
const long moTextureItemCtrl::ID_STATICTEXTSIZE = wxNewId();
//*)

BEGIN_EVENT_TABLE(moTextureItemCtrl,wxPanel)
	//(*EventTable(moTextureItemCtrl)
	//*)
	EVT_MOUSE_EVENTS(moTextureItemCtrl::OnMouseEnter)
END_EVENT_TABLE()

moTextureItemCtrl::moTextureItemCtrl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moTextureItemCtrl)
	Create(parent, id, wxPoint(0,0), wxSize(386,64), wxTAB_TRAVERSAL, _T("id"));
	SetForegroundColour(wxColour(255,255,0));
	SetBackgroundColour(wxColour(0,0,0));
	PanelItem = new wxPanel(this, ID_PANELITEM, wxPoint(0,0), wxSize(64,64), wxTAB_TRAVERSAL, _T("ID_PANELITEM"));
	PanelItem->SetBackgroundColour(wxColour(0,0,0));
	StaticBitmapThumb = new wxStaticBitmap(PanelItem, ID_STATICBITMAPTHUMB, wxBitmap(wxImage(_T( MOLDEODATADIR"/icons/imageempty.png")).Rescale(wxSize(64,44).GetWidth(),wxSize(64,44).GetHeight())), wxPoint(0,0), wxSize(64,44), 0, _T("ID_STATICBITMAPTHUMB"));
	StaticTextName = new wxStaticText(this, ID_STATICTEXTNAME, _("Name:"), wxPoint(72,0), wxDefaultSize, 0, _T("ID_STATICTEXTNAME"));
	StaticTextName->SetForegroundColour(wxColour(255,255,0));
	wxFont StaticTextNameFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticTextName->SetFont(StaticTextNameFont);
	StaticTextSize = new wxStaticText(this, ID_STATICTEXTSIZE, _("Size:"), wxPoint(72,16), wxDefaultSize, 0, _T("ID_STATICTEXTSIZE"));
	StaticTextSize->SetForegroundColour(wxColour(255,255,0));
	wxFont StaticTextSizeFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticTextSize->SetFont(StaticTextSizeFont);

	PanelItem->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&moTextureItemCtrl::OnMouseEnter,0,this);
	Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&moTextureItemCtrl::OnSetFocus);
	//*)

}

moTextureItemCtrl::~moTextureItemCtrl()
{
	//(*Destroy(moTextureItemCtrl)
	//*)
}


void moTextureItemCtrl::Init( moTextureDescriptor pTextureDescriptor, const wxBitmap& bitmap ) {

    StaticBitmapThumb->SetBitmap( bitmap );
    StaticBitmapThumb->SetSize( 0, 0, 64, 64);
    StaticTextName->SetLabel( wxString(wxT("Name: "))+ moText2Wx( pTextureDescriptor.GetResourceDefinition().GetName() ) );
    StaticTextSize->SetLabel( wxString(wxT("Size: ")) + moText2Wx( IntToStr(pTextureDescriptor.GetWidth())) +
                              wxString(wxT(" X ")) + moText2Wx( IntToStr(pTextureDescriptor.GetHeight())) );



}

void moTextureItemCtrl::OnSetFocus(wxFocusEvent& event)
{
       wxMessageBox( _T("Killed focus on:") + StaticTextName->GetLabel());
       event.Skip();
}

void moTextureItemCtrl::OnMouseEnter(wxMouseEvent& event)
{

    if ( event.Button(wxMOUSE_BTN_LEFT) || event.ButtonDown() ) {
        #if wxMAJOR_VERSION<3
        GetParent()->ProcessEvent(event);
        #else
        #endif
    }
    event.Skip();
}

void moTextureItemCtrl::Focus( bool focuson ) {
    if (focuson) {
        m_bSelected = true;
        /*StaticTextName->SetForegroundColour( wxColour(240,240,240) );
        StaticTextName->SetBackgroundColour( wxColour(80,80,80) );
        StaticTextSize->SetForegroundColour( wxColour(240,240,240) );
        StaticTextSize->SetBackgroundColour( wxColour(80,80,80) );
        this->SetBackgroundColour( wxColour(80,80,80) );*/
        Refresh();
    } else {
        m_bSelected = false;
        /*StaticTextName->SetForegroundColour( wxColour(80,80,80) );
        StaticTextName->SetBackgroundColour( wxColour(240,240,240) );
        StaticTextSize->SetForegroundColour( wxColour(80,80,80) );
        StaticTextSize->SetBackgroundColour( wxColour(240,240,240) );
        this->SetBackgroundColour( wxColour(240,240,240) );*/
        Refresh();
    }
}
