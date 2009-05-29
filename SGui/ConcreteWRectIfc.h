#ifndef _STATE_GUI_CONCRETE_WRITEABLE_RECTANGLE_INTERFACE_H
#define _STATE_GUI_CONCRETE_WRITEABLE_RECTANGLE_INTERFACE_H

#include "WRectIfc.h"

namespace SGui
{

	// Implements the Writeable Rectangle Interface by keeping a local real Rectangle inside it's body
	class ConcreteWRectIfc : public WRectIfc
	{
	protected:
		Rect rect;
	public:

		inline ConcreteWRectIfc()														{}

		inline ConcreteWRectIfc(Pos pos, Vec size) : rect(pos, size)					{}

		inline ConcreteWRectIfc(int x, int y, int w, int h) : rect(x, y, w, h)			{}

		inline ConcreteWRectIfc(const Rect &rect) : rect(rect)							{}



		// ------ Implementation of the virtual interface ------

		Pos getPos() const;
		Vec getSize() const;

		void setPos(Pos pos);
		void setSize(Vec size);

	};
};

#endif