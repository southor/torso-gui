#ifndef _STATE_GUI_LINKED_RECTANGLE_INTERFACE_CPP
#define _STATE_GUI_LINKED_RECTANGLE_INTERFACE_CPP

#include "LinkedRectIfc.h"

namespace SGui
{

	Pos LinkedRectIfc::getPos() const			{ return rect->getPos(); }
	Vec LinkedRectIfc::getSize() const			{ return rect->getSize(); }

};

#endif