#ifndef _STATE_GUI_MACROS_H_
#define _STATE_GUI_MACROS_H_

#include "declares.h"
#include "asm_int_3.h"


#include <iostream>



inline void sGuiDebugBreak()
{
	sGuiAsmInt3();
//#ifdef _M_X64
//	sGuiAsmInt3();
//#else
//	__asm int 3
//#endif
}

// Only handles positive values of x
#define TWO_TO_POWER_OF(x) ( 1 << x )

// Generates a class member with a get function. Use in the private section.
#define PRI_R_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() const { return name; } private:

// Generates a class member with get and set functions. Use in the private section.
#define PRI_RW_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = name; } private:

// Generates a class member with get and set functions (Set function with limits). Use in the private section.
#define PRI_RWL_MEMBER(type, name, Name, min, max) private: type name; public: inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = limit<type>(name, min, max); } private:

// Generates a class member with a get function. Use in the protected section.
#define PRO_R_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() const { return name; } protected:

// Generates a class member with get and set functions. Use in the protected section.
#define PRO_RW_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = name; } protected:

// Generates a class member with get and set functions (Set function with limits). Use in the protected section.
#define PRO_RWL_MEMBER(type, name, Name, min, max) protected: type name; public: inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = limit<type>(name, min, max); } protected:

// Generates a class member with a get function. Use in the public section.
#define PUB_R_MEMBER(type, name, Name) type name; inline type get ## Name() const { return name; }

// Generates a class member with get and set functions. Use in the public section.
#define PUB_RW_MEMBER(type, name, Name) type name; inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = name; }

// Generates a class member with get and set functions (Set function with limits). Use in the public section.
#define PUB_RWL_MEMBER(type, name, Name, min, max) type name; inline type get ## Name() const { return name; } inline void set ## Name(type name) { this-> ## name = limit<type>(name, min, max); }

#define rAssert(x)  { if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); } }


#ifdef _DEBUG	
	#define dAssert(x) { if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); } }
#else
	#define dAssert(x) {}
#endif

//template <typename T>
//inline void dAssert(T x)
//{
//#ifdef _DEBUG
//	if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); }
//#endif
//}
//
//template <typename T>
//inline void rAssert(T x)
//{
//	if (!(x)) { printf("%s(%d): %s failed\n",  __FILE__, __LINE__, #x); fflush(stdout); sGuiDebugBreak(); }
//}



#endif