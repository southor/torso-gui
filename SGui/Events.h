#ifndef _STATE_GUI_EVENTS_H
#define _STATE_GUI_EVENTS_H

#include "declares.h"

namespace SGui
{
	// General Event types (used by State)
	static const int N_EVENT_TYPES = 3;
	enum
	{
		SGUI_MOUSE_BUTTON_EVENT,
		SGUI_MOUSE_MOVE_EVENT,
		SGUI_KEY_EVENT
	};
	
	// Grid Events and Mouse Button Events (used by ActionSurface)
	static const int N_GRID_EVENTS = 6;
	enum
	{
		LEFT_MOUSE_DOWN,
		LEFT_MOUSE_UP,
		RIGHT_MOUSE_DOWN,
		RIGHT_MOUSE_UP,
		MOUSE_OVER_TILE,
		MOUSE_AWAY_FROM_TILE
	};
	//static const int ALL_MOUSE_BUTTON_EVENTS_BITS = TWO_TO_POWER_OF(LEFT_MOUSE_DOWN) |
	//											TWO_TO_POWER_OF(LEFT_MOUSE_UP) |
	//											TWO_TO_POWER_OF(RIGHT_MOUSE_DOWN) |
	//											TWO_TO_POWER_OF(RIGHT_MOUSE_UP);
	//static const int ALL_GRID_EVENTS_BITS = TWO_TO_POWER_OF(ALL_MOUSE_BUTTON_EVENTS_BITS) |
	//											TWO_TO_POWER_OF(MOUSE_OVER_TILE) |
	//											TWO_TO_POWER_OF(MOUSE_AWAY_FROM_TILE);
};

#endif