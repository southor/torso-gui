#ifndef _STATE_GUI_DECLARES_H_
#define _STATE_GUI_DECLARES_H_

//#if defined _WIN32
//	#define WIN32_LEAN_AND_MEAN
//	#include <windows.h>
//#endif
//
//#include <GL/gl.h>
//#include <GL/glu.h>
//
//#include "assert.h"

#define NULL 0

namespace SGui
{

	

	typedef signed char int8;
	typedef unsigned char uint8;

	typedef short int16;
	typedef unsigned short uint16;

	typedef int int32;
	typedef unsigned int uint32;

	
	
	

	typedef int8 byte;
	typedef uint8 ubyte;

	typedef unsigned char uchar;

	typedef unsigned short ushort;

	typedef unsigned int uint;
	
	//#define UINT_MSB 0x00000001;





	//enum
	//{
	//	ALIGN_LEFT = 1, // used for x-align
	//	ALIGN_RIGHT = 2, // used for x-align
	//	ALIGN_MIDDLE = 4, // used for both x-align and y-align
	//	ALIGN_TOP = 8, // used for y-align
	//	ALIGN_BOTTOM = 16 // used for y-align
	//	
	//};
	//static const int ALLOWED_X_ALIGNS = ALIGN_LEFT | ALIGN_RIGHT | ALIGN_MIDDLE;
	//static const int ALLOWED_Y_ALIGNS = ALIGN_TOP | ALIGN_BOTTOM | ALIGN_MIDDLE;

	enum
	{
		ALIGN_LEFT = 0,
		ALIGN_TOP = 0,
		ALIGN_RIGHT = 1,
		ALIGN_BOTTOM = 1,
		ALIGN_MIDDLE = 2
	};
	static const int N_X_ALIGNS = 3;
	static const int N_Y_ALIGNS = 3;




	enum
	{
		HORIZONTAL,
		VERTICAL		
	};
	static const int N_DIRECTIONS = 2;
	//static const int HORIZONTAL_OR_VERTICAL = HORIZONTAL | VERTICAL;



	//const static uint NULL = 0;
};

#endif