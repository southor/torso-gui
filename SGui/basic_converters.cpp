#ifndef _STATE_GUI_BASIC_CONVERTERS_CPP_
#define _STATE_GUI_BASIC_CONVERTERS_CPP_

#include "basic_converters.h"
#include "functions.h"

namespace SGui
{


	void color3bToColor3f(const Color3b &from, Color3f &to)
	{
		to.r = static_cast<float>(from.r) / 255.0f;
		to.g = static_cast<float>(from.g) / 255.0f;
		to.b = static_cast<float>(from.b) / 255.0f;
	}

	void color4bToColor4f(const Color4b &from, Color4f &to)
	{
		to.r = static_cast<float>(from.r) / 255.0f;
		to.g = static_cast<float>(from.g) / 255.0f;
		to.b = static_cast<float>(from.b) / 255.0f;
		to.a = static_cast<float>(from.a) / 255.0f;
	}

	void color3bToStr(const Color3b &from, std::string &str)
	{
		char tmpStr[] = "000000\0";		

		writeHexByte(from.r, tmpStr);
		writeHexByte(from.g, tmpStr+2);
		writeHexByte(from.b, tmpStr+4);

		str = tmpStr;
	}

	void color4bToStr(const Color4b &from, std::string &str)
	{
		char tmpStr[] = "00000000\0";		

		writeHexByte(from.r, tmpStr);
		writeHexByte(from.g, tmpStr+2);
		writeHexByte(from.b, tmpStr+4);
		writeHexByte(from.a, tmpStr+6);

		str = tmpStr;
	}

};

#endif

