/*******************************************************************************

                                moTreeObjectsLayerCtrl.h

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


*******************************************************************************/
#ifndef _MO_LAYERSTREE_CTRL
#define _MO_LAYERSTREE_CTRL

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "wxTreeMultiCtrl.h"
#include "moLayerEffectCtrl.h"
#include "moTimelineRuler.h"

/**
*
* Este arbol multiple contendra los layers de los efectos, sus controles, lineas de tiempo, etc...
*
*/

class moLayersTreeCtrl : public wxTreeMultiCtrl, public moIDirectorActions {

	public:

		moLayersTreeCtrl(wxWindow *parent, wxWindowID id = -1,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxTMC_DEFAULT_STYLE,
                        const wxValidator &validator = wxDefaultValidator,
                        const wxString& name = wxTreeMultiCtrlNameStr) : wxTreeMultiCtrl(parent, id,
						pos, size, style, validator, name)
		{

        }

		MOboolean Init();
		MOboolean Finish();
		void AddLayer( wxTreeMultiItem id, moItemLayerWindow* p_ObjectLayerCtrl );

    public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    ParameterUpdated( moParameterDescriptor p_ParameterDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );
        moDirectorStatus            SetMob( moMobDescriptor p_MobDesc );


    public:

        void    SetSplitPosition( int position );
        void    SetScrollPosition( int position );


        moItemLayerWindow* FindObjectByMob( moMobDescriptor p_MobDesc, TreeMultiItemNode *n=NULL );

    private:

        wxTreeMultiItem  mob_ids[ MO_OBJECT_TYPES ];

};

#endif

