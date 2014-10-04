#include "../SGui/gl_declares.h"
#include "gl_includes.h"

#include <typeinfo>

namespace SGui
{
	typedef unsigned char gl_ubyte;
	typedef unsigned int gl_uint;
	typedef float gl_float;
	typedef unsigned int gl_enum;
	typedef unsigned char gl_bool;

	bool glDeclaresCorrect()
	{
		bool res = true;
		res = res && (typeid(gl_ubyte) == typeid(GLubyte));
		res = res && (typeid(gl_uint) == typeid(GLuint));
		res = res && (typeid(gl_float) == typeid(GLfloat));
		res = res && (typeid(gl_enum) == typeid(GLenum));
		res = res && (typeid(gl_bool) == typeid(GLboolean));
		return res;
	}
};
