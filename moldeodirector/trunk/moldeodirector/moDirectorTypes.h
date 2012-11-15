/*******************************************************************************

                                moDirectorTypes.h

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
	general definitions

*******************************************************************************/
#ifndef _MO_DIRECTOR_TYPES
#define _MO_DIRECTOR_TYPES

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers(this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "moTypes.h"

#define MOLDEO_DIRECTOR_VERSION "7.8.0.0"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------


class moGLCanvas;
class moDirectorConsole;
class moDirectorChildConsole;
class moDirectorCore;
class moDirectorFrame;
class moDirectorChildFrame;
class moEffectConfig;
class moIDirectorActions;
class moProjectTreeCtrl;
class moSessionProject;

#include "moConsole.h"

#ifdef wxUSE_UNICODE
	#define moText2Wx(X) wxString::FromAscii((char*)(moText)X)
	#define moWx2Text(X) moText(X.ToAscii())
#else
	#define moText2Wx(X) (wxChar*)(char*)moText(X)
	#define moWx2Text(X) moText((char*)(wxChar*)X.c_str())
#endif

// IDs for the controls and the menu commands
enum
{
    // menu items
    MODIRECTOR_QUIT = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    //(where it is special and put into the "Apple" menu)
    MODIRECTOR_ABOUT = wxID_ABOUT,
	MODIRECTOR_NEWPROJECT = 9913,
	MODIRECTOR_OPENPROJECT = 9914,
	MODIRECTOR_CLOSEPROJECT = 9915,
	MODIRECTOR_SAVEPROJECT = 9916,

    MODIRECTOR_EXAMPLES = 9917,

	MODIRECTOR_NEWPREEFFECT = 9926,
	MODIRECTOR_NEWEFFECT = 9927,
	MODIRECTOR_NEWPOSTEFFECT = 9928,
	MODIRECTOR_NEWIODEVICE = 9929,
	MODIRECTOR_NEWRESOURCE = 9930,

	MODIRECTOR_SAVEMOB = 9940,
	MODIRECTOR_SAVEALL = 9941,
	MODIRECTOR_CLOSEMOB = 9942,
	MODIRECTOR_CLOSEALL = 9943,
	MODIRECTOR_OPENMOB = 9944,
	MODIRECTOR_IMPORTMOB = 9945,
	MODIRECTOR_DELETEMOB = 9946,
	MODIRECTOR_DUPLICATEMOB = 9947,
	MODIRECTOR_RENAMEMOB = 9948,
	MODIRECTOR_MOVEUPMOB = 9949,
	MODIRECTOR_MOVEDOWNMOB = 9950,

    MODIRECTOR_PREFERENCES = 9960,

	MODIRECTOR_PROJECT_PREVIEW = 9980,
	MODIRECTOR_PROJECT_PREVIEW_FULLSCREEN = 9981,
	MODIRECTOR_FULLSCREEN = 9982,
	MODIRECTOR_CONFIGURATION = 9983,
	MODIRECTOR_LOG = 9984,
	MODIRECTOR_COMMAND = 9990,

  MODIRECTOR_EXAMPLE_START = 10009,
  MODIRECTOR_EXAMPLE_END = 11009,
	MODIRECTOR_EXAMPLE_SIMPLE = 11010,
  MODIRECTOR_EXAMPLE_CAMERA = 11020,
  MODIRECTOR_EXAMPLE_CAMERA_CIRCULAR_BUFFER = 11021,
  MODIRECTOR_EXAMPLE_VIDEO_BUFFER = 11022,

  MODIRECTOR_EXAMPLE_PARTICLES_EXAMPLE = 11023,
  MODIRECTOR_EXAMPLE_PARTICLES_EXAMPLE_BOUNCE = 11024,
  MODIRECTOR_EXAMPLE_PARTICLES_INTERACTIVE = 11025,

  MODIRECTOR_EXAMPLE_PARTICLES_GRID = 11030,
  MODIRECTOR_EXAMPLE_PARTICLES_SPHERE = 11031,
  MODIRECTOR_EXAMPLE_PARTICLES_CYLINDER = 11032,
  MODIRECTOR_EXAMPLE_PARTICLES_JET = 11033,
  MODIRECTOR_EXAMPLE_PARTICLES_POINT = 11034,
  MODIRECTOR_EXAMPLE_PARTICLES_SPIRAL = 11035,

	MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA = 11039,
	MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU = 11040,
  MODIRECTOR_EXAMPLE_INTERACTIVE_CAMERA_GPU_KLT2 = 11050


};

#endif
