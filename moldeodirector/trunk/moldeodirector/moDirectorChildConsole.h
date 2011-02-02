/*******************************************************************************

                                moDirectorChildConsole.h

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
	based on moDirectorConsole.h, same but just for one effect preview

*******************************************************************************/
#ifndef _MO_DIRECTORCHILDCONSOLE_
#define _MO_DIRECTORCHILDCONSOLE_

#include "moDirectorTypes.h"
#include "moDirectorConsole.h"

class moDirectorChildConsole : public moDirectorConsole {

public:

	moDirectorChildConsole();
	~moDirectorChildConsole();

	moText m_EffectConfigName;
	moText m_EffectName;

	//from moConsole
	MOboolean Init( moText p_effectname,
		moText p_effectconfigname,
		moText p_apppath,
		moText p_datapath,
		moText p_consoleconfig,
		moIODeviceManager* p_pIODeviceManager = NULL,
		moResourceManager *p_pResourceManager = NULL,
		MOint p_render_to_texture_mode = MO_RENDER_TO_TEXTURE_FBOBJECT,
		MOint p_screen_width = MO_DEF_SCREEN_WIDTH, MOint p_screen_height = MO_DEF_SCREEN_HEIGHT,
		MOint p_render_width = MO_DEF_RENDER_WIDTH, MOint p_render_height = MO_DEF_RENDER_HEIGHT);
	MOboolean Init(
                    moText p_apppath,
                        moText p_datapath,
						moText p_consoleconfig,
						moIODeviceManager* p_pIODeviceManager = NULL,
						moResourceManager *p_pResourceManager = NULL,
		               MOint p_render_to_texture_mode = MO_RENDER_TO_TEXTURE_FBOBJECT,
					   MOint p_screen_width = MO_DEF_SCREEN_WIDTH, MOint p_screen_height = MO_DEF_SCREEN_HEIGHT,
					   MOint p_render_width = MO_DEF_RENDER_WIDTH, MOint p_render_height = MO_DEF_RENDER_HEIGHT);
	//MOboolean Init( moText consoleconfigname, moIODeviceManager* p_pIODeviceManager );

	void FullReset() { }


};

#endif
