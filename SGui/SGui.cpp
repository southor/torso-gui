#ifndef _STATE_GUI_STATE_GUI_CPP_
#define _STATE_GUI_STATE_GUI_CPP_

#include "SGui.h"

//#include "gl_includes.h"

namespace SGui
{
	void initNamespace(RenderContext *renderContext)
	{
		SGui::Txtr::clearLoaded(renderContext);
		SGui::Txtr::createDefaultTxtr(renderContext);
	}
	
	//void setClipping(const Pos &pos, const Rect &clipRect)
	//{
	//	glScissor(pos.x + clipRect.getX(), pos.y + clipRect.getY(),
	//			  clipRect.getWidth(), clipRect.getHeight());
	//}

	void cleanupNamespace(RenderContext *renderContext)
	{
		SGui::Txtr::clearLoaded(renderContext);
	}
};

#endif