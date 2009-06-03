#ifndef _STATE_GUI_GRAPH_STATE_H_
#define _STATE_GUI_GRAPH_STATE_H_

#include "State.h"
#include "RenderObj.h"

#include <vector>

namespace SGui
{

	class GraphState : public State
	{

	public:

		typedef std::vector<RenderObj*> RenderObjs;		
		RenderObjs renderObjs;

		GraphState();

		//GraphState(int id);

		

		void renderState(RenderContext *renderContext, const Rect &clipRect);
	};
};

#endif