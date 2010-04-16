/*******************************************************************************

                                moFilesBook.h

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
	tab for MDI files

*******************************************************************************/
#ifndef _MO_FILES_BOOK_
#define _MO_FILES_BOOK_

#include "moDirectorTypes.h"
#include "moDirectorChildFrame.h"

class moFilesbookPage : public wxNotebookPage {
	public:
		moFilesbookPage( wxWindow* parent, wxWindowID id, moDirectorChildFrame* childframe );
		moDirectorChildFrame*		GetChildFrame();
		void		Activate();
	private:
		moDirectorChildFrame*		m_pChildFrame;
};

class moFilesbook : public wxAuiNotebook {
	public:
		moFilesbook( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0) :
		wxAuiNotebook(parent, id, pos, size, wxBORDER_NONE | wxAUI_NB_TAB_SPLIT | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TAB_MOVE ) { }

	void		OnPageChange( wxNotebookEvent &event );

	DECLARE_EVENT_TABLE()
};


#endif
