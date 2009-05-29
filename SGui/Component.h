#ifndef _STATE_GUI_COMPONENT_H_
#define _STATE_GUI_COMPONENT_H_

#include "basic.h"
#include "macros.h"

#include <climits>


namespace SGui
{

	class Component
	{
	private:

		virtual Pos getPos() = 0;
		virtual Vec getSize() = 0;

		virtual void setPos(const Pos &pos) = 0;
		virtual void setSize(const Vec &size) = 0;

	};
};

#endif