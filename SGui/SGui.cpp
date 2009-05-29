#ifndef _STATE_GUI_STATE_GUI_CPP_
#define _STATE_GUI_STATE_GUI_CPP_

#include "SGui.h"

namespace SGui
{
	void initNamespace()
	{
		SGui::Txtr::createDefaultTxtr();
	}
	
	void setClipping(const Pos &pos, const Rect &clipRect)
	{
		glScissor(pos.x + clipRect.getX(), pos.y + clipRect.getY(),
				  clipRect.getWidth(), clipRect.getHeight());
	}

	void cleanupNamespace()
	{
	}
};

#endif