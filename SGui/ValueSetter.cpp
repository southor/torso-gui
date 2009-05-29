#ifndef _STATE_GUI_VALUE_SETTER_CPP_
#define _STATE_GUI_VALUE_SETTER_CPP_

#include "ValueSetter.h"

namespace SGui
{

	//template <typename T>
	//const ValueSetter<T>::Action ValueSetter<T>::Action::DEFAULT = ValueSetter<T>::Action(NULL);

	template <typename T>
	void ValueSetter<T>::recieveEvent(const GridEventInfo &info)
	{
		assert(between(info.gridEvent, 0, N_GRID_EVENTS-1));		

		const Action &action = actionList[info.gridEvent];
		if (action.target)
		{
			//assert( absFun(static_cast<int>(*(action.target)) - static_cast<int>(action.value)) <= 1);
			*(action.target) = action.value;

			info.gridPos.
		}

		nextRecieve(info);
	}
};

#endif
