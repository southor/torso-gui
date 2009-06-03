#ifndef _STATE_GUI_RENDER_OBJECT_H_
#define _STATE_GUI_RENDER_OBJECT_H_

#include "ConcreteWRectIfc.h"
#include "RenderContext.h"

namespace SGui
{


	class RenderObj : public ConcreteWRectIfc
	{
	private:
		
	//	// Fast access to the render context
	//	RenderContext *renderContext;
	//protected:
	//	inline RenderContext* getRenderContext()			{ return renderContext; }
	public:
		
		RenderObj()
			: ConcreteWRectIfc(0, 0, 0, 0)//, renderContext(renderContext)
		{}

		RenderObj(const Pos &pos, const Vec &size)
			: ConcreteWRectIfc(pos, size)//, renderContext(renderContext)
		{}

		virtual ~RenderObj()										{}

		virtual void render(RenderContext *renderContext) = 0;

	};

};

#endif