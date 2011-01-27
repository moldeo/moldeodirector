#include "moEffectsPaletteCtrl.h"



moEffectsPaletteCtrl::moEffectsPaletteCtrl( wxWindow* parent, wxWindowID id ) :
wxGrid( parent, id ) {



}


moEffectsPaletteCtrl::~moEffectsPaletteCtrl() {


}


moDirectorStatus
moEffectsPaletteCtrl::ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor ) {

  ///actualizar paleta? si se cambio de proyecto??... mmm no

  return MO_DIRECTOR_STATUS_OK;

}
