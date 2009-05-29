#ifndef _STATE_GUI_STATE_GUI_H_
#define _STATE_GUI_STATE_GUI_H_

#include "Rect.h"
#include "Txtr.h"

namespace SGui
{
	void initNamespace();
	
	void setClipping(const Pos &pos, const Rect &clipRect);

	void cleanupNamespace();
};

#endif