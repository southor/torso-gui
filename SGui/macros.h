#ifndef _STATE_GUI_MACROS_H_
#define _STATE_GUI_MACROS_H_

#include "declares.h"

namespace SGui
{

	#define TWO_TO_POWER_OF(x) ( 1 << x )

	#define PRI_R_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() { return name; } private:
	#define PRI_RW_MEMBER(type, name, Name) private: type name; public: inline type get ## Name() { return name; } inline void set ## Name(type name) { this-> ## name = name; } private:

	#define PRO_R_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() { return name; } protected:
	#define PRO_RW_MEMBER(type, name, Name) protected: type name; public: inline type get ## Name() { return name; } inline void set ## Name(type name) { this-> ## name = name; } protected:

};

#endif