#ifndef MOEFFECTSPALETTECTRL_H_INCLUDED
#define MOEFFECTSPALETTECTRL_H_INCLUDED

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include <wx/grid.h>

class moEffectsPaletteCtrl : public moIDirectorActions, public wxGrid  {

  public:

    moEffectsPaletteCtrl( wxWindow* parent, wxWindowID id );
    virtual ~moEffectsPaletteCtrl();

  public:

        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );


};



#endif // MOEFFECTSPALETTECTRL_H_INCLUDED

