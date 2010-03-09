#ifndef _STATE_GUI_BASIC_CONVERTERS_CPP_
#define _STATE_GUI_BASIC_CONVERTERS_CPP_

#include "basic_converters.h"

namespace SGui
{
	void color3bToColor3f(const Color3b &from, Color3f &to)
	{
		to.r = static_cast<float>(from.r) / 255.0f;
		to.g = static_cast<float>(from.g) / 255.0f;
		to.b = static_cast<float>(from.b) / 255.0f;
	}
};

#endif