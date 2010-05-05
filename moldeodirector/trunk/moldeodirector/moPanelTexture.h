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
		wxStaticText* StaticTextType;
		wxPanel* Panel5;
		wxTreeCtrl* TreeCtrlImages;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxTextCtrl* TextCtrlMedia;
		wxStaticText* StaticTextFiltered;
		wxStaticBitmap* StaticBitmapThumbnail;
		wxButton* ButtonImport;
		wxStaticText* StaticText1;
		wxPanel* PanelPreview;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxBitmapButton* BitmapButton1;
		wxStaticText* StaticTextSize;
		wxPanel* PanelFilter;
		//*)

	protected:

		//(*Identifiers(moPanelTexture)
		static const long ID_STATICBOX1;
		static const long ID_PANELFILTER;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRLMEDIA;
		static const long ID_BUTTONIMPORT;
		static const long ID_STATICTEXT3;
		static const long ID_PANEL4;
		static const long ID_STATICBITMAPTHUMB;
		static const long ID_PANELPreview;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXTSIZE;
		static const long ID_BITMAPBUTTON1;
		static const long ID_PANEL5;
		static const long ID_TREECTRL1;
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
		//*)

        moShaderCtrl*       m_pShaderCtrl;
        //moTexturesTreeCtrl* m_pTexturesTreeCtrl;

        void LoadImage();


		DECLARE_EVENT_TABLE()
};

#endif
