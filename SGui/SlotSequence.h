#ifndef _STATE_GUI_SLOT_SEQUENCE_H_
#define _STATE_GUI_SLOT_SEQUENCE_H_

#include "basic.h"
#include "macros.h"

#include "Slot.h"

#include "basic_includes.h"

//#include <climits>
#include <vector>

namespace SGui
{

	class SlotSequence : public ConcreteWRectIfc
	{		
	private:

		static const int DEFAULT_DEFAULT_X_ALIGN = ALIGN_MIDDLE;
		static const int DEFAULT_DEFAULT_Y_ALIGN = ALIGN_MIDDLE;

		//static const Veci DEFAULT_DEFAULT_ALIGN;

		int direction;

		Veci defaultAlign;

		int defaultXAlign;
		int defaultYAlign;

		typedef std::vector<Slot> Slots;
		Slots slots;

	public:

		/**
		 * @param direction Should be either HORIZONTAL or VERTICAL
		 * @param defaultXAlign Sets the defualt xAlign for all slots
		 *			Should be either ALIGN_LEFT, ALIGN_RIGHT or ALIGN_MIDDLE
		 * @param defaultYAlign  Sets the defualt yAlign for all slots
					Should be either ALIGN_TOP, ALIGN_BOTTOM, or ALIGN_MIDDLE
		 *
		 *
		 *
		 * @param defaultAlign should be a Veci on the following form:
					Veci(ALIGN_LEFT/ALIGN_RIGHT/ALIGN_MIDDLE,
						 ALIGN_TOP/ALIGN_BOTTOM/ALIGN_MIDDLE)
		 */
		SlotSequence(int direction,
					 int defaultXAlign = DEFAULT_DEFAULT_X_ALIGN,
					 int defaultYAlign = DEFAULT_DEFAULT_Y_ALIGN)
					 //Veci defaultAlign = DEFAULT_DEFAULT_ALIGN)
					 : direction(direction),
					   defaultXAlign(defaultXAlign),
					   defaultYAlign(defaultXAlign)
		{
			//TODO use exceptions?
			assert(checkAlternative(direction, N_DIRECTIONS));

			
		}

		template <class T>
		void add(T *child)
		{
			Slot slot(defaultXAlign, defaultYAlign);
			slot.setChild(child);
			slots.push_back(slot);
		}

		template <class T>
		void add(T *child, int xAlign, int yAlign)
		{
			Slot slot(xAlign, yAlign);
			slot.setChild(child);
			slots.push_back(slot);
		}

		//void add(WRectIfc *child)
		//{
		//	Slot slot(defaultXAlign, defaultYAlign);
		//	slot.setChild(child);
		//	slots.push_back(slot);
		//}

		//void add(Slot *child)
		//{
		//	Slot slot(defaultXAlign, defaultYAlign);
		//	slot.setChild(child);
		//	slots.push_back(slot);
		//}

		//void add(SlotSequence *child)
		//{
		//	Slot slot( defaultXAlign, defaultYAlign);
		//	slot.setChild(child);
		//	slots.push_back(slot);
		//}


		//void add(WRectIfc *child, int xAlign, int yAlign)
		//{
		//	Slot slot(xAlign, yAlign);
		//	slots.push_back(slot);
		//}

		//void add(Slot *child, int xAlign, int yAlign)
		//{
		//	Slot slot(xAlign, yAlign);
		//	slots.push_back(slot);
		//}

		//void add(SlotSequence *child, int xAlign, int yAlign)
		//{
		//	Slot slot(xAlign, yAlign);
		//	slots.push_back(slot);
		//}


		
		Vecf updateSize(Vecf tension);

		void updateChildPoss();

	};
};

#endif