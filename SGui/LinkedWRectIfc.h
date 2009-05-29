#ifndef _STATE_GUI_LINKED_WRITEABLE_RECTANGLE_INTERFACE_H
#define _STATE_GUI_LINKED_WRITEABLE_RECTANGLE_INTERFACE_H

#include "WRectIfc.h"

namespace SGui
{

	// Implements the Writeable Rectangle Interface by using a reference to another writeable rectangle interface to map it's values and write functions to this rectangle.
	class LinkedWRectIfc : public WRectIfc
	{
	private:
		WRectIfc *rect;
	public:

		// Will not take ownership of rectangle
		inline LinkedWRectIfc(WRectIfc *rect) :rect(rect)				{}



		// ------ Implementation of the virtual interface ------

		Pos getPos() const;
		Vec getSize() const;

		void setPos(Pos pos);
		void setSize(Vec size);

	};
};

#endif