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
//#include "dAssert.h"

//#define NULL 0

#include <stdint.h>
#include <string>

namespace SGui
{

#if defined _WIN32
	typedef wchar_t fschar;
	typedef std::wstring fsstring;
#else
	typedef char fschar;
	typedef std::string fsstring;
#endif
	
	//typedef signed char int8;
	//typedef unsigned char uint8;

	//typedef short int16;
	//typedef unsigned short uint16;

	//typedef int int32;
	//typedef unsigned int uint32;

	typedef int8_t int8;
	typedef uint8_t uint8;

	typedef int16_t int16;
	typedef uint16_t uint16;

	typedef int32_t int32;
	typedef uint32_t uint32;

	typedef int64_t int64;
	typedef uint64_t uint64;

	//typedef signed __int128 int128;
	//typedef unsigned __int128 uint128;
	typedef int8 byte;
	typedef uint8 ubyte;

	typedef unsigned char uchar;

	typedef unsigned short ushort;

	typedef unsigned int uint;
	
	//#define UINT_MSB 0x00000001;


#ifdef _M_X64
	typedef int64 fint;
	typedef int32 hint;
	typedef int16 qint;

	typedef uint64 ufint;
	typedef uint32 uhint;
	typedef uint16 uqint;
#else
	typedef int32 fint;
	typedef int16 hint;
	typedef int8 qint;

	typedef uint32 ufint;
	typedef uint16 uhint;
	typedef uint8 uqint;
#endif


	// A different name for integers if you want them to represent a true/false value.
	typedef int ibool;
	
	typedef int64 ibool64;
	typedef int32 ibool32;
	typedef int16 ibool16;
	typedef int8 ibool8;
	
	typedef fint fbool;
	typedef hint hbool;
	


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



	//const static uint nullptr = 0;
};

#endif