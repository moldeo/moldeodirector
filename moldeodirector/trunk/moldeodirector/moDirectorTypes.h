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
  Andrés Colubri

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
//#ifndef WX_PRECOMP
//    #include "wx/wx.h"
//#endif

#include "moTypes.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

//#include "wx/app.h"
//#include "wx/grid.h"
//#include "wx/treectrl.h"
//#include "wx/spinctrl.h"
//#include "wx/artprov.h"
//#include "wx/clipbrd.h"
//#include "wx/image.h"
//#include "wx/colordlg.h"
//#include "wx/wxhtml.h"
//#include "wx/imaglist.h"
//#include "wx/dataobj.h"
//#include "wx/dcclient.h"
//#include "wx/bmpbuttn.h"
//#include "wx/menu.h"
//#include "wx/toolbar.h"
//#include "wx/statusbr.h"
//#include "wx/msgdlg.h"
//#include "wx/textdlg.h"
//#include <wx/stdpaths.h>
//#include "wx/button.h"
//#include "wx/image.h"
//#include "wx/sysopt.h"
//#include "wx/html/htmlwin.h"
//#include "wx/html/htmlproc.h"
//#include "wx/fs_inet.h"
//#include "wx/filedlg.h"
//#include "wx/utils.h"
//#include "wx/aui/aui.h"
//#include <wx/glcanvas.h>


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

#define moText2Wx(X) (wxChar*)(char*)X
#define moWx2Text(X) moText((char*)(wxChar*)X.c_str())

#endif
