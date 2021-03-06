#ifndef _STATE_GUI_GL_DECLARES_H_
#define _STATE_GUI_GL_DECLARES_H_

namespace SGui
{
	typedef unsigned char gl_ubyte;
	typedef unsigned int gl_uint;
	typedef float gl_float;
	typedef unsigned int gl_enum;
	typedef unsigned char gl_bool;

	// @eturns true if above definitions is compatible with gl
	bool glDeclaresCorrect();
};

#endif