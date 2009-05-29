#ifndef _STATE_GUI_GRAPH_STATE_CPP_
#define _STATE_GUI_GRAPH_STATE_CPP_

#include "GraphState.h"

namespace SGui
{
	GraphState::GraphState() : State(), renderObjs()
	{}

	//GraphState::GraphState(int id) : State(id), renderObjs()
	//{}

	void GraphState::renderState(const Rect &clipRect)
	{
		RenderObj *renderObj;
		RenderObjs::iterator iter = renderObjs.begin();
		RenderObjs::iterator end = renderObjs.end();
		for(; iter != end; ++iter)
		{
			//TODO check which is fastest, check if outside cliparea or just render.
			renderObj = *iter;
			if (clipRect.covering(renderObj->getRect()))
			{
				renderObj->render();
			}
		}
	}
};

#endif