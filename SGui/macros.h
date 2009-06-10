#ifndef _STATE_GUI_MACROS_H_
#define _STATE_GUI_MACROS_H_

#include "declares.h"


inline void sGuiDebugBreak()
{
#ifndef _M_X64 // TODO deal with case X64 later, (write a binary function manually).
		__asm int 3
#endif
}


#define TWO_TO_POWER_OF(x) ( 1 << x )

#define PRI_R_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() { return name; } private:
#define PRI_RW_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() { return name; } inline void set ## Name(type name) { this-> ## name = name; } private:

#define PRO_R_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() { return name; } protected:
#define PRO_RW_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() { return name; } inline void set ## Name(type name) { this-> ## name = name; } protected:



#define rAssert(x) if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); }


#ifdef _DEBUG	
	#define dAssert(x) if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); }
#else
	#define dAssert(x);
#endif



#endif