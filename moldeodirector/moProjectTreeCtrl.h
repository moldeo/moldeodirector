/*******************************************************************************

                                moProjectTreeCtrl.h

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
	tree control of the current open project

*******************************************************************************/
#ifndef _MO_PROJECT_TREE_CTRL_
#define _MO_PROJECT_TREE_CTRL_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include <wx/treectrl.h>

class moMobItemData : public wxTreeItemData {

    public:

        moMobItemData() {
        }
        moMobItemData( const moMobDescriptor& p_MobDescriptor ) {
            m_MobDescriptor = p_MobDescriptor;
        }
        virtual ~moMobItemData() {
        }

        void SetMobDescriptor( const moMobDescriptor& p_MobDescriptor ) {
            m_MobDescriptor = p_MobDescriptor;
        }
        moMobDescriptor& GetMobDescriptor() {
            return m_MobDescriptor;
        }

    protected:

        moMobDescriptor     m_MobDescriptor;


};

class moProjectTreeCtrl : public moIDirectorActions, public wxTreeCtrl {

	public:

		moProjectTreeCtrl( wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style );


		bool Init();
		bool Finish();

  public:

        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );

        void Branchs( moMobDescriptor& p_MobDescriptor, moMobDescriptors& p_MobDescriptors );


  protected:
  		void  OnActivate(wxTreeEvent &event);
      void  OnPopMenu(wxTreeEvent &event);

      void  OnDeleteMob( wxCommandEvent& event );
      void  OnDuplicateMob( wxCommandEvent& event );
      void  OnMoveUpMob( wxCommandEvent& event );
      void  OnMoveDownMob( wxCommandEvent& event );
      void  OnAddChildMob( wxCommandEvent& event );

  private:

    wxTreeItemId rootid;
    wxTreeItemId mob_ids[ MO_OBJECT_TYPES ];

    void ResetBaseTree( wxString p_treename );

    wxMenu      m_PopMenu;
    wxTreeItemId  m_Popped;
    moMobDescriptor  m_MobSelected;


	DECLARE_EVENT_TABLE()

};

#endif

