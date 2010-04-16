/*******************************************************************************

                                moSessionProject.h

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
	contains the session project structure from current console.mol.
	internal storage of effect's configurations.

*******************************************************************************/
#ifndef _MO_SESSIONPROJECT_
#define _MO_SESSIONPROJECT_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"
#include "moDirectorCore.h"
#include "moMobConfig.h"

class moSessionProject : public moIDirectorActions {

public:

	moSessionProject();
	~moSessionProject();

	void			Init( );
	void			SetDirectorCore( moDirectorCore* p_pDirectorCore );
	void			Finish();

public:

//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================

	//moDirectorStatus Preview();
	//moDirectorStatus SaveAll();
	//moDirectorStatus CloseAll();

//================================================================
//Project
//================================================================
	moDirectorStatus NewProject( moProjectDescriptor p_projectdescriptor );
	moDirectorStatus OpenProject( moProjectDescriptor p_projectdescriptor );
	moDirectorStatus CloseProject();
	moDirectorStatus SaveProject();
	moDirectorStatus SaveAsProject( moText p_configname, moText p_configpath );

	moDirectorStatus SetProject( moProjectDescriptor p_projectdescriptor );
	moProjectDescriptor GetProject();
	moDirectorStatus ReloadProject();

//================================================================
//MOB Moldeo Object
//================================================================

	moDirectorStatus OpenMob( moMobDescriptor p_MobDesc );
	moDirectorStatus CloseMob( moMobDescriptor p_MobDesc );
	moDirectorStatus ReloadMob( moMobDescriptor p_MobDesc );
	moDirectorStatus NewMob( moMobDescriptor p_MobDesc );
	moDirectorStatus EditMob( moMobDescriptor p_MobDesc );
	moDirectorStatus SaveMob( moMobDescriptor p_MobDesc );
	moDirectorStatus DeleteMob( moMobDescriptor p_MobDesc );
	moMobDescriptor GetMob( moMobDescriptor p_MobDesc );
	moDirectorStatus SetMob( moMobDescriptor p_MobDesc );

	moDirectorStatus AddMobToProject( moMobDescriptor p_MobDesc );
	moDirectorStatus RemoveMobToProject( moMobDescriptor p_MobDesc );
	moDirectorStatus MoveMobInProject( moMobDescriptor p_MobDesc );


private:

	void				LoadMobs();
	void				UnloadMobs();

	moDirectorCore*		m_pDirectorCore;

	moConfig			m_ConsoleConfig;

	moMobConfig*		m_pMobs[ MO_OBJECT_TYPES ];

	//PATHS
	moProjectDescriptor	m_ProjectDescriptor;


};

#endif
