#ifndef _STATE_GUI_SLOT_H_
#define _STATE_GUI_SLOT_H_

#include "Box.h"
//#include "macros.h"

//#include <climits>


namespace SGui
{

	class SlotSequence;

	class Slot : public Box
	{
	private:

		int xAlign;
		int yAlign;

		// max one pointer can be none-null
		WRectIfc *obj;
		Slot *slot;
		SlotSequence *slotSequence;

		Vecf kValue;

		// -----------------------

		static const Color4f &DEFAULT_COLOR;

		static const Vecf DEFAULT_K_VALUE;

		static const Pos DEFAULT_POS;
		static const Vec DEFAULT_SIZE;

		static const int DEFAULT_X_ALIGN = ALIGN_MIDDLE;
		static const int DEFAULT_Y_ALIGN = ALIGN_MIDDLE;

		// -----------------------



		//inline void alignChildPos(int parentPos, int parentSize, int childSize, int align, int &childPos)
		//{
		//	switch(align)
		//	{
		//		case ALIGN_LEFT
		//	};
		//}

		// Will remove the child if there is a child
		void removeChild();

	public:

		//Slot(WRectIfc *obj, int xAlign, int yAlign, const Color4f &color = DEFAULT_COLOR) 
		//	: Box(Pos(0, 0), Vec(0, 0), false, color), obj(obj), slot(NULL), slotSequence(NULL), xAlign(xAlign), yAlign(yAlign)
		//{
		//	kValue = DEFAULT_K_VALUE;
		//}

		//Slot(Slot *slot, int xAlign, int yAlign, const Color4f &color = DEFAULT_COLOR) 
		//	: Box(Pos(0, 0), Vec(0, 0), false, color), obj(obj), slot(slot), slotSequence(NULL), xAlign(xAlign), yAlign(yAlign)
		//{
		//	kValue = DEFAULT_K_VALUE;
		//}

		//Slot(SlotSequence *slotSequence, int xAlign, int yAlign, const Color4f &color = DEFAULT_COLOR) 
		//	: Box(Pos(0, 0), Vec(0, 0), false, color), obj(NULL), slot(NULL), slotSequence(slotSequence), xAlign(xAlign), yAlign(yAlign)
		//{
		//	kValue = DEFAULT_K_VALUE;
		//}

		Slot(int xAlign = DEFAULT_X_ALIGN, int yAlign = DEFAULT_Y_ALIGN, const Color4f &color = DEFAULT_COLOR)
			: Box(DEFAULT_POS, DEFAULT_SIZE, color, 1), obj(NULL), slot(NULL), slotSequence(NULL), xAlign(xAlign), yAlign(yAlign)
		{
			kValue = DEFAULT_K_VALUE;
		}

		WRectIfc* getChild() const;

		inline bool hasChild() const				{ return getChild() != NULL; }

		void setChild(WRectIfc *obj)				{ removeChild();
													  this->obj = obj; }

		void setChild(Slot *slot)					{ removeChild();
													  this->slot = slot; }

		void setChild(SlotSequence *slotSequence)	{ removeChild();
													  this->slotSequence = slotSequence; }

		//bool childIsSlotSequence() const
		//{
		//	dAssert(isConsistent());
		//	return slotSequence;
		//}

		//bool childIsObj() const
		//{
		//	dAssert(isConsistent());
		//	return obj;
		//}

		Vecf updateSize(Vecf tension);

		void updateChildPos();


		bool isConsistent() const;		

	};
};

#endif