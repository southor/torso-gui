#ifndef _STATE_GUI_BASIC_CONVERTERS_H_
#define _STATE_GUI_BASIC_CONVERTERS_H_

#include "basic.h"

#include <iostream>

namespace SGui
{
	void color3bToColor3f(const Color3b &from, Color3f &to);
	void color4bToColor4f(const Color4b &from, Color4f &to);

	void color3bToStr(const Color3b &from, std::string &str);
	void color4bToStr(const Color4b &from, std::string &str);
};

#endif