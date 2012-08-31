#ifndef _STATE_GUI_EVENT_RECEIVER_H_
#define _STATE_GUI_EVENT_RECEIVER_H_

#include "Events.h"
#include "basic.h"
#include "macros.h"

namespace SGui
{
	class State;

	struct GridEventInfo
	{
		State *state;
		int actionSurfaceId;
		int gridEvent;
		Pos gridPos;

		GridEventInfo(State *state, int actionSurfaceId, int gridEvent, Pos gridPos)
			: state(state), actionSurfaceId(actionSurfaceId), gridEvent(gridEvent), gridPos(gridPos)
		{}
	};

	class EventReceiver
	{
	private:
		PRI_RW_MEMBER(EventReceiver*, next, Next)
	
	protected:
		
		inline void nextRecieve(const GridEventInfo &info, fint extra = 0)
		{
			if (next) next->recieveEvent(info, extra);
		}

		//inline void nextRecieve(int clientEvent, int arg, fint extra = 0)
		//{
		//	if (next) next->recieveEvent(clientEvent, arg, extra);
		//}

	public:

		EventReceiver(EventReceiver *next = nullptr) : next(next)					{}

		virtual ~EventReceiver()												{}

		// Lets the hole EventReceiver chain recieve the event
		//void chainRecieveEvent(const GridEventInfo &info);

		// Lets this EventReceiver chain recieve the event
		virtual void recieveEvent(const GridEventInfo &info, fint extra = 0) = 0; //	{}

		// Lets this EventReceiver chain recieve the event
		//virtual void recieveEvent(int clientEvent, int arg, fint extra = 0)		{}

		//void setNext(EventReceiver *next);
	};

	// Allows the use of the old missspelled name.
	typedef EventReceiver EventReciever;

};

#endif