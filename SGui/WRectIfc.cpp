#ifndef _STATE_GUI_WRITEABlE_RECTANGLE_INTERFACE_CPP
#define _STATE_GUI_WRITEABlE_RECTANGLE_INTERFACE_CPP

#include "WRectIfc.h"

namespace SGui
{

	//void WRectIfc::setPos(Pos pos)				{}
	//void WRectIfc::setSize(Vec size)				{}

	void WRectIfc::setCenterPos(Pos cPos)			{ setPos(cPos + getSize() / 2); }
	
	void WRectIfc::setCenterX(int cx)				{ setX(cx - getWidth() / 2); }
	void WRectIfc::setCenterY(int cy)				{ setX(cy - getHeight() / 2); }

};

#endif