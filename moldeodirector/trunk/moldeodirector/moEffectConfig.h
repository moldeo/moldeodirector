/*******************************************************************************

                                moEffectConfig.h

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
	effect's and device's configuration

*******************************************************************************/
#ifndef _MO_MOBCONFIG_
#define _MO_MOBCONFIG_

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

class moMobConfig {

public:

	bool Init( moMobDescriptor p_MobDescriptor );
	bool LoadConfig( moMobDescriptor p_MobDescriptor ); //load a console.cfg file with their effects.cfg
	bool UnloadConfig();
	bool SaveConfig(); //save a console.cfg file with their effects.cfg
	bool SaveAsConfig( moText p_confignewname ); //save a console.cfg file with their effects.cfg
	bool IsConfigLoaded();
	bool Finish();

	void SetConfigFullText();

	void SetMobDescriptor( moMobDescriptor p_MobDescriptor );
	moMobDescriptor GetMobDescriptor( moMobDescriptor p_MobDescriptor );

private:

	moMobDescriptor		m_MobDescriptor;

	moConfig m_Config;
	//moXMLConfig *m_ConfigXML;
};

#endif
