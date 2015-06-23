/*******************************************************************************

                                moDirectorCore.h

  ****************************************************************************
  *                                                                          *
  *   This source is free software; you can redistribute it and/or modify    *
  *   it under the terms of the GNU General Public License as published by   *
  *   the Free Software Foundation; either version 2 of the License, or      *
  *  (at your option) any later version.                                     *
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
	Core functions

*******************************************************************************/
#ifndef _MO_DIRECTOR_CORE_
#define _MO_DIRECTOR_CORE_

#include "moDirectorTypes.h"
#include "moDirectorIODeviceManager.h"
#include "moIDirectorActions.h"
#include "moDirectorFrame.h"
#include "moDirectorConsole.h"

enum moAppParamIndex {
    CORE_INSTALLATIONPATH,
    CORE_CONFIGURATIONPATH,
    CORE_PLUGINSPATH,
    CORE_LASTPROJECTS,
    CORE_OPENFILES,
    CORE_AUTOSAVE,
    CORE_EXECUTIONS,
    CORE_SPLASHSCREEN,
    CORE_3DLOGO
};

class moDirectorCore : public moIDirectorActions, public moAbstract {

public:

	moDirectorCore();
	virtual ~moDirectorCore();

    MOboolean        Init();
	void		SetUserInterface( moDirectorFrame* p_pUserInterface );
	void        SetPaths( moText p_installationpath, moText p_configurationpath, moText p_pluginspath, moText p_datapath );
    void        LoadPlugins( moPluginDefinitions& rPluginDefs, moText plugindir, moMoldeoObjectType mobjecttype );


	moResourceManager* GetResourceManager();
	moConsole*  GetDirectorConsole() {
        return (moConsole*)m_pDirectorConsole;
	}

	moDirectorIODeviceManager*      GetDirectorIODeviceManager() { return m_pDirectorIODeviceManager; }

    moDirectorConsole*			m_pDirectorConsole;


public:

//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================

	moDirectorStatus Preview();
	moDirectorStatus FullScreen(bool force=false);
	moDirectorStatus ConsoleLoop();
	void ViewSwapBuffers();
	MO_HANDLE GetHandle();
	moDirectorStatus SetView( int x, int y, int w, int h );

	moDirectorStatus Play();
	moDirectorStatus Pause();
	moDirectorStatus Stop();
	moDirectorStatus Seek( MOulong p_timecode );

	moDirectorStatus SaveSession();

	moDirectorStatus FocusOutput();

	moDirectorStatus SaveAll();
	moDirectorStatus CloseAll();
	moDirectorStatus CloseApp();



	moApplicationDescriptor GetApplicationDescriptor();

//================================================================
//Project
//================================================================
	moDirectorStatus NewProject( const moProjectDescriptor& p_projectdescriptor );
	moDirectorStatus OpenProject( const moProjectDescriptor& p_projectdescriptor );
	moDirectorStatus CloseProject();
	moDirectorStatus SaveProject();
	moDirectorStatus SaveAsProject( moText p_configname, moText p_configpath );
	moDirectorStatus ProjectUpdated( const moProjectDescriptor& p_projectdescriptor );

	moDirectorStatus SetProject( const moProjectDescriptor& p_projectdescriptor );
	const moProjectDescriptor& GetProject();
	moDirectorStatus ReloadProject();

	moDirectorStatus ProjectPreview( );
	moDirectorStatus EffectPreview( MOint p_n );

	virtual moMobDescriptors GetMobDescriptors();

//================================================================
//Resources
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

  moDirectorStatus AddChildMob( moMobDescriptor p_MobDesc, moMobDescriptor p_MobDescFather );


	moDirectorStatus NewMob( moMobDescriptor p_MobDesc );
	moDirectorStatus EditMob( moMobDescriptor p_MobDesc );
	moDirectorStatus SaveMob( moMobDescriptor p_MobDesc );
	moDirectorStatus DeleteMob( moMobDescriptor p_MobDesc );
	moMobDescriptor GetMob( moMobDescriptor p_MobDesc );
	moDirectorStatus SetMob( moMobDescriptor p_MobDesc );
	moDirectorStatus DuplicateMob( moMobDescriptor p_MobDesc );
	moDirectorStatus MoveMob( moMobDescriptor p_MobDesc, int position );
	moDirectorStatus MobUpdated( moMobDescriptor p_MobDesc );

	moParameterDescriptors  GetParameterDescriptors( moMobDescriptor p_MobDesc );

//================================================================
//PARAMETERS
//================================================================

	moDirectorStatus NewParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus InsertParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus MoveParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus EditParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus SaveParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus SetParameter( moParameterDescriptor p_ParameterDesc );
	moParameterDescriptor GetParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus DeleteParameter( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus ParameterUpdated( moParameterDescriptor p_ParameterDesc );
	moDirectorStatus ReloadParameter( moParameterDescriptor p_ParameterDesc );

	moValueDescriptors  GetValueDescriptors( moParameterDescriptor p_ParamDesc );

//================================================================
// VALUES
//================================================================

	moDirectorStatus NewValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus InsertValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus EditValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus SaveValue( moValueDescriptor p_ValueDesc );
	moValueDescriptor GetValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus SetValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus DeleteValue( moValueDescriptor p_ValueDesc );
	moDirectorStatus ValueUpdated( moValueDescriptor p_ValueDesc );
	moDirectorStatus ReloadValue( moValueDescriptor p_ValueDesc );

//===============================================================
// LOGS
//===============================================================

	void Log( moText p_message );
	void LogError( moText p_message );
	void ShowMessage( moText p_message );
	bool ConfirmMessage( moText p_message );
	void AlertMessage( moText p_message );
	void ErrorMessage( moText p_message );


    moConfigDefinition * GetDefinition( moConfigDefinition *p_configdefinition = NULL );//retreive the parameters definition of the Moldeo Object


/*
	void ShowError( moText p_messageerror );
	void ShowLog( moText p_messageerror );
*/
protected:

    virtual void LoadDefinition();

	moDirectorFrame*			m_pUserInterface;

	moDirectorIODeviceManager*	m_pDirectorIODeviceManager;

    moApplicationDescriptor     m_ApplicationDescriptor;

	moResourceManager*			m_pResourceManager;
	moConfig					m_Config;

};

#endif
