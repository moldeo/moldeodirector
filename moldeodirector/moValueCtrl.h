/*******************************************************************************

                                moValueCtrl.h

  ****************************************************************************
  *                                                                          *
  *   This source is free software; you can redistribute it and/or modify    *
  *   it under the terms of the GNU General Public License as published by   *
  *   the Free Software Foundation; either version 2 of the License, or      *
  *  (at your option) any later version.                                    *
  *                                                                          *
  *   This code is distributed in the hope that it will be useful, but       *
  *   WITHOUT ANY WARRANTY; without even the implied warranty of             *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
  *   General Public License for more details.                               *
  *                                                                          *
  *   A copy of the GNU General Public License is available on the World     *
  *   Wide Web at <http://www.gnu.org/copyleft/gpl.html>. You can also       *
  *   obtain it by writing to the Free Software Foundation,                  *
  *   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         *
  *                                                                          *
  ****************************************************************************

  Copyright(C) 2006 Fabricio Costa

  Authors:
  Fabricio Costa

  Description:
	moValue Control

*******************************************************************************/

#ifndef _MO_DIRECTOR_VALUECTRL_
#define _MO_DIRECTOR_VALUECTRL_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "moDirectorChildFrame.h"
#include <wx/tglbtn.h>

#define MO_OPTIONS_MAX 1024

class moValueCtrl : public wxPanel, public moIDirectorActions {

	public:
		moValueCtrl(wxWindow *parent,
            int x = 0, int y = 0, int width = 400, int height = 24,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxPanelNameStr);

		void Init( moDirectorChildFrame* parent, moValueDescriptor p_valuedescriptor );
		void Set(moValueDescriptor p_valuedescriptor);

        void OnParamToggleClick(  wxCommandEvent& event );
        void OnInspectorClick(  wxCommandEvent& event );
        void OnAddClick(  wxCommandEvent& event );
        void OnDeleteClick(  wxCommandEvent& event );

        void OnTextUpdated( wxCommandEvent& event);
        void OnSpinUpdated( wxSpinEvent& event);
        void OnComboUpdated( wxCommandEvent& event);
        void OnFocus( wxFocusEvent& event);

        void ParamToggleOff();
        void ParamToggleOn();

        moValueDescriptor& GetValueDescriptor() {
                return m_ValueDescriptor;
        }

    protected:

        wxSpinCtrl* m_pSpinCtrl;
        wxComboBox* m_pBlendingCtrl;
        wxComboBox* m_pPolygonModeCtrl;
        wxComboBox* m_pFontTypeCtrl;
        wxComboBox* m_pOptionsCtrl;

        wxTextCtrl* m_pTextCtrl;
        wxTextCtrl*	m_pTextCtrlR;
        wxTextCtrl*	m_pTextCtrlG;
        wxTextCtrl*	m_pTextCtrlB;

        wxRadioButton*	m_pParamToggle;
        wxButton*	m_pInspectorButton;
        wxButton*	m_pAddButton;
        wxButton*	m_pDeleteButton;

        moDirectorChildFrame* m_pDirectorChildFrame;
        moValueDescriptor m_ValueDescriptor;

        wxString blendings[MO_BLENDINGS];
        wxString polygonmodes[MO_POLYGONMODES];
        wxString fonttypes[MO_FONT_TYPES];
        wxString options[MO_OPTIONS_MAX];

        bool    m_bInit;
        bool block;

    DECLARE_EVENT_TABLE()
};

#endif



