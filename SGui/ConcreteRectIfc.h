#ifndef _STATE_GUI_CONCRETE_RECTANGLE_INTERFACE_H
#define _STATE_GUI_CONCRETE_RECTANGLE_INTERFACE_H

#include "RectIfc.h"

namespace SGui
{

	// Implements the Rectangle Interface by keeping a local real Rectangle inside it's body
	class ConcreteRectIfc : public RectIfc
	{
	protected:
		Rect rect;
	public:

		inline ConcreteRectIfc()														{}

		inline ConcreteRectIfc(Pos pos, Vec size) : rect(pos, size)						{}

		inline ConcreteRectIfc(int x, int y, int w, int h) : rect(x, y, w, h)			{}

		inline ConcreteRectIfc(const Rect &rect) : rect(rect)							{}



		// ------ Implementation of the virtual interface ------

		Pos getPos() const;
		Vec getSize() const;

	};
};

#endif