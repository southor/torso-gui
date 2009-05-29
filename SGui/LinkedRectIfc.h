#ifndef _STATE_GUI_LINKED_RECTANGLE_INTERFACE_H
#define _STATE_GUI_LINKED_RECTANGLE_INTERFACE_H

#include "RectIfc.h"

namespace SGui
{

	// Implements the Rectangle Interface by using a reference to another rectangle interface to map it's values to this rectangle.
	class LinkedRectIfc : public RectIfc
	{
	private:
		RectIfc *rect;
	public:

		// Will not take ownership of rectangle
		inline LinkedRectIfc(RectIfc *rect) :rect(rect)				{}



		// ------ Implementation of the virtual interface ------

		Pos getPos() const;
		Vec getSize() const;

	};
};

#endif