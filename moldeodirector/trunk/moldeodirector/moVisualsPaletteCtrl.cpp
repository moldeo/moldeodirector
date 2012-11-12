#include "moVisualsPaletteCtrl.h"

moVisualsPaletteCtrl::moVisualsPaletteCtrl( wxWindow* parent, wxWindowID id ) :
wxGrid( parent, id ) {



}


moVisualsPaletteCtrl::~moVisualsPaletteCtrl() {


}


moDirectorStatus
moVisualsPaletteCtrl::ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor ) {

  ///actualizar paleta? si se cambio de proyecto??... mmm no

  return MO_DIRECTOR_STATUS_OK;

}

