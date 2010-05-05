#include "moShaderCtrl.h"

//(*InternalHeaders(moShaderCtrl)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/filedlg.h>
//*)

//(*IdInit(moShaderCtrl)
const long moShaderCtrl::ID_TEXTCTRLSHADERCFG = wxNewId();
const long moShaderCtrl::ID_TEXTCTRLDESTINATION = wxNewId();
const long moShaderCtrl::ID_CHECKBOXSHADERONOFF = wxNewId();
const long moShaderCtrl::ID_BITMAPBUTTONSHADERSELECT = wxNewId();
const long moShaderCtrl::ID_BITMAPBUTTONSHADERIMPORT = wxNewId();
const long moShaderCtrl::ID_SLIDERSHADERALPHA = wxNewId();
//*)
const long moShaderCtrl::ID_LEVELSHADERALPHA = wxNewId();


BEGIN_EVENT_TABLE(moShaderCtrl,wxPanel)
	//(*EventTable(moShaderCtrl)
	//*)
END_EVENT_TABLE()

moShaderCtrl::moShaderCtrl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(moShaderCtrl)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("id"));
	SetFocus();
	SetBackgroundColour(wxColour(144,144,144));
	TextCtrlShaderCfg = new wxTextCtrl(this, ID_TEXTCTRLSHADERCFG, wxEmptyString, wxPoint(16,0), wxSize(80,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLSHADERCFG"));
	TextCtrlDestination = new wxTextCtrl(this, ID_TEXTCTRLDESTINATION, wxEmptyString, wxPoint(208,0), wxSize(80,16), 0, wxDefaultValidator, _T("ID_TEXTCTRLDESTINATION"));
	CheckBoxOnOff = new wxCheckBox(this, ID_CHECKBOXSHADERONOFF, wxEmptyString, wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOXSHADERONOFF"));
	CheckBoxOnOff->SetValue(false);
	BitmapButtonShaderSelect = new wxBitmapButton(this, ID_BITMAPBUTTONSHADERSELECT, wxBitmap(wxImage(_T("../../doc/icons/select.png"))), wxPoint(120,0), wxSize(13,13), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSHADERSELECT"));
	BitmapButtonShaderSelect->SetDefault();
	BitmapButtonShaderImport = new wxBitmapButton(this, ID_BITMAPBUTTONSHADERIMPORT, wxBitmap(wxImage(_T("../../doc/icons/import.png"))), wxPoint(104,0), wxSize(13,13), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTONSHADERIMPORT"));
	BitmapButtonShaderImport->SetDefault();
	SliderShaderAlpha = new wxSlider(this, ID_SLIDERSHADERALPHA, 0, 0, 100, wxPoint(136,0), wxSize(64,13), 0, wxDefaultValidator, _T("ID_SLIDERSHADERALPHA"));
	
	Connect(ID_TEXTCTRLSHADERCFG,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moShaderCtrl::OnTextCtrlShaderCfgText);
	Connect(ID_TEXTCTRLDESTINATION,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&moShaderCtrl::OnTextCtrlDestinationText);
	Connect(ID_CHECKBOXSHADERONOFF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&moShaderCtrl::OnCheckBoxOnOffClick);
	Connect(ID_BITMAPBUTTONSHADERSELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moShaderCtrl::OnBitmapButtonShaderSelectClick);
	Connect(ID_BITMAPBUTTONSHADERIMPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&moShaderCtrl::OnBitmapButtonShaderImportClick);
	//*)
	SetSize(pos.x, pos.y, size.x, size.y );

	m_pLevelShaderAlphaCtrl =  new wxMoLevelCtrl(this, ID_LEVELSHADERALPHA, 50, 0, 100, SliderShaderAlpha->GetPosition(), SliderShaderAlpha->GetSize(), 0, wxDefaultValidator, _T("ID_LEVELSHADERALPHA") );
    Connect( ID_LEVELSHADERALPHA, wxEVT_MOLEVELCTRL, (wxObjectEventFunction)&moShaderCtrl::OnLevelShaderAlpha );
	if (SliderShaderAlpha) SliderShaderAlpha->Destroy();

}

moShaderCtrl::~moShaderCtrl()
{
	//(*Destroy(moShaderCtrl)
	//*)
}

void
moShaderCtrl::Inspect( moValueDescriptor p_ValueDescriptor ) {

    m_ValueDescriptor = p_ValueDescriptor;

    if (m_ValueDescriptor.GetValue().GetSubValueCount()==1) {

        TextCtrlShaderCfg->ChangeValue( wxT("") );
        TextCtrlDestination->ChangeValue( wxT("") );

    } else if (m_ValueDescriptor.GetValue().GetSubValueCount()>1) {

        TextCtrlShaderCfg->ChangeValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(1).Text());
        TextCtrlDestination->ChangeValue( (wxChar*)(char*)m_ValueDescriptor.GetValue().GetSubValue(2).Text());

        if (m_ValueDescriptor.GetValue().GetSubValueCount()==4) {

            moValueBase vB = m_ValueDescriptor.GetValue().GetSubValue(3);
            MOfloat alphaval = 1.0;

            if ( vB.GetType() == MO_VALUE_FUNCTION ) {
                moMathFunction* pFunc = vB.Fun();
                if (pFunc) {
                    alphaval = pFunc->Eval( 0 );
                } else {
                    alphaval = 1.0;
                    LogError("Alpha Filter Function undefined");
                }
            } else {
                alphaval = vB.Float();
            }

            m_pLevelShaderAlphaCtrl->SetRange(0,100);
            m_pLevelShaderAlphaCtrl->ChangeValue( (MOint)(alphaval * 100 ) );
            m_pLevelShaderAlphaCtrl->Refresh();
        } else {
            m_pLevelShaderAlphaCtrl->SetRange(0,100);
            m_pLevelShaderAlphaCtrl->ChangeValue( (MOint)(100 ) );
            m_pLevelShaderAlphaCtrl->Refresh();
        }
    }

}

void moShaderCtrl::OnTextCtrlShaderCfgText(wxCommandEvent& event)
{
    ProcessShaderValues();
}

void moShaderCtrl::OnTextCtrlDestinationText(wxCommandEvent& event)
{

    ProcessShaderValues();

}

void moShaderCtrl::OnBitmapButtonShaderImportClick(wxCommandEvent& event)
{
    wxFileDialog* pFileDialog = new wxFileDialog( this );

	if(pFileDialog) {

		pFileDialog->SetWildcard(wxT("Cfg files (*.cfg)|*.cfg|All files (*.*)|*.*"));

		if( pFileDialog->ShowModal() == wxID_OK ) {

			wxFileName	FileName( pFileDialog->GetPath() );

			moProjectDescriptor ProjectDescriptor;
			ProjectDescriptor = m_ValueDescriptor.GetParamDescriptor().GetMobDescriptor().GetProjectDescriptor();

			wxString relativepath = (wxChar*)(const char*)ProjectDescriptor.GetConfigPath();

			FileName.MakeRelativeTo( relativepath );


			wxString path = FileName.GetFullPath();
			const char *cnamerelative = (char*)path.c_str();

			TextCtrlShaderCfg->SetValue( path );

		}

	}
}

void moShaderCtrl::OnLevelShaderAlpha(wxCommandEvent& event) {

    ProcessShaderValues();

}

void moShaderCtrl::ProcessShaderValues() {

    moValue& rValue( m_ValueDescriptor.GetValue() );

    moText shaderstr = moWx2Text( TextCtrlShaderCfg->GetValue() );
    moText shaderdest = moWx2Text( TextCtrlDestination->GetValue() );
    MOfloat alphaval = (float)m_pLevelShaderAlphaCtrl->GetValue() / 100.0;

    if (shaderdest!=moText("") && shaderstr!=moText("")) {
        if (rValue.GetSubValueCount()==1) {

            rValue.AddSubValue( shaderstr, "TXT" );
            rValue.AddSubValue( shaderdest, "TXT" );
            rValue.AddSubValue( FloatToStr( alphaval ), "FUNCTION" );

        } else if (rValue.GetSubValueCount()==3) {

            rValue.GetSubValue(1).SetText( shaderstr );
            rValue.GetSubValue(2).SetText( shaderdest );

            //we have a shader: put some alpha in it
            rValue.AddSubValue( FloatToStr( alphaval ), "FUNCTION" );

        } else if (rValue.GetSubValueCount()==4) {
            rValue.GetSubValue(1).SetText( shaderstr );
            rValue.GetSubValue(2).SetText( shaderdest );

            rValue.GetSubValue(3).SetText( FloatToStr( alphaval ) );
            rValue.GetSubValue(3).SetType( MO_VALUE_FUNCTION );

        }
    } else {
        //Eliminate the SubValues after the first one: we do no longer need them
        rValue.RemoveSubValues(true);

    }

    SetValue( m_ValueDescriptor );


}

void moShaderCtrl::OnBitmapButtonShaderSelectClick(wxCommandEvent& event)
{
}

void moShaderCtrl::OnCheckBoxOnOffClick(wxCommandEvent& event)
{
}
