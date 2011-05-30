#ifndef _STATE_GUI_EVENT_STACK_H
#define _STATE_GUI_EVENT_STACK_H

#include "Event.h"

#include <vector>

namespace SGui
{
	class EventStack
	{
	private:
		std::vector<Event> stack; 
	public:

		void pushEvent(const Event &ev)
		{
			stack.push_back(ev);
		}

		bool popEvent(Event &ev)
		{
			if (stack.empty()) return false;
			ev = stack.back();
			stack.pop_back();
			return true;
		}

		size_t getNElements()
		{
			return stack.size();
		}

		bool empty()
		{
			return stack.empty();
		}
		
	};

};

#endif