#ifndef MOSHADERSPANEL_H
#define MOSHADERSPANEL_H

#include "moIDirectorActions.h"

#include "wxTreeMultiCtrl.h"

#include "moShaderCtrl.h"

//(*Headers(moShadersPanel)
#include <wx/listctrl.h>
#include <wx/panel.h>
//*)

class moShadersPanel: public wxPanel, public moIDirectorActions
{
	public:

		moShadersPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moShadersPanel();

        void    Inspect( moValueDescriptor p_ValueDescriptor );
        void    Inspect( moParameterDescriptor p_ParamDescriptor );

        void    InitShadersTree();

        moParameterDescriptor   m_ParamDescriptor;

		//(*Declarations(moShadersPanel)
		wxListCtrl* ListCtrlShaders;
		wxListCtrl* ListCtrlFilters;
		//*)

	protected:

        wxTreeMultiCtrl*   m_pTreeFiltersCtrl;

		//(*Identifiers(moShadersPanel)
		static const long ID_LISTCTRL1;
		static const long ID_LISTCTRLFILTERS;
		//*)

	private:

		//(*Handlers(moShadersPanel)
		//*)

		moValueDescriptors  m_ValueDescriptors;

		DECLARE_EVENT_TABLE()
};

#endif

