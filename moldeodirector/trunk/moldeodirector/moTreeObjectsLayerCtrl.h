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
#ifndef _MO_TREEOBJECTSLAYER_CTRL
#define _MO_TREEOBJECTSLAYER_CTRL

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "wxTreeMultiCtrl.h"
#include "moEffectLayerCtrl.h"
#include "moTimelineRuler.h"

class moTreeLayerCtrl : public wxTreeMultiCtrl, public moIDirectorActions {

	public:

		moTreeLayerCtrl(wxWindow *parent, wxWindowID id = -1,
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

        moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );

    /*
		moObjectLayerCtrls m_pPreEffectsLayers;
		moObjectLayerCtrls m_pEffectsLayers;
		moObjectLayerCtrls m_pPostEffectsLayers;*/

        void    SetSplitPosition( int position );
        void    SetScrollPosition( int position );


        moItemLayerWindow* FindObjectByMob( moMobDescriptor p_MobDesc, TreeMultiItemNode *n=NULL );

};

/*
class moLayersPanelCtrl : public wxSplitterWindow {

    public:
        moLayersPanelCtrl( wxWindow *parent, wxWindowID id,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxSP_3D,
                        const wxString& name = wxTreeMultiCtrlNameStr );
        virtual ~moLayersPanelCtrl() {
        }

    protected:

    DECLARE_EVENT_TABLE()

};
*/



class moLayersPanelCtrl : public wxPanel {

    public:
        moLayersPanelCtrl( wxWindow *parent, wxWindowID id,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxNO_BORDER,
                        const wxString& name = _("LayersPanel") );
        virtual ~moLayersPanelCtrl() {
        }

        wxSplitterWindow*   TopSplitter;
        wxSplitterWindow*   BottomSplitter;

        wxWindow*           m_pTimelineRulerWindow;
        moTimelineRuler*    m_pTimelineRuler;

        wxScrollBar*        ScrollBar;

        wxPanel*            m_pLayersTopCtrl;
        moTreeLayerCtrl*    m_pLayersTreeCtrl;
        wxPanel*            m_pLayersBottomCtrl;

        void SashPosition( wxSplitterEvent& event );
        void SashDClick( wxSplitterEvent& event );
        void SashChanged( wxSplitterEvent& event );
        void ScrollTimeline( wxScrollEvent& event );


    protected:

    DECLARE_EVENT_TABLE()

};

#endif
