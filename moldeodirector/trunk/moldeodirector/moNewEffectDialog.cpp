#include "moNewEffectDialog.h"

//(*InternalHeaders(moNewEffectDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(moNewEffectDialog)
const long moNewEffectDialog::ID_STATICTEXT1 = wxNewId();
const long moNewEffectDialog::ID_LABELNAMECTRL = wxNewId();
const long moNewEffectDialog::ID_FILENAMECTRL = wxNewId();
const long moNewEffectDialog::ID_STATICTEXT2 = wxNewId();
const long moNewEffectDialog::ID_OKBUTTON = wxNewId();
const long moNewEffectDialog::ID_CANCELBUTTON = wxNewId();
const long moNewEffectDialog::ID_CHOICE1 = wxNewId();
const long moNewEffectDialog::ID_TREECTRL = wxNewId();
const long moNewEffectDialog::ID_STATICTEXT3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moNewEffectDialog,wxDialog)
	//(*EventTable(moNewEffectDialog)
	//*)
END_EVENT_TABLE()

moNewEffectDialog::moNewEffectDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moNewEffectDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(360,352));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Effect Label Name (used to reference between objects)"), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	LabelNameCtrl = new wxTextCtrl(this, ID_LABELNAMECTRL, wxEmptyString, wxPoint(16,32), wxSize(264,21), 0, wxDefaultValidator, _T("ID_LABELNAMECTRL"));
	ConfigFilenameCtrl = new wxTextCtrl(this, ID_FILENAMECTRL, wxEmptyString, wxPoint(16,80), wxSize(264,21), 0, wxDefaultValidator, _T("ID_FILENAMECTRL"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Effects Plugins"), wxPoint(16,128), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	OkButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(176,312), wxDefaultSize, 0, wxDefaultValidator, _T("ID_OKBUTTON"));
	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(256,312), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCELBUTTON"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(208,128), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->Append(_("Pre-Effects"));
	Choice1->SetSelection( Choice1->Append(_("Effects")) );
	Choice1->Append(_("Post-Effects"));
	TreeCtrl = new wxTreeCtrl(this, ID_TREECTRL, wxPoint(16,152), wxSize(320,152), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL"));
	StaticTextConfigFilename = new wxStaticText(this, ID_STATICTEXT3, _("Config file name"), wxPoint(16,64), wxDefaultSize, 0, _T("ID_STATICTEXT3"));

	Connect(ID_LABELNAMECTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewEffectDialog::OnLabelNameCtrlText);
	Connect(ID_FILENAMECTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewEffectDialog::OnConfigFilenameCtrlText);
	Connect(ID_OKBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewEffectDialog::OnOkButtonClick);
	Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewEffectDialog::OnCancelButtonClick);
	Connect(ID_TREECTRL,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&moNewEffectDialog::OnTreeCtrlSelectionChanged);
	//*)
}

moNewEffectDialog::~moNewEffectDialog()
{
	//(*Destroy(moNewEffectDialog)
	//*)
}

void
moNewEffectDialog::Init( moDirectorFrame*  pFrame ) {

        m_pDirectorFrame = pFrame;

        OkButton->Enable(false);


        m_AppDescriptor = m_pDirectorFrame->GetApplicationDescriptor();

        //carga las definiciones de los plugins:

        moPluginDefinitions & rPlugins( m_AppDescriptor.GetPluginDefinitions() );

        wxTreeItemId rootid = TreeCtrl->AddRoot( wxT("Moldeo Objects - MOB")) ;

        wxTreeItemId preid = TreeCtrl->AppendItem( rootid, wxT("preeffects"));
        wxTreeItemId eid = TreeCtrl->AppendItem( rootid, wxT("effects"));
        wxTreeItemId postid = TreeCtrl->AppendItem( rootid, wxT("posteffects"));
        wxTreeItemId ioid = TreeCtrl->AppendItem( rootid, wxT("iodevices"));
        wxTreeItemId resid = TreeCtrl->AppendItem( rootid, wxT("resources"));

        for( MOuint i = 0; i<rPlugins.Count(); i++) {

            moPluginDefinition  pDefinition = rPlugins[i];

            switch( pDefinition.GetType() ) {
                case MO_OBJECT_PREEFFECT:
                    TreeCtrl->AppendItem( preid, moText2Wx(pDefinition.GetName()) ,-1, -1, new moPluginItemData(pDefinition) );
                    break;
                case MO_OBJECT_EFFECT:
                    TreeCtrl->AppendItem( eid, moText2Wx(pDefinition.GetName()), -1, -1, new moPluginItemData(pDefinition));
                    break;
                case MO_OBJECT_POSTEFFECT:
                    TreeCtrl->AppendItem( postid, moText2Wx(pDefinition.GetName()),-1, -1, new moPluginItemData(pDefinition));
                    break;
                case MO_OBJECT_IODEVICE:
                    TreeCtrl->AppendItem( ioid, moText2Wx(pDefinition.GetName()),-1, -1, new moPluginItemData(pDefinition));
                    break;
                case MO_OBJECT_RESOURCE:
                    TreeCtrl->AppendItem( resid, moText2Wx(pDefinition.GetName()),-1, -1, new moPluginItemData(pDefinition));
                    break;
                default:
                    break;
            }

        }


}

moMobDefinition
moNewEffectDialog::GetMobDefinition() {

        return m_MobDefinition;

}

void moNewEffectDialog::OnOkButtonClick(wxCommandEvent& event)
{
    if (CheckData())
      EndModal( wxID_OK );
}

void moNewEffectDialog::OnCancelButtonClick(wxCommandEvent& event)
{
    EndModal( wxID_CANCEL );
}

void moNewEffectDialog::OnLabelNameCtrlText(wxCommandEvent& event)
{
    CheckData();
}

bool moNewEffectDialog::CheckData() {

    if (LabelNameCtrl->GetValue()!=wxT("")) {

        if (ConfigFilenameCtrl->GetValue()!=wxT("")) {

            wxTreeItemId idsel = TreeCtrl->GetSelection();
            if ( idsel.IsOk() ) {
                moPluginItemData* pData = (moPluginItemData*) TreeCtrl->GetItemData( idsel );

                if (pData!=NULL) {

                    moPluginDefinition& rPluginDef( pData->GetPluginDefinition() );

                    m_MobDefinition = moMobDefinition(  rPluginDef.GetName(),
                                                        moWx2Text(ConfigFilenameCtrl->GetValue()),
                                                        rPluginDef.GetType(),
                                                        moWx2Text(LabelNameCtrl->GetValue()) );

                    OkButton->Enable(true);
                    return true;

                } else OkButton->Enable(false);
            }
        }
    }

    return false;
}

void moNewEffectDialog::OnTreeCtrlSelectionChanged(wxTreeEvent& event)
{
    CheckData();
}

void moNewEffectDialog::OnConfigFilenameCtrlText(wxCommandEvent& event)
{
    CheckData();
}
