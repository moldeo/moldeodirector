/*******************************************************************************

                                moDirectorIODeviceManager.h

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
	based on moIODeviceManager.h, overwrite PollEvents to catch wxEvents...

*******************************************************************************/
#ifndef _MO_DIRECTORIODEVICEMANAGER_
#define _MO_DIRECTORIODEVICEMANAGER_

#include "moDirectorTypes.h"
#include <wx/event.h>

class moDirectorIODeviceManager : public wxEvtHandler, public moIODeviceManager {

public:

	moDirectorIODeviceManager();
	virtual ~moDirectorIODeviceManager();

	virtual void PollEvents();//overwrite the default one based on SDL

private:

	moEventList		m_AuxEvents;
	long m_MouseX,m_MouseY;
	void OnMouseEvent( wxMouseEvent &event );
	void OnKeyUp( wxKeyEvent &event );
	void OnKeyDown( wxKeyEvent &event );

	DECLARE_EVENT_TABLE()
};

#endif
