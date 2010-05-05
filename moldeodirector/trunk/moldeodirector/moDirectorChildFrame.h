/*******************************************************************************

                                moDirectorChildFrame.h

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
	MDI child frame

*******************************************************************************/

#ifndef _MO_DIRECTOR_CHILD_FRAME_
#define _MO_DIRECTOR_CHILD_FRAME_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "moDirectorFrame.h"

#include "treemultictrl/wxTreeMultiCtrl.h"
#include "wx/sizer.h"
#include <wx/tglbtn.h>
#include <wx/aui/auibook.h>

class moConfigNotebook : public wxAuiNotebook {
	public:
		moConfigNotebook( wxWindow* parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style=0) : wxAuiNotebook(parent, id, pos, size, style) { }
};

class moConfigTextCodeCtrl : public wxTextCtrl {
	public:
		moConfigTextCodeCtrl(wxWindow* parent, wxWindowID idconst, const wxString& value, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0 ) : wxTextCtrl(parent, idconst, value, pos, size, style) {
		    }
};


class moConfigParameterFoldbar : public wxPanel {//wxFoldbar
	public:
		moConfigParameterFoldbar(wxWindow* parent, wxWindowID id) : wxPanel( parent, id) { }
};

class moParameterRoot : public TreeMultiItemRoot {

};

class moParametersTree : public wxTreeMultiCtrl {
	public:
		moParametersTree(wxWindow* parent, wxWindowID id) : wxTreeMultiCtrl( parent, id) { }

};


class moValueTreeItem {

    public:
        moValueTreeItem() {
            m_ValueCtrl = NULL;
        }
        moValueTreeItem( wxTreeMultiItem item, moValueDescriptor p_descriptor, wxWindow* pcontrol ) {
            m_Item = item;
            m_ValueDescriptor = p_descriptor;
            m_ValueCtrl = pcontrol;
        }
        wxWindow* GetWindow() {
            return m_ValueCtrl;
        }
        moValueDescriptor GetDescriptor() {
            return m_ValueDescriptor;
        }
        wxTreeMultiItem GetItem() {
            return m_Item;
        }
    private:

        moValueDescriptor m_ValueDescriptor;
        wxWindow*   m_ValueCtrl;
        wxTreeMultiItem m_Item;

};

moDeclareDynamicArray( moValueTreeItem, moValueTreeItemList )

class moParamTreeItem {

    public:
        moParamTreeItem() {}
        moParamTreeItem( moParameterDescriptor p_descriptor,  wxTreeMultiItem p_item ) {
            m_ParamDescriptor = p_descriptor;
            item = p_item;
        }

        moValueTreeItemList& GetValueTreeItemList() {
            return m_ValueTreeItemList;
        }

        moParameterDescriptor& GetParamDescriptor() {
            return m_ParamDescriptor;
        }
        wxTreeMultiItem GetItem() {
                return item;
        }


    private:
        moValueTreeItemList   m_ValueTreeItemList;
        moParameterDescriptor m_ParamDescriptor;
        wxTreeMultiItem item;
};

moDeclareDynamicArray( moParamTreeItem, moParamTreeItemList )


// Define a new frame type: this is going to be our main frame
class moDirectorChildFrame : public wxPanel, public moIDirectorActions
{

public:
    moDirectorChildFrame( wxWindow* parent, const wxString& title);
    virtual ~moDirectorChildFrame();

	MOboolean Init(  moDirectorFrame* pDirectorFrame, moMobDescriptor p_MobDescriptor );
	MOboolean Finish();

    void OnQuit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnFocus(wxFocusEvent& event);
    void OnSize(wxSizeEvent& event);

    void Inspect( moValueDescriptor p_ValueDescriptor, bool setselection = false );
    void Save();
    bool Close();

public:

	bool	IsMob( moMobDescriptor p_MobDescriptor );
	moText	GetConfigName() { return m_ConfigFullName; }

	moDirectorStatus ParameterUpdated( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus EditParameter( moParameterDescriptor p_ParameterDesc );

	moDirectorStatus EditValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus DeleteValue( moValueDescriptor p_ValueDesc );
    moDirectorStatus ValueUpdated( moValueDescriptor p_ValueDesc );


//interface controls
private:

	moMobDescriptor				m_MobDescriptor;

	moConfigNotebook*			m_pConfigNotebook;
	moConfigTextCodeCtrl*		m_pConfigTextCodeCtrl;
	moConfigParameterFoldbar*	m_pConfigParameterFoldbar;
	moParametersTree*			m_pParameterTree;

	wxPanel*					m_pPreview;
	wxPanel*					m_pConnection;



//Action connectors
private:
	moIDirectorActions*			m_pDirectorFrame;
	moParamTreeItemList         m_ParamTreeItemList;

//child members
	moMoldeoObjectType			m_ConfigType;
	MOint						m_nPosition;
	moText						m_ConfigName;
	moText						m_ConfigFullName;

    wxColour                    m_cForeground;
    wxColour                    m_cBackground;

    DECLARE_EVENT_TABLE()
};

#endif
