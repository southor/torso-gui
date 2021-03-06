#ifndef _STATE_GUI_VALUE_SETTER_H_
#define _STATE_GUI_VALUE_SETTER_H_

#include "EventReceiver.h"
#include "ActionList.h"

//#include "gl_includes.h"
#include "gl_declares.h"

namespace SGui
{

	template <typename T>
	class ValueSetter : public EventReceiver
	{
	protected:

		struct Action
		{
			T *target;
			T value;

			Action()														{}
			Action(T *target) : target(nullptr)								{ dAssert(target == nullptr); }
			Action(T *target, T value) : target(target), value(value)		{}

			inline static Action getDefaultAction()							{ return Action(nullptr); }

			//static const Action DEFAULT;
		};

		ActionList<Action> actionList;

	public:

		inline ValueSetter(EventReceiver *next = nullptr) : EventReceiver(next)	{}

		~ValueSetter()				{}
		
		void recieveEvent(const GridEventInfo &info, fint extra = 0);

		inline void resetActions()				{ actionList.resetActions(); }

		inline void setAction(int gridEvent, const Action &action)
		{
			actionList[gridEvent] = action;
		}

		inline void setAction(int gridEvent, T *target, T value)
		{
			setAction(gridEvent, Action(target, value));
		}
	};

	typedef ValueSetter<gl_uint> TxtrIdSetter;
	typedef ValueSetter<Color3f> Color3Setter;
	typedef ValueSetter<Color4f> Color4Setter;
};

#endif