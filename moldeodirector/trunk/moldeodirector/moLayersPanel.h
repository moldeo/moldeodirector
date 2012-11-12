#ifndef MOLAYERSPANEL_H_INCLUDED
#define MOLAYERSPANEL_H_INCLUDED

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

#include "moTimelineRuler.h"
#include "moLayersTreeCtrl.h"
#include <wx/splitter.h>

class moLayersPanelCtrl : public wxPanel, public moIDirectorActions {

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
        moLayersTreeCtrl*   m_pLayersTreeCtrl;
        wxPanel*            m_pLayersBottomCtrl;

        void SashPosition( wxSplitterEvent& event );
        void SashDClick( wxSplitterEvent& event );
        void SashChanged( wxSplitterEvent& event );
        void ScrollTimeline( wxScrollEvent& event );

    public:
        //===============================
        // INTERFACE DIRECTOR ACTIONS
        //===============================

        virtual moDirectorStatus    ValueUpdated( moValueDescriptor p_ValueDesc );
        virtual moDirectorStatus    ParameterUpdated( moParameterDescriptor p_ParameterDesc );
        virtual moDirectorStatus    MobUpdated( moMobDescriptor p_MobDesc );
        virtual moDirectorStatus    ProjectUpdated( const moProjectDescriptor& p_ProjectDescriptor );
        virtual moDirectorStatus    SetMob( moMobDescriptor p_MobDesc );

    protected:

    DECLARE_EVENT_TABLE()

};

#endif // MOLAYERSTREEPANEL_H_INCLUDED

