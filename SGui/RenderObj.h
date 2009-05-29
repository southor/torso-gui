#ifndef _STATE_GUI_RENDER_OBJECT_H_
#define _STATE_GUI_RENDER_OBJECT_H_

#include "ConcreteWRectIfc.h"

namespace SGui
{

	class RenderObj : public ConcreteWRectIfc
	{
	public:
		
		RenderObj() : ConcreteWRectIfc(0, 0, 0, 0)					{}

		RenderObj(const Pos &pos, const Vec &size)
			: ConcreteWRectIfc(pos, size)							{}

		virtual ~RenderObj()										{}

		virtual void render() = 0;

	};

};

#endif