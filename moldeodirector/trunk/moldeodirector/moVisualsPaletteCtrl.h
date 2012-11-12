#ifndef MOVISUALSPALETTECTRL_H_INCLUDED
#define MOVISUALSPALETTECTRL_H_INCLUDED


#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include <wx/grid.h>

class moVisualsPaletteCtrl : public moIDirectorActions, public wxGrid  {

  public:

    moVisualsPaletteCtrl( wxWindow* parent, wxWindowID id );
    virtual ~moVisualsPaletteCtrl();

  public:

        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );


};

#endif // MOVISUALSPALETTECTRL_H_INCLUDED

