#ifndef _STATE_GUI_STATE_SWITCHER_CPP_
#define _STATE_GUI_STATE_SWITCHER_CPP_

#include "StateSwitcher.h"
#include "StateHndlr.h"

#include "function_templates.inl"

namespace SGui
{

	const StateSwitcher::Action StateSwitcher::Action::DEFAULT = StateSwitcher::Action(StateSwitcher::Action::NO_ACTION);

	// Sets the same action for all Grid Events at once.
	void StateSwitcher::setAllActions(const Action &action)
	{
		for(int gridEvent = 0; gridEvent < N_GRID_EVENTS; ++gridEvent)
		{
			actionList[gridEvent] = action;	
		}
	}

	void StateSwitcher::recieveEvent(const GridEventInfo &info)
	{
		assert(between(info.gridEvent, 0, N_GRID_EVENTS-1));		

		const Action &action = actionList[info.gridEvent];

		if (action.type == Action::ENTER_STATE)
		{
			assert(stateHndlr);
			stateHndlr->enterState(action.stateId);
		}
		else if (action.type == Action::RESTART_STATE)
		{
			assert(stateHndlr);
			stateHndlr->restartState(action.stateId);
		}

		nextRecieve(info);
	}


};

#endif