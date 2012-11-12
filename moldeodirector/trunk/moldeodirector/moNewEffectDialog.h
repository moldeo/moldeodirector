#ifndef NEWEFFECTDIALOG_H
#define NEWEFFECTDIALOG_H

#include "moDirectorTypes.h"
#include "moDirectorFrame.h"

//(*Headers(moNewEffectDialog)
#include <wx/treectrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
class moPluginItemData : public wxTreeItemData {

    public:
        moPluginItemData() {}
        moPluginItemData( const moPluginDefinition &plugindefinition ) {
            m_PluginDefinition = plugindefinition;
        }
        virtual ~moPluginItemData() {}

        moPluginDefinition& GetPluginDefinition() {
                return m_PluginDefinition;
        }

    protected:
        moPluginDefinition  m_PluginDefinition;

};

class moNewEffectDialog: public wxDialog
{
	public:

		moNewEffectDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moNewEffectDialog();

        void    Init( moDirectorFrame*  pFrame );
		moMobDefinition GetMobDefinition();
		bool CheckData();

		//(*Declarations(moNewEffectDialog)
		wxStaticText* StaticText2;
		wxTextCtrl* LabelNameCtrl;
		wxStaticText* StaticText1;
		wxButton* OkButton;
		wxStaticText* StaticTextConfigFilename;
		wxTextCtrl* ConfigFilenameCtrl;
		wxButton* CancelButton;
		wxChoice* Choice1;
		wxTreeCtrl* TreeCtrl;
		//*)

	protected:

		//(*Identifiers(moNewEffectDialog)
		static const long ID_STATICTEXT1;
		static const long ID_LABELNAMECTRL;
		static const long ID_FILENAMECTRL;
		static const long ID_STATICTEXT2;
		static const long ID_OKBUTTON;
		static const long ID_CANCELBUTTON;
		static const long ID_CHOICE1;
		static const long ID_TREECTRL;
		static const long ID_STATICTEXT3;
		//*)

	private:

		//(*Handlers(moNewEffectDialog)
		void OnOkButtonClick(wxCommandEvent& event);
		void OnCancelButtonClick(wxCommandEvent& event);
		void OnLabelNameCtrlText(wxCommandEvent& event);
		void OnTreeCtrlSelectionChanged(wxTreeEvent& event);
		void OnConfigFilenameCtrlText(wxCommandEvent& event);
		//*)

        moDirectorFrame*        m_pDirectorFrame;
		moMobDefinition         m_MobDefinition;
		moApplicationDescriptor m_AppDescriptor;

		DECLARE_EVENT_TABLE()
};

#endif

