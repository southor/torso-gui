#ifndef _STATE_GUI_CONCRETE_RECTANGLE_INTERFACE_CPP
#define _STATE_GUI_CONCRETE_RECTANGLE_INTERFACE_CPP

#include "ConcreteRectIfc.h"

#include <iostream>

namespace SGui
{
	Pos ConcreteRectIfc::getPos() const				{ return rect.pos; }
	Vec ConcreteRectIfc::getSize() const			
	{
		//std::cout << " rect.size.y = " << rect.size.y;
		return rect.size;
	}

};

#endif