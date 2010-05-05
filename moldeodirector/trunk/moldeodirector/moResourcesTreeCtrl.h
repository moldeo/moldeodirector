#ifndef MO_RESOURCESTREECTRL_H
#define MO_RESOURCESTREECTRL_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include "wxTreeMultiCtrl.h"
#include "moShaderCtrl.h"
#include "moTextureItemCtrl.h"
#include <wx/imaglist.h>


class moResourcesTreeCtrl : public wxTreeMultiCtrl, public moIDirectorActions {

    public:
        moResourcesTreeCtrl( wxWindow* window, wxWindowID id);
        virtual ~moResourcesTreeCtrl();


        void InitDescriptors();
        void UpdateDescriptors();


    public:

        wxTreeMultiItem imgid;
        wxTreeMultiItem videosid;
        wxTreeMultiItem othersid;
        wxBitmap EmptyBitmap;

        wxImageList         m_ImageList;
        moResourceDescriptors    m_ResourceDescriptors;

    DECLARE_EVENT_TABLE()

};



#endif
