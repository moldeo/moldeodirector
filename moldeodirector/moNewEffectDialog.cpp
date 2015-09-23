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
const long moNewEffectDialog::ID_STATICTEXT4 = wxNewId();
const long moNewEffectDialog::ID_CHOICE2 = wxNewId();
const long moNewEffectDialog::ID_STATICTEXT5 = wxNewId();
const long moNewEffectDialog::ID_COMBOBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(moNewEffectDialog,wxDialog)
	//(*EventTable(moNewEffectDialog)
	//*)
END_EVENT_TABLE()

moNewEffectDialog::moNewEffectDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moNewEffectDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(360,401));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Effect Label Name (used to reference between objects)"), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	LabelNameCtrl = new wxTextCtrl(this, ID_LABELNAMECTRL, wxEmptyString, wxPoint(16,32), wxSize(312,21), 0, wxDefaultValidator, _T("ID_LABELNAMECTRL"));
	ConfigFilenameCtrl = new wxTextCtrl(this, ID_FILENAMECTRL, wxEmptyString, wxPoint(16,80), wxSize(312,21), 0, wxDefaultValidator, _T("ID_FILENAMECTRL"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Effects Plugins"), wxPoint(16,128), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	OkButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(176,368), wxDefaultSize, 0, wxDefaultValidator, _T("ID_OKBUTTON"));
	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(264,368), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCELBUTTON"));
	Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(208,128), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->Append(_("Pre-Effects"));
	Choice1->SetSelection( Choice1->Append(_("Effects")) );
	Choice1->Append(_("Post-Effects"));
	TreeCtrl = new wxTreeCtrl(this, ID_TREECTRL, wxPoint(16,152), wxSize(320,152), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL"));
	StaticTextConfigFilename = new wxStaticText(this, ID_STATICTEXT3, _("Config file name"), wxPoint(16,64), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Keyboard"), wxPoint(224,312), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	ChoiceKey = new wxChoice(this, ID_CHOICE2, wxPoint(224,328), wxSize(63,24), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	ChoiceKey->SetSelection( ChoiceKey->Append(_("None")) );
	ChoiceKey->Append(_("A"));
	ChoiceKey->Append(_("B"));
	ChoiceKey->Append(_("C"));
	ChoiceKey->Append(_("D"));
	ChoiceKey->Append(_("E"));
	ChoiceKey->Append(_("F"));
	ChoiceKey->Append(_("G"));
	ChoiceKey->Append(_("H"));
	ChoiceKey->Append(_("I"));
	ChoiceKey->Append(_("J"));
	ChoiceKey->Append(_("K"));
	ChoiceKey->Append(_("L"));
	ChoiceKey->Append(_("M"));
	ChoiceKey->Append(_("N"));
	ChoiceKey->Append(_("O"));
	ChoiceKey->Append(_("P"));
	ChoiceKey->Append(_("Q"));
	ChoiceKey->Append(_("R"));
	ChoiceKey->Append(_("S"));
	ChoiceKey->Append(_("T"));
	ChoiceKey->Append(_("U"));
	ChoiceKey->Append(_("V"));
	ChoiceKey->Append(_("W"));
	ChoiceKey->Append(_("X"));
	ChoiceKey->Append(_("Y"));
	ChoiceKey->Append(_("Z"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Active"), wxPoint(24,312), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	ChoiceActive = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(24,328), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	ChoiceActive->Append(_("No"));
	ChoiceActive->SetSelection( ChoiceActive->Append(_("Yes")) );

	Connect(ID_LABELNAMECTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewEffectDialog::OnLabelNameCtrlText);
	Connect(ID_FILENAMECTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moNewEffectDialog::OnConfigFilenameCtrlText);
	Connect(ID_OKBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewEffectDialog::OnOkButtonClick);
	Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moNewEffectDialog::OnCancelButtonClick);
	Connect(ID_TREECTRL,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&moNewEffectDialog::OnTreeCtrlSelectionChanged);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&moNewEffectDialog::OnChoice2Select);
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

wxTreeItemId
moNewEffectDialog::EditMobIterationClassName( const wxTreeItemId& p_itemid, const moMobDefinition& p_MobDefinition ) {

  wxTreeItemId itemid;
  wxTreeItemId returned;

  moPluginItemData* pItemData = (moPluginItemData*) TreeCtrl->GetItemData( p_itemid );
  if (pItemData) {
    if (p_MobDefinition.GetName()==pItemData->GetPluginDefinition().GetName()) {
      return p_itemid;
    }
  }

  if (TreeCtrl) {
    wxTreeItemIdValue cookie;
    itemid = TreeCtrl->GetFirstChild( p_itemid, cookie );

    while(itemid.IsOk()) {

      returned = EditMobIterationClassName(  itemid, p_MobDefinition );

      if (returned.IsOk())
          return returned;

      itemid = TreeCtrl->GetNextChild( p_itemid, cookie );
    }
  }

  return returned;
}

void
moNewEffectDialog::EditMob( const moMobDefinition& p_MobDefinition ) {
  m_MobDefinition = p_MobDefinition;

  LabelNameCtrl->SetValue( moText2Wx( m_MobDefinition.GetLabelName() ) );
  ConfigFilenameCtrl->SetValue( moText2Wx( m_MobDefinition.GetConfigName() ) );

  if (m_MobDefinition.GetActivate())
    ChoiceActive->Select(1);
  else
    ChoiceActive->Select(0);


  for(int i = 0; i<ChoiceKey->GetCount(); i++) {
    moText mo_string = moWx2Text( ChoiceKey->GetString(i) );
    if ( mo_string == m_MobDefinition.GetKeyName() ) {
        ChoiceKey->Select(i);
        break;
    }

  }

  //wxTreeItemId idsel = TreeCtrl->GetSelection();

  wxTreeItemId rootid = TreeCtrl->GetRootItem();
  wxTreeItemId matchedid;

  matchedid = EditMobIterationClassName( rootid, m_MobDefinition );

  if (!matchedid.IsOk()) return;

  TreeCtrl->SelectItem( matchedid, true );


  CheckData();

/*
  if ( idsel.IsOk() ) {
      //moPluginItemData* pData = (moPluginItemData*) TreeCtrl->GetItemData( idsel );
  }
*/

  //->SetValue( moText2Wx( m_MobDefinition.GetConfigName() ) );

  //wxTreeItemId idsel = TreeCtrl->GetSelection();

  //TreeCtrl->Get

  //if ( idsel.IsOk() ) {
  //moPluginItemData* pData = (moPluginItemData*) TreeCtrl->GetItemData( idsel );
}


const moMobDefinition&
moNewEffectDialog::GetMobDefinition() {

        return m_MobDefinition;

}

void moNewEffectDialog::OnOkButtonClick(wxCommandEvent& event)
{
    if (CheckData()) {
      EndModal( wxID_OK );
    } else event.Skip();

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

    moMobDefinition oldDef = m_MobDefinition;


    if (LabelNameCtrl->GetValue()!=wxT("")) {

        if (ConfigFilenameCtrl->GetValue()!=wxT("")) {

            wxTreeItemId idsel = TreeCtrl->GetSelection();

            if ( idsel.IsOk() ) {
                moPluginItemData* pData = (moPluginItemData*) TreeCtrl->GetItemData( idsel );

                if (pData!=NULL) {

                    moPluginDefinition& rPluginDef( pData->GetPluginDefinition() );
                    moText key_trigger = "";
                    bool on_off = true;
                    key_trigger = moWx2Text( ChoiceKey->GetString( ChoiceKey->GetCurrentSelection() ) );
                    if (key_trigger=="None") key_trigger = "";
                    on_off = (ChoiceActive->GetCurrentSelection()==1);
                    m_MobDefinition = moMobDefinition(  rPluginDef.GetName(),
                                                        moWx2Text(ConfigFilenameCtrl->GetValue()),
                                                        rPluginDef.GetType(),
                                                        moWx2Text(LabelNameCtrl->GetValue()) );
                    m_MobDefinition.SetKeyName( key_trigger );
                    m_MobDefinition.SetActivate( on_off );
                    m_MobDefinition.SetMoldeoId(oldDef.GetMoldeoId());
                    m_MobDefinition.SetMoldeoFatherId( oldDef.GetMoldeoFatherId() );
                    m_MobDefinition.SetFatherLabelName( oldDef.GetFatherLabelName() );

                    m_MobDefinition.SetConsoleParamIndex( oldDef.GetMobIndex().GetParamIndex() );
                    m_MobDefinition.SetConsoleValueIndex( oldDef.GetMobIndex().GetValueIndex() );

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


void moNewEffectDialog::OnChoice2Select(wxCommandEvent& event)
{
    CheckData();
}

void moNewEffectDialog::OnComboBox1Selected(wxCommandEvent& event)
{
    CheckData();
}
