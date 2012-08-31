#ifndef _STATE_GUI_STATE_SWITCHER_H_
#define _STATE_GUI_STATE_SWITCHER_H_

#include "EventReceiver.h"
#include "ActionList.h"

namespace SGui
{

	class StateHndlr;

	class StateSwitcher : public EventReceiver
	{
	public:

		struct Action
		{			

			enum Type
			{
				NO_ACTION,
				ENTER_STATE,
				RESTART_STATE
			};

			Type type;
			int stateId;

			Action()															{}			
			Action(Type type, int stateId = 0) : type(type), stateId(stateId)	{}

			static const Action DEFAULT;

			static Action getDefaultAction()									{ return DEFAULT; }
		};

		

	protected:

		ActionList<Action>  actionList;

		StateHndlr *stateHndlr;

	public:

		inline StateSwitcher(StateHndlr *stateHndlr, EventReceiver *next = nullptr)
			: EventReceiver(next), stateHndlr(stateHndlr)
		{}

		~StateSwitcher()			{}
		
		// must have a valid StateHndlr if the action uses it.
		void recieveEvent(const GridEventInfo &info, fint extra = 0);
		
		inline void resetActions()				{ actionList.resetActions(); }

		inline void setAction(int gridEvent, const Action &action)					{ actionList[gridEvent] = action; }

		inline void setAction(int gridEvent, Action::Type type, int stateId)		{ setAction(gridEvent, Action(type, stateId)); }

		// Sets the same action for all Grid Events at once.
		void setAllActions(const Action &action);

		// Sets the same action for all Grid Events at once.
		inline void setAllActions(Action::Type type, int stateId)					{ setAllActions(Action(type, stateId)); }
	};
};

#endif