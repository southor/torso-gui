#ifndef _STATE_GUI_VALUE_SETTER_CPP_
#define _STATE_GUI_VALUE_SETTER_CPP_

#include "ValueSetter.h"

namespace SGui
{

	//template <typename T>
	//const ValueSetter<T>::Action ValueSetter<T>::Action::DEFAULT = ValueSetter<T>::Action(nullptr);

	template <typename T>
	void ValueSetter<T>::recieveEvent(const GridEventInfo &info, fint extra)
	{
		dAssert(between(info.gridEvent, 0, N_GRID_EVENTS-1));		

		const Action &action = actionList[info.gridEvent];
		if (action.target)
		{
			//dAssert( absFun(static_cast<int>(*(action.target)) - static_cast<int>(action.value)) <= 1);
			*(action.target) = action.value;

			info.gridPos.
		}

		nextRecieve(info);
	}
};

#endif
