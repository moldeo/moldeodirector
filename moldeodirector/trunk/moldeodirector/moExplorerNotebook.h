#ifndef MOEXPLORERNOTEBOOK_H_INCLUDED
#define MOEXPLORERNOTEBOOK_H_INCLUDED

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

#include <wx/aui/auibook.h>
#include "virtualdirtreectrl.h"

#include "moProjectTreeCtrl.h"
#include "moEffectsPaletteCtrl.h"
#include "moVisualsPaletteCtrl.h"

class moExplorerNotebook : public wxAuiNotebook, public moIDirectorActions  {

	public:

		moExplorerNotebook( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
		virtual ~moExplorerNotebook() {}

  public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );

  private:

    moProjectTreeCtrl*      m_pProjectTreeCtrl;

    moVisualsPaletteCtrl*   m_pVisualsPaletteCtrl;
    moEffectsPaletteCtrl*   m_pEffectsPaletteCtrl;

    wxVirtualDirTreeCtrl*   m_pFilesTreeCtrl;

  public:
    DECLARE_EVENT_TABLE()
};


#endif // MOEXPLORERNOTEBOOK_H_INCLUDED
