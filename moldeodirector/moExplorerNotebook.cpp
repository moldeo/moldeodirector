#include "moExplorerNotebook.h"

BEGIN_EVENT_TABLE( moExplorerNotebook, wxAuiNotebook )

END_EVENT_TABLE()


moExplorerNotebook::moExplorerNotebook( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) :
		wxAuiNotebook(parent, id, wxPoint(0,0), wxSize(100,100),  wxBORDER_NONE | wxNO_BORDER |  wxAUI_NB_SCROLL_BUTTONS ),
		m_pVisualsPaletteCtrl(NULL),
		m_pProjectTreeCtrl(NULL),
		m_pEffectsPaletteCtrl(NULL),
		m_pFilesTreeCtrl(NULL)
		 {

    SetArtProvider( new wxMoAuiTabArt() );

    wxColour m_cForeground(255,255,255);
    wxColour m_cBackground(0,0,0);

    ///arbol de la configuracion del proyecto
		m_pProjectTreeCtrl = new moProjectTreeCtrl( this, wxID_ANY, wxPoint(0,0), wxSize(300,377), wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE);
		if (m_pProjectTreeCtrl) {
      m_pProjectTreeCtrl->SetNextActionHandler( this );
      m_pProjectTreeCtrl->SetForegroundColour(m_cForeground);
      m_pProjectTreeCtrl->SetBackgroundColour(m_cBackground);
      if ( AddPage( m_pProjectTreeCtrl, wxT("Project") ) ) {
        SetPageBitmap( GetPageIndex( m_pProjectTreeCtrl ), wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/ontology_16.png"))) );
      }
		}

		/// paleta de efectos para agregar
		//m_pEffectsPaletteCtrl = new moEffectsPaletteCtrl( this, wxID_ANY );
		if (m_pEffectsPaletteCtrl) {
      m_pEffectsPaletteCtrl->SetNextActionHandler( this );
      m_pEffectsPaletteCtrl->SetForegroundColour(m_cForeground);
      m_pEffectsPaletteCtrl->SetBackgroundColour(m_cBackground);

      if (AddPage( m_pEffectsPaletteCtrl, wxT("FX Palette") ) ) {
        SetPageBitmap( GetPageIndex( m_pEffectsPaletteCtrl ), wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/rdf_16.png"))) );
      }
		}

		///visuales ( texturas, videos, animados, bufferes circulares, etc... )
		//m_pVisualsPaletteCtrl = new moVisualsPaletteCtrl(this, wxID_ANY );
		if (m_pVisualsPaletteCtrl) {
      m_pVisualsPaletteCtrl->SetNextActionHandler( this );
      m_pVisualsPaletteCtrl->SetForegroundColour(m_cForeground);
      m_pVisualsPaletteCtrl->SetBackgroundColour(m_cBackground);

      if (AddPage( m_pVisualsPaletteCtrl, wxT("Visuals") ) ) {
        SetPageBitmap( GetPageIndex( m_pVisualsPaletteCtrl ), wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/image_16.png"))) );
      }

		}

		///arbol de archivos en el directorio de datos
		m_pFilesTreeCtrl = new wxVirtualDirTreeCtrl( this, wxID_ANY, wxPoint(0,0), wxSize(300,377),wxTR_DEFAULT_STYLE | wxNO_BORDER | wxBORDER_NONE );
		if (m_pFilesTreeCtrl) {
		  m_pFilesTreeCtrl->SetForegroundColour(m_cForeground);
		  m_pFilesTreeCtrl->SetBackgroundColour(m_cBackground);
		  if (AddPage( m_pFilesTreeCtrl, wxT("Files") ) ) {
        SetPageBitmap( GetPageIndex( m_pFilesTreeCtrl ), wxBitmap(wxImage(_T(MOLDEODATADIR "/icons/folder_sans_16.png"))) );
		  }
		}

}

moDirectorStatus
moExplorerNotebook::ValueUpdated( moValueDescriptor p_ValueDesc ) {

  return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moExplorerNotebook::MobUpdated( moMobDescriptor p_MobDesc ) {

  if (m_pProjectTreeCtrl) m_pProjectTreeCtrl->MobUpdated(p_MobDesc);
  //if (m_pFilesTreeCtrl) m_pFilesTreeCtrl->MobUpdated(p_MobDesc);
  //if (m_pEffectsPaletteCtrl) m_pEffectsPaletteCtrl->MobUpdated(p_MobDesc);

  return MO_DIRECTOR_STATUS_OK;

}

moDirectorStatus
moExplorerNotebook::ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor ) {

  int layer_height = 64;
  wxString cPath;
  moDirectorStatus status = MO_DIRECTOR_STATUS_FALSE;

  ///pedimos todos los descriptores:
  cPath = moText2Wx( p_ProjectDescriptor.GetConfigPath() );

  ///actualizamos el arbol
  if (m_pProjectTreeCtrl)
    status = m_pProjectTreeCtrl->ProjectUpdated( p_ProjectDescriptor );

  ///actualizamos las paletas de efectos
  if (m_pEffectsPaletteCtrl)
    status = CHECK_DIRECTOR_STATUS_ERROR( status, m_pEffectsPaletteCtrl->ProjectUpdated( p_ProjectDescriptor ) );

  ///actualizamos la paleta de visuales
  if (m_pVisualsPaletteCtrl)
    status = CHECK_DIRECTOR_STATUS_ERROR( status, m_pVisualsPaletteCtrl->ProjectUpdated( p_ProjectDescriptor ) );


  ///actualizamos el arbol de archivos
  if (m_pFilesTreeCtrl)
    status = CHECK_DIRECTOR_STATUS_ERROR( status, m_pFilesTreeCtrl->SetRootPath( cPath, wxVDTC_DEFAULT) );


  return status;
}


