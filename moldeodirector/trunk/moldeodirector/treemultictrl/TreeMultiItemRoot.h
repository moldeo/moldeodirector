//---------------------------------------------------------------------------
// $RCSfile$
// $Source$
// $Revision$
// $Date$
//---------------------------------------------------------------------------
// Author:      Jorgen Bodde
// Copyright:   (c) Jorgen Bodde
// License:     wxWidgets License
//---------------------------------------------------------------------------

#ifndef __TREEMULTIITEMROOT_HPP_
#define __TREEMULTIITEMROOT_HPP_

#ifdef __GNUG__
    #pragma interface "TreeMultiItemRoot.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "TreeMultiItemBase.h"
#include "TreeMultiItemNode.h"

/** This class is the root class. It can hold many of the TreeMultiItemWindow and
 * TreeMultiItemNode classes.
 */
class TreeMultiItemRoot : public TreeMultiItemNode
{
public:
	TreeMultiItemRoot();
	virtual ~TreeMultiItemRoot();

	// IsClass method
	virtual TreeMultiItemRoot *IsTreeMultiItemRoot() const {
		return (TreeMultiItemRoot *)this;
	};

};

#endif

