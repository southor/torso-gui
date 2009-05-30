#ifndef _STATE_GUI_ACTION_LIST_H_
#define _STATE_GUI_ACTION_LIST_H_

#include "Events.h"
#include "function_templates.h"
#include <iostream>

#include "basic_includes.h"

namespace SGui
{

	template <typename Action>
	class ActionList
	{
	protected:

		Action actions[N_GRID_EVENTS];

	public:

		void resetActions();

		inline ActionList()				{ resetActions(); }

		virtual ~ActionList()			{}

		Action& operator [](int gridEvent)
		{
			dAssert(between(gridEvent, 0, N_GRID_EVENTS-1));
			return actions[gridEvent];
		}

		const Action& operator [](int gridEvent) const
		{
			dAssert(between(gridEvent, 0, N_GRID_EVENTS-1));
			return actions[gridEvent];
		}
	};
};

#endif