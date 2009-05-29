#ifndef _STATE_GUI_ACTION_LIST_CPP_
#define _STATE_GUI_ACTION_LIST_CPP_

#include "ActionList.h"

namespace SGui
{
	template <typename Action>
	void ActionList<Action>::resetActions()
	{
		for(int i=0; i<N_GRID_EVENTS; ++i)
		{
			actions[i] = Action::getDefaultAction();
		}
	}
};

#endif