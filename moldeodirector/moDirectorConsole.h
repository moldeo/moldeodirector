/*******************************************************************************

                                moDirectorConsole.h

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
	based on moConsole.h, but using wxGLCanvas context, not SDL context

*******************************************************************************/

#ifndef _MO_DIRECTORCONSOLE_
#define _MO_DIRECTORCONSOLE_

#include "moDirectorTypes.h"
#include "moGLCanvas.h"
#include "moIDirectorActions.h"
#include "moDirectorIODeviceManager.h"
#include "moDirectorCore.h"
#include <moPreConfig.h>

#define TICKS_ID 333

class moDirectorConsole : public wxEvtHandler, public moConsole, public moIDirectorActions {

public:

	moDirectorConsole();
	virtual ~moDirectorConsole();
	MOboolean Finish();

	void Draw();

	void OnTimer(wxTimerEvent &event);

	void FullReset() {}
	void ResetEffect( MOint p_n ) {}
	void ResetPreEffect( MOint p_n ) {}
	void ResetPostEffect( MOint p_n ) {}
	void ResetMasterEffect( MOint p_n ) {}
	void ResetIODevice( MOint p_n ) {}

	void SetDirectorCore( moDirectorCore* p_pDirectorCore );

	moMoldeoObject* GetObject( moMobDescriptor p_MobDesc );
  moMoldeoObject* GetObjectByIdx( int p_object_id );

//================================================================
// Effects states
//================================================================

    moDirectorStatus AddPreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc );


//================================================================
//Project
//================================================================

    moDirectorStatus ConsoleLoop();
    moDirectorStatus SetView( int x, int y, int w, int h );

	moDirectorStatus Play();
	moDirectorStatus Stop();
	moDirectorStatus Pause();
	moDirectorStatus Seek( MOulong p_timecode );
	moDirectorStatus SaveSession();
	moDirectorStatus Render();

	moDirectorStatus NewProject( const moProjectDescriptor& p_ProjectDes );
	moDirectorStatus OpenProject( const moProjectDescriptor& p_ProjectDes );
	moDirectorStatus CloseProject();
	moDirectorStatus SaveProject();
	moDirectorStatus SaveAsProject( moText p_configname, moText p_configpath );

	moDirectorStatus SetProject( const moProjectDescriptor& p_ProjectDes );
	const moProjectDescriptor& GetProject();
	moDirectorStatus ReloadProject();
	virtual moMobDescriptors GetMobDescriptors();

//================================================================
//Resource
//================================================================

    moResourceDescriptor GetResourceDescriptor( moResourceDescriptor p_ResourceDescriptor );
    moResourceDescriptors GetResourceDescriptors(  moResourceType p_ResourceType  );

//================================================================
//MOB Moldeo Object
//================================================================

	moDirectorStatus ImportMob( moText p_filename );

	moDirectorStatus OpenMob( moMobDescriptor p_MobDesc );
	moDirectorStatus CloseMob( moMobDescriptor p_MobDesc );
	moDirectorStatus ReloadMob( moMobDescriptor p_MobDesc );
	moDirectorStatus NewMob( moMobDescriptor p_MobDesc );
	moDirectorStatus EditMob( moMobDescriptor p_MobDesc );
	moDirectorStatus SaveMob( moMobDescriptor p_MobDesc );
	moDirectorStatus DeleteMob( moMobDescriptor p_MobDesc );
	moDirectorStatus MoveMob( moMobDescriptor p_MobDesc, int position );
	moDirectorStatus AddChildMob( moMobDescriptor p_MobDesc, moMobDescriptor p_MobDescFather );
	moDirectorStatus DuplicateMob( moMobDescriptor p_MobDesc );
	moMobDescriptor GetMob( moMobDescriptor p_MobDesc );
	virtual moDirectorStatus SetMob( moMobDescriptor p_MobDesc );

    moParameterDescriptors  GetParameterDescriptors( moMobDescriptor p_MobDesc);

//================================================================
//Parameter
//================================================================
    moDirectorStatus    SetParameter( moParameterDescriptor  p_ParameterDesc );
    moValueDescriptors  GetValueDescriptors( moParameterDescriptor p_ParamDesc );

//================================================================
//Values
//================================================================
    moDirectorStatus InsertValue( moValueDescriptor p_ValueDesc );
    moDirectorStatus DeleteValue( moValueDescriptor p_ValueDesc );
    moDirectorStatus SaveValue( moValueDescriptor p_ValueDesc );
    moDirectorStatus SetValue( moValueDescriptor p_ValueDesc );
    moValueDescriptor GetValue( moValueDescriptor p_ValueDesc );

	MOulong m_timerticks;
/*
	virtual const moText& ToJSON() {
    return moConsole::ToJSON();
	}
	*/

protected:
	MOulong GetTicks();
	void GLSwapBuffers();
	void GUIYield();

    bool previewreset;
    bool previewreset2;

protected:

	moDirectorCore*	m_pDirectorCore;
	moProjectDescriptor     m_ProjectDescriptor;

	wxTimer		m_timer;

	DECLARE_EVENT_TABLE()

};

#endif
