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
#include <wx/combobox.h>
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
		const moMobDefinition& GetMobDefinition();
		bool CheckData();
		void EditMob( const moMobDefinition& p_MobDefinition );
    wxTreeItemId EditMobIterationClassName( const wxTreeItemId& p_itemid, const moMobDefinition& p_MobDefinition );
		//(*Declarations(moNewEffectDialog)
		wxStaticText* StaticText2;
		wxTextCtrl* LabelNameCtrl;
		wxComboBox* ChoiceActive;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* OkButton;
		wxStaticText* StaticTextConfigFilename;
		wxTextCtrl* ConfigFilenameCtrl;
		wxChoice* ChoiceKey;
		wxStaticText* StaticText4;
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
		static const long ID_STATICTEXT4;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX1;
		//*)

	private:

		//(*Handlers(moNewEffectDialog)
		void OnOkButtonClick(wxCommandEvent& event);
		void OnCancelButtonClick(wxCommandEvent& event);
		void OnLabelNameCtrlText(wxCommandEvent& event);
		void OnTreeCtrlSelectionChanged(wxTreeEvent& event);
		void OnConfigFilenameCtrlText(wxCommandEvent& event);
		void OnChoice2Select(wxCommandEvent& event);
		void OnComboBox1Selected(wxCommandEvent& event);
		//*)

        moDirectorFrame*        m_pDirectorFrame;
		moMobDefinition         m_MobDefinition;
		moApplicationDescriptor m_AppDescriptor;

		DECLARE_EVENT_TABLE()
};

#endif

