#include "moLogNotebook.h"


moLogTextCtrl::moLogTextCtrl(wxWindow* parent, wxWindowID id) : wxTextCtrl(parent,id, wxT(""),
                          wxPoint(0,0), wxSize(500,90),
                          wxNO_BORDER | wxTE_MULTILINE | wxTE_RICH) {


}

moLogTextCtrl::~moLogTextCtrl() {

}


void moLogTextCtrl::Log( moText p_message ) {

    wxString  w = moText2Wx( p_message );

    ///cada 10000 lineas publicadas, limpia el buffer completo
    if (GetNumberOfLines()>10000) {
        Clear();
    }

    SetDefaultStyle( wxTextAttr( wxColour( 50, 255, 50 )) );
    AppendText(w + wxT("\n"));

    ShowPosition( GetLastPosition() );

}

void moLogTextCtrl::LogError( moText p_message ) {

    wxString  w = moText2Wx( p_message );

    if (GetNumberOfLines()>10000) {
        Clear();
    }

    SetDefaultStyle( wxTextAttr( wxColour(255,0,0) ) );
    AppendText(w + wxT("\n"));

    ShowPosition( GetLastPosition() );

}


///===================================================================================================

BEGIN_EVENT_TABLE( moLogNotebook, wxAuiNotebook )

END_EVENT_TABLE()

moLogNotebook::moLogNotebook( wxWindow* parent, wxWindowID id ) :
		wxAuiNotebook(parent, id, wxPoint(0,0), wxSize(100,100),  wxBORDER_NONE | wxNO_BORDER ),
		m_pLogBase(NULL),
		m_pLogError(NULL),
		m_pLogStdout(NULL)
		 {

    SetArtProvider( new wxMoAuiTabArt() );

    wxColour m_cBackground(0,0,0);

    ///caja de texto de registro de base
		m_pLogBase = new moLogTextCtrl( this, wxID_ANY );
		if (m_pLogBase) {
      m_pLogBase->SetNextActionHandler( this );
      m_pLogBase->SetBackgroundColour(m_cBackground);
      if ( AddPage( m_pLogBase, wxT("Log") ) ) {
        ///SetPageBitmap( GetPageIndex( m_pProjectTreeCtrl ), wxBitmap(wxImage(_T("../../art/icons/ontology_16.png"))) );
      }
		}

		/// caja de texto de errores
		m_pLogError = new moLogTextCtrl( this, wxID_ANY );
		if (m_pLogError) {
      m_pLogError->SetNextActionHandler( this );
      m_pLogError->SetBackgroundColour(m_cBackground);
      if ( AddPage( m_pLogError, wxT("Errors") ) ) {
        ///SetPageBitmap( GetPageIndex( m_pProjectTreeCtrl ), wxBitmap(wxImage(_T("../../art/icons/ontology_16.png"))) );
      }
		}

		/// caja de texto de salida estandar
		m_pLogStdout = new moLogTextCtrl( this, wxID_ANY );
		if (m_pLogStdout) {
      m_pLogStdout->SetNextActionHandler( this );
      m_pLogStdout->SetBackgroundColour(m_cBackground);
      if ( AddPage( m_pLogStdout, wxT("Standard Output") ) ) {
        ///SetPageBitmap( GetPageIndex( m_pProjectTreeCtrl ), wxBitmap(wxImage(_T("../../art/icons/ontology_16.png"))) );
      }
		}

}

void moLogNotebook::Log( moText p_message ) {

    if (m_pLogBase) {
      m_pLogBase->Log( p_message );
    }

}

void moLogNotebook::LogError( moText p_message ) {


    if (m_pLogBase) {
      m_pLogBase->LogError( p_message );
    }

    if (m_pLogError) {
      m_pLogError->LogError( p_message );
    }

    if (GetSelection()!=GetPageIndex(m_pLogError))
        SetSelection(GetPageIndex(m_pLogError));

}
