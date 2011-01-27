#ifndef MO_LOGNOTEBOOK_H_INCLUDED
#define MO_LOGNOTEBOOK_H_INCLUDED

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "wxMoldeoControls.h"

#include <wx/aui/auibook.h>

class moLogTextCtrl : public wxTextCtrl, public moIDirectorActions {

  public:

    moLogTextCtrl(wxWindow* parent, wxWindowID id);
    virtual ~moLogTextCtrl();

  public:
        //===========================================
        // INTERFACE DIRECTOR ACTIONS IMPLEMENTED
        //===========================================

        virtual void Log( moText p_message );
        virtual void LogError( moText p_message );

};

class moLogNotebook : public wxAuiNotebook, public moIDirectorActions {

	public:

		moLogNotebook( wxWindow* parent, wxWindowID id );
		virtual ~moLogNotebook() {}

  public:
        ///===========================================
        /// INTERFACE DIRECTOR ACTIONS IMPLEMENTED
        ///===========================================

        virtual void Log( moText p_message );
        virtual void LogError( moText p_message );

  private:

    moLogTextCtrl*      m_pLogBase;
    moLogTextCtrl*      m_pLogError;
    moLogTextCtrl*      m_pLogStdout;

  public:

  DECLARE_EVENT_TABLE()

};


#endif // MOEXPLORERNOTEBOOK_H_INCLUDED
