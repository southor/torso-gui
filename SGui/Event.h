#ifndef _STATE_GUI_EVENT_H
#define _STATE_GUI_EVENT_H

#include "Events.h"
#include "basic.h"

namespace SGui
{
	struct Event
	{
		int generalType;
		int subType;
		Pos mousePos; // used for mouse events

		//Event& operator =(const Event &rhs)
		//{
		//	generalType = rhs.generalType;
		//	subType = rhs.subType;
		//	mousePos = rhs.mousePos;
		//}
	};
};

#endif