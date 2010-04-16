#include "moValueCtrl.h"

BEGIN_EVENT_TABLE( moValueCtrl, wxPanel)
    EVT_TEXT( -1,  moValueCtrl::OnTextUpdated)
    EVT_SPIN( -1,  moValueCtrl::OnSpinUpdated)
    EVT_COMBOBOX( -1,  moValueCtrl::OnComboUpdated)
END_EVENT_TABLE()

moValueCtrl::moValueCtrl(wxWindow *parent,
            int x , int y, int width, int height,
            long style,
            const wxString& name) : wxPanel( parent,
            x, y, width, height, wxNO_BORDER, name ) {
    m_bInit = false;
    m_pTextCtrl = NULL;
    m_pTextCtrlR = NULL;
    m_pTextCtrlG = NULL;
    m_pTextCtrlB = NULL;
    m_pSpinCtrl = NULL;
    m_pBlendingCtrl = NULL;
    m_pParamToggle = NULL;
    block = false;
}

void
moValueCtrl::Init( moDirectorChildFrame* parent, moValueDescriptor p_valuedescriptor ) {

	wxString ValueStr = _("");
	MOint  ValueInt = 0;
	MOdouble  ValueFloat = 0.0;
	int xpos = 0;

    fonttypes[MO_FONT_OUTLINE] = wxT("Outline");
    fonttypes[MO_FONT_TRANSLUCENT] = wxT("Translucent");
    fonttypes[MO_FONT_TRANSLUCENTTEXTURE] = wxT("Translucent texture");
    fonttypes[MO_FONT_GRAYSCALE] = wxT("Grayscale");
    fonttypes[MO_FONT_MONOCHROME] = wxT("Monochrome");
    fonttypes[MO_FONT_SOLID] = wxT("Solid");
    fonttypes[MO_FONT_FILLED] = wxT("Filled");
    fonttypes[MO_FONT_GLBUILD] = wxT("GLBuild");

    blendings[MO_BLENDING_TRANSPARENCY] = wxT("Transparency");
    blendings[MO_BLENDING_ADDITIVEALPHA] = wxT("Additive w/alpha");
    blendings[MO_BLENDING_MIXING] = wxT("Mixing");
    blendings[MO_BLENDING_MULTIPLY] = wxT("Multiply");
    blendings[MO_BLENDING_EXCLUSION] = wxT("Exclusion");
    blendings[MO_BLENDING_ADDITIVE] = wxT("Additive color");
    blendings[MO_BLENDING_OVERLAY] = wxT("Overlay");
    blendings[MO_BLENDING_SUBSTRACTIVE] = wxT("Substractive");
    blendings[MO_BLENDING_SATURATE] = wxT("Saturate");

    polygonmodes[MO_POLYGONMODE_FILL] = wxT("FILL");
    polygonmodes[MO_POLYGONMODE_LINE] = wxT("LINE");
    polygonmodes[MO_POLYGONMODE_POINT] = wxT("POINT");


	m_pDirectorChildFrame = parent;

	SetNextActionHandler( parent );

    m_ValueDescriptor = p_valuedescriptor;

    moParamType PType = m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType();
    moValue pValue( m_ValueDescriptor.GetValue() );

    //este boton permite marcar este parametro, para luego ser grabado como preconfiguracion
    long ParamToggleId = wxNewId();
    long stylewnd = 0;

	m_pParamToggle = new wxRadioButton( this, ParamToggleId, wxT(""), wxPoint(xpos,0), wxSize(20,20),  stylewnd);
	xpos+= m_pParamToggle->GetSize().x;
	Connect( ParamToggleId, wxEVT_COMMAND_RADIOBUTTON_SELECTED , (wxObjectEventFunction)&moValueCtrl::OnParamToggleClick );


	switch( PType ) {
		case MO_PARAM_ALPHA:
		case MO_PARAM_SYNC:
		case MO_PARAM_PHASE:
		case MO_PARAM_FUNCTION:
		case MO_PARAM_TRANSLATEX:
		case MO_PARAM_TRANSLATEY:
		case MO_PARAM_TRANSLATEZ:
		case MO_PARAM_SCALEX:
		case MO_PARAM_SCALEY:
		case MO_PARAM_SCALEZ:
		case MO_PARAM_ROTATEX:
		case MO_PARAM_ROTATEY:
		case MO_PARAM_ROTATEZ:
		case MO_PARAM_TEXT:
		case MO_PARAM_OBJECT:
		case MO_PARAM_3DMODEL:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(20,0),wxSize(150,20));
			xpos+=m_pTextCtrl->GetSize().x;
			//Connect(
			break;
        case MO_PARAM_NUMERIC:
            if (pValue.GetSubValue(0).Type()==MO_VALUE_NUM_FLOAT || pValue.GetSubValue(0).Type()==MO_VALUE_NUM_DOUBLE ) {
                ValueFloat = pValue.GetSubValue(0).Float();
                ValueStr = moText2Wx( FloatToStr(ValueFloat) );
            } else {
                ValueInt = pValue.GetSubValue(0).Int();
                ValueStr = moText2Wx( IntToStr(ValueInt) );
            }

            //m_pSpinCtrl = new wxSpinCtrl( this, -1, (wxChar*)(char*)IntToStr(ValueInt),wxPoint(20,0),wxSize(80,20));
            m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(20,0),wxSize(150,20));
            xpos+=m_pTextCtrl->GetSize().x;
            break;
        case MO_PARAM_BLENDING:
            ValueInt = pValue.GetSubValue(0).Int();
            m_pBlendingCtrl = new wxComboBox( this, -1, blendings[ValueInt], wxPoint(20,0), wxSize(80,20), MO_BLENDINGS, blendings,wxCB_READONLY);
            xpos+=m_pBlendingCtrl->GetSize().x;
            break;
        case MO_PARAM_POLYGONMODE:
            ValueInt = pValue.GetSubValue(0).Int();
            m_pPolygonModeCtrl = new wxComboBox( this, -1, polygonmodes[ValueInt], wxPoint(20,0), wxSize(80,20), MO_POLYGONMODES, polygonmodes,wxCB_READONLY);
            xpos+=m_pPolygonModeCtrl->GetSize().x;
            break;
        case MO_PARAM_FONT:
            ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
            m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
            xpos+=m_pTextCtrl->GetSize().x;

            ValueInt = pValue.GetSubValue(1).Int();
            m_pFontTypeCtrl = new wxComboBox( this, -1, fonttypes[ValueInt], wxPoint(xpos,0), wxSize(80,20), MO_FONT_TYPES, fonttypes, wxCB_READONLY);
            xpos+=m_pFontTypeCtrl->GetSize().x;

            ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).ToText();
            m_pTextCtrlR = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
            xpos+=m_pTextCtrlR->GetSize().x;
            break;
		case MO_PARAM_TEXTURE:
		case MO_PARAM_VIDEO:
            if (pValue.GetSubValueCount()==1) {
                ///NO FILTERS
                ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
                m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(150,20));
                xpos+=m_pTextCtrl->GetSize().x;
            } else if (pValue.GetSubValueCount()>1) {
                /// SHADER FILTER
                ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
                m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                xpos+=m_pTextCtrl->GetSize().x;

                ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
                m_pTextCtrlR = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                xpos+=m_pTextCtrlR->GetSize().x;

                ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
                m_pTextCtrlG = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                xpos+=m_pTextCtrlG->GetSize().x;

                ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
                m_pTextCtrlB = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                xpos+=m_pTextCtrlB->GetSize().x;
            }
			//Connect(
			break;
        case MO_PARAM_FILTER:
            ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
            xpos+=m_pTextCtrl->GetSize().x;

            ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
			m_pTextCtrlR = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
            xpos+=m_pTextCtrlR->GetSize().x;

			ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
			m_pTextCtrlG = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
            xpos+=m_pTextCtrlG->GetSize().x;

			ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
			m_pTextCtrlB = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
			xpos+=m_pTextCtrlB->GetSize().x;
            break;
		case MO_PARAM_COLOR:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			m_pTextCtrlR = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
			xpos+=m_pTextCtrlR->GetSize().x;

			ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
			m_pTextCtrlG = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
			xpos+=m_pTextCtrlG->GetSize().x;

			ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
			m_pTextCtrlB = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
			xpos+=m_pTextCtrlB->GetSize().x;

			ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
			m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
			xpos+=m_pTextCtrl->GetSize().x;
			break;
		default:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(20,0),wxSize(300,20));
			xpos+=m_pTextCtrl->GetSize().x;
			break;
	};


    long InspectorId = wxNewId();
	m_pInspectorButton = new wxButton( this, InspectorId, wxT("..."), wxPoint(xpos,0),wxSize(20,20) );
	xpos+=m_pInspectorButton->GetSize().x;
	Connect( InspectorId, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&moValueCtrl::OnInspectorClick );

    long AddId = wxNewId();
	m_pAddButton = new wxButton( this, AddId, wxT("+"), wxPoint(xpos,0),wxSize(20,20) );
	xpos+=m_pAddButton->GetSize().x;
	Connect( AddId, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&moValueCtrl::OnAddClick );

	long DeleteId = wxNewId();
	m_pDeleteButton = new wxButton( this, DeleteId, wxT("x"), wxPoint(xpos,0),wxSize(20,20) );
	xpos+=m_pDeleteButton->GetSize().x;
    Connect( DeleteId, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&moValueCtrl::OnDeleteClick );

    m_bInit = true;
}

void
moValueCtrl::Set( moValueDescriptor p_valuedescriptor ) {

    wxString ValueStr = _("");
    int ValueInt = 0;
    double ValueFloat = 0.0;
    int xpos = 0;

    m_ValueDescriptor = p_valuedescriptor;

    moParamType PType = m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType();
    moValue& pValue( m_ValueDescriptor.GetValue() );

    switch( PType ) {
		case MO_PARAM_ALPHA:
		case MO_PARAM_SYNC:
		case MO_PARAM_PHASE:
		case MO_PARAM_FUNCTION:
		case MO_PARAM_TRANSLATEX:
		case MO_PARAM_TRANSLATEY:
		case MO_PARAM_TRANSLATEZ:
		case MO_PARAM_SCALEX:
		case MO_PARAM_SCALEY:
		case MO_PARAM_SCALEZ:
		case MO_PARAM_ROTATEX:
		case MO_PARAM_ROTATEY:
		case MO_PARAM_ROTATEZ:
		case MO_PARAM_TEXT:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );
			//Connect(
			break;
    case MO_PARAM_NUMERIC:
        if (pValue.GetSubValue(0).Type()==MO_VALUE_NUM_FLOAT || pValue.GetSubValue(0).Type()==MO_VALUE_NUM_DOUBLE ) {
            ValueFloat = pValue.GetSubValue(0).Float();
            ValueStr = moText2Wx( FloatToStr(ValueFloat) );
        } else {
            ValueInt = pValue.GetSubValue(0).Int();
            ValueStr = moText2Wx( IntToStr(ValueInt) );
        }
        if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );
        break;
    case MO_PARAM_BLENDING:
        ValueInt = pValue.GetSubValue(0).Int();
        if ( 0<=ValueInt && ValueInt<MO_BLENDINGS && m_pBlendingCtrl)
            m_pBlendingCtrl->SetValue( blendings[ValueInt] );
        break;
    case MO_PARAM_POLYGONMODE:
        ValueInt = pValue.GetSubValue(0).Int();
        if ( 0<=ValueInt && ValueInt<MO_POLYGONMODES && m_pPolygonModeCtrl)
                m_pPolygonModeCtrl->SetValue( polygonmodes[ValueInt] );
        break;
    case MO_PARAM_FONT:
        ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
        if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );

        ValueInt = pValue.GetSubValue(1).Int();
        if ( 0<=ValueInt && ValueInt<MO_FONT_TYPES && m_pFontTypeCtrl)
          m_pFontTypeCtrl->SetValue( fonttypes[ValueInt] );

        ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
        if (m_pTextCtrlR) m_pTextCtrlR->ChangeValue( ValueStr );
        break;
    case MO_PARAM_TEXTURE:
    case MO_PARAM_VIDEO:
            if (pValue.GetSubValueCount()==1) {
                ///NO FILTERS, ONLY VIDEO OR TEXTURE
                ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
                if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );
                if (m_pTextCtrlR) { m_pTextCtrlR->Destroy(); m_pTextCtrlR = NULL; }
                if (m_pTextCtrlG) { m_pTextCtrlG->Destroy(); m_pTextCtrlG = NULL; }
                if (m_pTextCtrlB) { m_pTextCtrlB->Destroy(); m_pTextCtrlB = NULL; }
            } else if (pValue.GetSubValueCount()>1) {
                ///FILTER OR (MULTIPLE IMAGES???)
                m_bInit = false;

                if (m_pTextCtrlR) {

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
                    if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
                    if (m_pTextCtrlR) m_pTextCtrlR->ChangeValue( ValueStr );

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
                    if (m_pTextCtrlG) m_pTextCtrlG->ChangeValue( ValueStr );

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
                    if (m_pTextCtrlB) m_pTextCtrlB->ChangeValue( ValueStr );

                } else {

                    xpos = m_pParamToggle->GetSize().x;

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
                    m_pTextCtrl = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                    xpos+=m_pTextCtrl->GetSize().x;

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
                    m_pTextCtrlR = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                    xpos+=m_pTextCtrlR->GetSize().x;

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
                    m_pTextCtrlG = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                    xpos+=m_pTextCtrlG->GetSize().x;

                    ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
                    m_pTextCtrlB = new wxTextCtrl( this, -1, ValueStr,wxPoint(xpos,0),wxSize(70,20));
                    xpos+=m_pTextCtrlB->GetSize().x;

                    if (m_pInspectorButton)
                        m_pInspectorButton->SetSize( xpos, 0, m_pInspectorButton->GetSize().x, m_pInspectorButton->GetSize().y );
                    xpos+=m_pInspectorButton->GetSize().x;
                    if (m_pAddButton)
                        m_pAddButton->SetSize( xpos, 0, m_pAddButton->GetSize().x, m_pAddButton->GetSize().y );
                    xpos+=m_pAddButton->GetSize().x;
                    if (m_pDeleteButton)
                        m_pDeleteButton->SetSize( xpos, 0, m_pDeleteButton->GetSize().x, m_pDeleteButton->GetSize().y );

                    this->Refresh();
                }
                m_bInit = true;
            }
			//Connect(
			break;
        case MO_PARAM_FILTER:
            ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );
            ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
			if (m_pTextCtrlR) m_pTextCtrlR->ChangeValue( ValueStr );
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
			if (m_pTextCtrlG) m_pTextCtrlG->ChangeValue( ValueStr );
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
			if (m_pTextCtrlB) m_pTextCtrlB->ChangeValue( ValueStr );
            break;
		case MO_PARAM_COLOR:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			if (m_pTextCtrlR) m_pTextCtrlR->ChangeValue( ValueStr );
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(1).Text();
			if (m_pTextCtrlG) m_pTextCtrlG->ChangeValue( ValueStr );
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(2).Text();
			if (m_pTextCtrlB) m_pTextCtrlB->ChangeValue( ValueStr );
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(3).Text();
			if (m_pTextCtrl) m_pTextCtrl->ChangeValue( ValueStr );
			break;
		default:
			ValueStr =(wxChar*)(char*) pValue.GetSubValue(0).Text();
			if (m_pTextCtrl)
                m_pTextCtrl->ChangeValue( ValueStr );
			break;
	};
}

void moValueCtrl::ParamToggleOff() {
    if (m_pParamToggle)
        m_pParamToggle->SetValue(false);
}

void moValueCtrl::ParamToggleOn() {
    if (m_pParamToggle)
        m_pParamToggle->SetValue(true);
}


void moValueCtrl::OnParamToggleClick(  wxCommandEvent& event ) {

    moParameterDescriptor  ParamDescriptor = m_ValueDescriptor.GetParamDescriptor();
    ParamDescriptor.SetIndexValue( m_ValueDescriptor.GetValueIndex().m_ValueIndex );

    m_pDirectorChildFrame->SetParameter( ParamDescriptor );

}

void moValueCtrl::OnInspectorClick(  wxCommandEvent& event ) {

    m_pDirectorChildFrame->Inspect( m_ValueDescriptor, true );

}

void moValueCtrl::OnAddClick(  wxCommandEvent& event ) {

    //wxMessageBox("Add click, must add another value (copy of this one)");
    moValueDescriptor pCopy;

    pCopy = m_ValueDescriptor;

    InsertValue( pCopy );


}

void moValueCtrl::OnDeleteClick(  wxCommandEvent& event ) {

    moValueDescriptor pCopy;

    pCopy = m_ValueDescriptor;

    DeleteValue( pCopy );

}

void
moValueCtrl::OnSpinUpdated( wxSpinEvent& event) {
  if (m_bInit) {

    moValue& rValue( m_ValueDescriptor.GetValue() );

    switch( (int)m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {

        case MO_PARAM_NUMERIC:
            //if (m_pSpinCtrl) rValue.GetSubValue(0).SetInt( m_pSpinCtrl->GetValue() );
            break;

    }
    SetValue( m_ValueDescriptor );
    m_pDirectorChildFrame->Inspect( m_ValueDescriptor, false );
  }
}

void
moValueCtrl::OnTextUpdated( wxCommandEvent& event) {

    if (m_bInit) {

        moValue& rValue( m_ValueDescriptor.GetValue() );

        //dependiendo del control, actualizar el config...
        switch( m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {
            case MO_PARAM_ALPHA:
            case MO_PARAM_FUNCTION:
            case MO_PARAM_TRANSLATEX:
            case MO_PARAM_TRANSLATEY:
            case MO_PARAM_TRANSLATEZ:
            case MO_PARAM_SCALEX:
            case MO_PARAM_SCALEY:
            case MO_PARAM_SCALEZ:
            case MO_PARAM_ROTATEX:
            case MO_PARAM_ROTATEY:
            case MO_PARAM_ROTATEZ:
            case MO_PARAM_TEXT:
                if (m_pTextCtrl) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                break;
            case MO_PARAM_NUMERIC:
                if (m_pTextCtrl) {
                    if ( rValue.GetSubValue(0).Type()==MO_VALUE_NUM_FLOAT ||
                        rValue.GetSubValue(0).Type()==MO_VALUE_NUM_DOUBLE) {
                        float ff = atof( (const char*)m_pTextCtrl->GetValue().c_str() );
                        rValue.GetSubValue(0).SetFloat( ff );

                    } else {
                        int ii = atoi( (const char*)m_pTextCtrl->GetValue().c_str() );
                        rValue.GetSubValue(0).SetInt( ii );
                    }
                }
                break;
            case MO_PARAM_BLENDING:
                if (m_pBlendingCtrl) {
                    int i,isel = 0;
                    wxString valuestr = m_pBlendingCtrl->GetValue();
                    for(i=0; i<MO_BLENDINGS; i++) {
                        if (blendings[i]==valuestr) {
                            isel = i;
                            break;
                        }
                    }
                    rValue.GetSubValue(0).SetInt( isel );
                }
                break;
            case MO_PARAM_POLYGONMODE:
                if (m_pPolygonModeCtrl) {
                    int i,isel = 0;
                    wxString valuestr = m_pPolygonModeCtrl->GetValue();
                    for(i=0; i<MO_POLYGONMODES; i++) {
                        if (polygonmodes[i]==valuestr) {
                            isel = i;
                            break;
                        }
                    }
                    rValue.GetSubValue(0).SetInt( isel );
                }
                break;

            case MO_PARAM_TEXTURE:
            case MO_PARAM_VIDEO:
                if (rValue.GetSubValueCount()==1) {

                    if (m_pTextCtrl) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );

                } else if ( rValue.GetSubValueCount() > 1 ) {

                    if (m_pTextCtrl)    rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                    if (m_pTextCtrlR)   rValue.GetSubValue(1).SetText( moText((char*)(wxChar*)m_pTextCtrlR->GetValue().c_str() ) );
                    if (m_pTextCtrlG)   rValue.GetSubValue(2).SetText( moText((char*)(wxChar*)m_pTextCtrlG->GetValue().c_str() ) );
                    if (m_pTextCtrlB)   rValue.GetSubValue(3).SetText( moText((char*)(wxChar*)m_pTextCtrlB->GetValue().c_str() ) );

                }
                break;
            case MO_PARAM_FONT:
                if (rValue.GetSubValueCount()>0) {
                    if (m_pTextCtrl) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                    if (m_pFontTypeCtrl) {
                        int i,isel = 0;
                        wxString valuestr = m_pFontTypeCtrl->GetValue();
                        for(i=0; i<MO_FONT_TYPES; i++) {
                            if (fonttypes[i]==valuestr) {
                                isel = i;
                                break;
                            }
                        }
                        rValue.GetSubValue(0).SetInt( isel );
                    }
                    if (m_pTextCtrlR) {
                        int ii = atoi( (const char*)m_pTextCtrlR->GetValue().c_str() );
                        rValue.GetSubValue(2).SetInt( ii );
                    }
                }
                break;
            case MO_PARAM_COLOR:
                if (m_pTextCtrlR) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrlR->GetValue().c_str() ) );
                if (m_pTextCtrlG) rValue.GetSubValue(1).SetText( moText((char*)(wxChar*)m_pTextCtrlG->GetValue().c_str() ) );
                if (m_pTextCtrlB) rValue.GetSubValue(2).SetText( moText((char*)(wxChar*)m_pTextCtrlB->GetValue().c_str() ) );
                if (m_pTextCtrl) rValue.GetSubValue(3).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                break;
            case MO_PARAM_FILTER:
                if (m_pTextCtrl) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                if (m_pTextCtrlR) rValue.GetSubValue(1).SetText( moText((char*)(wxChar*)m_pTextCtrlR->GetValue().c_str() ) );
                if (m_pTextCtrlG) rValue.GetSubValue(2).SetText( moText((char*)(wxChar*)m_pTextCtrlG->GetValue().c_str() ) );
                if (m_pTextCtrlB) rValue.GetSubValue(3).SetText( moText((char*)(wxChar*)m_pTextCtrlB->GetValue().c_str() ) );
                //rValue.GetSubValue(3).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                break;
            default:
                if (m_pTextCtrl) rValue.GetSubValue(0).SetText( moText((char*)(wxChar*)m_pTextCtrl->GetValue().c_str() ) );
                break;
        };
        SetValue( m_ValueDescriptor );
        m_pDirectorChildFrame->Inspect( m_ValueDescriptor, false );

    }

}

void
moValueCtrl::OnComboUpdated( wxCommandEvent& event) {

    if (m_bInit) {

        moValue& rValue( m_ValueDescriptor.GetValue() );
        switch( (int)m_ValueDescriptor.GetParamDescriptor().GetParamDefinition().GetType()) {
            case MO_PARAM_BLENDING:
                if (m_pBlendingCtrl) {
                    int i,isel = 0;
                    wxString valuestr = m_pBlendingCtrl->GetValue();
                    for(i=0; i<MO_BLENDINGS; i++) {
                        if (blendings[i]==valuestr) {
                            isel = i;
                            break;
                        }
                    }
                    rValue.GetSubValue(0).SetInt( isel );
                }
                break;
            case MO_PARAM_POLYGONMODE:
                if (m_pPolygonModeCtrl) {
                    int i,isel = 0;
                    wxString valuestr = m_pPolygonModeCtrl->GetValue();
                    for(i=0; i<MO_POLYGONMODES; i++) {
                        if (polygonmodes[i]==valuestr) {
                            isel = i;
                            break;
                        }
                    }
                    rValue.GetSubValue(0).SetInt( isel );
                }
                break;
            case MO_PARAM_FONT:
                if (m_pFontTypeCtrl) {
                    int i,isel = 0;
                    wxString valuestr = m_pFontTypeCtrl->GetValue();
                    for(i=0; i<MO_FONT_TYPES; i++) {
                        if (fonttypes[i]==valuestr) {
                            isel = i;
                            break;
                        }
                    }
                    if (rValue.GetSubValueCount()==3)
                        rValue.GetSubValue(1).SetInt( isel );
                    else moIDirectorActions::ErrorMessage("moValueCtrl::OnComboUpdated: value count incorrect updating combo FontType");
                }
                break;
        };
        SetValue( m_ValueDescriptor );
        m_pDirectorChildFrame->Inspect( m_ValueDescriptor, false );
    }

}

