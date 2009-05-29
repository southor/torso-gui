#ifndef _STATE_GUI_CONCRETE_WRITEABLE_RECTANGLE_INTERFACE_CPP
#define _STATE_GUI_CONCRETE_WRITEABLE_RECTANGLE_INTERFACE_CPP

#include "ConcreteWRectIfc.h"

namespace SGui
{
	Pos ConcreteWRectIfc::getPos() const				{ return this->rect.pos; }
	Vec ConcreteWRectIfc::getSize() const				{ return this->rect.size; }

	void ConcreteWRectIfc::setPos(Pos pos)				{ this->rect.pos = pos; }
	void ConcreteWRectIfc::setSize(Vec size)			{ this->rect.size = size; }
};

#endif