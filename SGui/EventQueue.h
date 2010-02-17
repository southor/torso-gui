#ifndef _STATE_GUI_EVENT_QUEUE_H
#define _STATE_GUI_EVENT_QUEUE_H

#include "Event.h"

#include <queue>

namespace SGui
{
	class EventQueue
	{
	private:
		std::queue<Event> queue; 
	public:

		void pushEvent(const Event &ev)
		{
			queue.push(ev);
		}

		bool popEvent(Event &ev)
		{
			if (queue.empty()) return false;
			ev = queue.front();
			queue.pop();
			return true;
		}

		size_t getNElements()
		{
			return queue.size();
		}

		bool empty()
		{
			return queue.empty();
		}
		
	};

};

#endif