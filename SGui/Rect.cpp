#ifndef _STATE_GUI_RECTANGLE_CPP
#define _STATE_GUI_RECTANGLE_CPP

#include "Rect.h"
#include <limits>



namespace SGui
{

	int Rect::area() const
	{
		__int64 area = size.x * size.y;
		return static_cast<int>(limit(area, static_cast<__int64>(INT_MIN),
								static_cast<__int64>(INT_MAX)));
	}

	void Rect::intersectWith(const Rect &rect)
	{
		// store right bottom corner positions
		// (must be stored because this.pos will be changed)
		int oldRight = getRight();
		int oldTop = getTop();
		
		// calculate new position
		pos.x = maxFun(pos.x, rect.pos.x);
		pos.y = maxFun(pos.y, rect.pos.y);
		
		// calculate new size
		size.x = minFun(oldRight, rect.getRight()) - pos.x;
		size.y = minFun(oldTop, rect.getTop()) - pos.y;

		// No negative rectangle area sizes allowed.
		if (area() < 0) size.x = 0;	
	}
};

#endif