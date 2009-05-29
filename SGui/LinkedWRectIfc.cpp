#ifndef _STATE_GUI_LINKED_WRITEABLE_RECTANGLE_INTERFACE_CPP
#define _STATE_GUI_LINKED_WRITEABLE_RECTANGLE_INTERFACE_CPP

#include "LinkedWRectIfc.h"

namespace SGui
{

	Pos LinkedWRectIfc::getPos() const			{ return rect->getPos(); }
	Vec LinkedWRectIfc::getSize() const			{ return rect->getSize(); }

	void LinkedWRectIfc::setPos(Pos pos)		{ rect->setPos(pos); }
	void LinkedWRectIfc::setSize(Vec size)		{ rect->setSize(size); }

};

#endif