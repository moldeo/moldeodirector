#ifndef MOPANELTEXTURE_H
#define MOPANELTEXTURE_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include "treemultictrl/wxTreeMultiCtrl.h"
#include "moShaderCtrl.h"
#include "moTextureItemCtrl.h"

//(*Headers(moPanelTexture)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/notebook.h>
//*)

class moPanelTexture: public wxPanel, public moIDirectorActions
{
	public:

		moPanelTexture(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moPanelTexture();
        void Inspect( moValueDescriptor p_ValueDescriptor );

        void    InitTexturesTree();

		//(*Declarations(moPanelTexture)
		wxMoColourPanel* ImagePanel;
		wxTextCtrl* TextCtrlMedia;
		wxButton* ButtonImport;
		wxPanel* ImportPanel;
		//*)

	protected:

		//(*Identifiers(moPanelTexture)
		static const long ID_TEXTCTRLMEDIA;
		static const long ID_BUTTONIMPORT;
		static const long ID_IMPORTPANEL;
		static const long ID_IMAGEPANEL;
		//*)
		static const long ID_SHADERCTRL;
		static const long ID_TEXTURESTREECTRL;


	private:

        moValueDescriptor   m_ValueDescriptor;

		//(*Handlers(moPanelTexture)
		void OnListbook1PageChanged(wxNotebookEvent& event);
		void OnButtonImportClick(wxCommandEvent& event);
		void OnTextCtrlMediaText(wxCommandEvent& event);
		void OnTextCtrlShaderCfgText(wxCommandEvent& event);
		void OnTextCtrlDestinationText(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButtonImportShaderClick(wxCommandEvent& event);
		void OnPanelFilterPaint(wxPaintEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnPanel4Paint(wxPaintEvent& event);
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnPanelDetailsPaint(wxPaintEvent& event);
		//*)

        moShaderCtrl*       m_pShaderCtrl;
        //moTexturesTreeCtrl* m_pTexturesTreeCtrl;

        void LoadImage();

    wxTreeMultiCtrl*  m_pTreeMultiCtrl;

    //wxPanel* m_pDetails;
    wxStaticText* m_pTextDetails;

		DECLARE_EVENT_TABLE()
};

#endif
