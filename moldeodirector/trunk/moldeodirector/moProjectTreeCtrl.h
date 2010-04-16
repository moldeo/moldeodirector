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
  Andrés Colubri

  Description:
	tree control of the current open project

*******************************************************************************/
#ifndef _MO_PROJECT_TREE_CTRL_
#define _MO_PROJECT_TREE_CTRL_

#include "moDirectorTypes.h"
#include "moDirectorFrame.h"
#include "moIDirectorActions.h"

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
        moMobDescriptor GetMobDescriptor() {
            return m_MobDescriptor;
        }

    protected:

        moMobDescriptor     m_MobDescriptor;


};

class moProjectTreeCtrl : public wxTreeCtrl {

	public:

		moProjectTreeCtrl( wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style );
		void OnActivate(wxTreeEvent &event);

		bool Init();
		bool Finish();

		void SetDirectorFrame( moDirectorFrame* p_pDirectorFrame ) { m_pDirectorFrame = p_pDirectorFrame; }

	private:
		moDirectorFrame*		m_pDirectorFrame;

	DECLARE_EVENT_TABLE()

};

#endif
