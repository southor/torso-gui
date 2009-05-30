#ifndef _STATE_GUI_SLOT_CPP_
#define _STATE_GUI_SLOT_CPP_

#include "Slot.h"
#include "SlotSequence.h"

namespace SGui
{

	const Pos Slot::DEFAULT_POS = Pos(0, 0);
	
	const Vec Slot::DEFAULT_SIZE = Vec(0, 0);
	
	const Color4f &Slot::DEFAULT_COLOR = Color4f(0.5f, 0.5f, 0.5f, 1.0f);

	const Vecf Slot::DEFAULT_K_VALUE = Vecf(1.0f, 1.0f);
	
	void Slot::removeChild()
	{
		obj = NULL;
		slot = NULL;
		slotSequence = NULL;
	}
	
	WRectIfc* Slot::getChild() const
	{
		dAssert(isConsistent());
		
		WRectIfc *rect = slotSequence;
		return obj ? obj : (slot ? slot : rect);
	}

	Vecf Slot::updateSize(Vecf tension)
	{
		Vecf currentTension(kValue/static_cast<Vecf>(getSize()));
		
		currentTension = (tension + currentTension) / 2.0f;

		setSize(static_cast<Vec>(kValue/currentTension));

		if (slotSequence) slotSequence->updateSize(tension);
		else if (slot) slot->updateSize(tension);

		return currentTension;
	}

	void Slot::updateChildPos()
	{
		WRectIfc *child = getChild();

		if (child) // if a child was added
		{		
			Pos tmpPos(getPos());

			Vec childSize(child->getSize());

			// align child x		
			if (xAlign != ALIGN_LEFT)
			{
				tmpPos.x -= childSize.x/2;
				if (xAlign == ALIGN_MIDDLE) tmpPos.x += getSize().x/2;
			}

			// align child y		
			if (yAlign != ALIGN_TOP)
			{
				tmpPos.y -= childSize.y/2;
				if (yAlign == ALIGN_MIDDLE) tmpPos.y += getSize().y/2;
			}

			// run recursive updateChildPos if
			if (slotSequence) slotSequence->updateChildPoss();
		}		
	}



	//debug
	bool Slot::isConsistent() const
	{
		// check number of active pointers
		int nActive = (obj ? 1 : 0) +
					  (slot ? 1 : 0) +
					  (slotSequence ? 1 : 0);
		if (nActive > 1) return false;
	
		// everything is fine
		return true;
	}

};

#endif