#ifndef _STATE_GUI_SLOT_SEQUENCE_CPP_
#define _STATE_GUI_SLOT_SEQUENCE_CPP_

#include "SlotSequence.h"

namespace SGui
{

	Vecf SlotSequence::updateSize(Vecf tension)
	{
		Vecf resultTension(0.0f, 0.0f);		

		Vec newSize(0, 0);

		Slots::iterator it = slots.begin();
		Slots::iterator end = slots.end();
			
		if (direction == HORIZONTAL)
		{
			for(; it != end; ++it)
			{
				resultTension += it->updateSize(tension);				
				newSize.x += it->getWidth();
				newSize.y = maxFun(it->getHeight(), newSize.y);
			}

			Slots::iterator it = slots.begin();
			for(; it != end; ++it)
			{
				it->setHeight(newSize.y);
			}
		}
		else
		{
			assert(direction == VERTICAL);
			for(; it != end; ++it)
			{
				resultTension += it->updateSize(tension);
				newSize.y += it->getHeight();
				newSize.x = maxFun(it->getWidth(), newSize.x);
			}

			Slots::iterator it = slots.begin();
			for(; it != end; ++it)
			{
				it->setWidth(newSize.x);
			}
		}

		setSize(newSize);

		return resultTension / static_cast<float>(slots.size());
	}

	void SlotSequence::updateChildPoss()
	{
		Slots::iterator it = slots.begin();
		Slots::iterator end = slots.end();

		int offset = 0;

		if (direction == HORIZONTAL)
		{
			for(; it != end; ++it)
			{
				it->setX(offset);				
				it->setY(getY());
				offset += it->getX();
			}
		}
		else
		{
			assert(direction == VERTICAL);
			for(; it != end; ++it)
			{
				it->setY(offset);
				it->setX(getX());
				offset += it->getY();
			}
		}
	}

};

#endif