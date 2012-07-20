#ifndef _STATE_GUI_EVENT_RECIEVER_H_
#define _STATE_GUI_EVENT_RECIEVER_H_

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

	class EventReciever
	{
	private:
		PRI_RW_MEMBER(EventReciever*, next, Next)
	
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

		EventReciever(EventReciever *next = nullptr) : next(next)					{}

		virtual ~EventReciever()												{}

		// Lets the hole EventReciever chain recieve the event
		//void chainRecieveEvent(const GridEventInfo &info);

		// Lets this EventReciever chain recieve the event
		virtual void recieveEvent(const GridEventInfo &info, fint extra = 0) = 0; //	{}

		// Lets this EventReciever chain recieve the event
		//virtual void recieveEvent(int clientEvent, int arg, fint extra = 0)		{}

		//void setNext(EventReciever *next);
	};
};

#endif