#ifndef _STATE_GUI_EVENT_H
#define _STATE_GUI_EVENT_H

#include "Events.h"
#include "basic.h"

#include <set>

namespace SGui
{
	struct Event
	{
		int32 generalType;
		int32 subType;
		int64 arg;

		Event()
		{}

		Event(int32 generalType, int32 subType = 0, int64 arg = 0)
			: generalType(generalType), subType(subType), arg(arg)
		{}

		Event(int32 generalType, int32 subType, int32 arg)
			: generalType(generalType), subType(subType), arg(static_cast<int64>(arg))
		{}

		Event(int32 generalType, int32 subType, bool arg)
			: generalType(generalType), subType(subType), arg(static_cast<int64>(arg))
		{}

		Event(int32 generalType, int32 subType, std::pair<int32, int32> pairArg)
			: generalType(generalType), subType(subType), arg(0)
		{
			//arg = *reinterpret_cast<int64*>(&argPair);
			setArgAsPair(pairArg);
		}

		Event(int32 generalType, int32 subType, Pos posArg)
			: generalType(generalType), subType(subType), arg(0)
		{
			setArgAsPos(posArg);
		}

		Event(int32 generalType, int32 subType, void *ptrArg)
			: generalType(generalType), subType(subType), arg(0)
		{
			//fint tmp = reinterpret_cast<fint>(ptr);
			//arg = static_cast<arg>(ptr);
			//arg = reinterpret_cast<int64>(ptrArg);
			setArgAsPtr(ptrArg);
		}


		inline int getArgAsInt() const
		{
			return static_cast<int>(arg);
		}

		inline bool getArgAsBool() const
		{
			return static_cast<bool>(arg);
		}

		inline std::pair<int32, int32> getArgAsPair() const
		{
			//return Pos(arg & 0x00000000FFFFFFFF, (arg & 0xFFFFFFFF00000000) >> 32
			//return reinterpret_cast<Pos>(&arg);
			return *reinterpret_cast<const std::pair<int32, int32>*>(&arg);
		}

		inline Pos getArgAsPos() const
		{
			//return Pos(arg & 0x00000000FFFFFFFF, (arg & 0xFFFFFFFF00000000) >> 32
			//return reinterpret_cast<Pos>(&arg);
			return *reinterpret_cast<const Pos*>(&arg);
		}

		inline void* getArgAsPtr() const
		{
			//fint tmp = arg;
			//return reinterpret_cast<void*>(tmp);
			return reinterpret_cast<void*>(arg);
		}

		inline int getArgAsFlags(int mask) const
		{
			int64 mask2 = static_cast<int64>(mask);
			return static_cast<int>(arg & mask2);
		}

		inline int getArgAsFlags() const
		{
			int mask = 0xFFFFFFFF;
			int64 mask2 = static_cast<int64>(mask);
			return static_cast<int>(arg & mask2);
		}

		

		inline void setArgAsInt(int arg)
		{
			arg = static_cast<int64>(arg);
		}

		inline void setArgAsBool(bool arg)
		{
			arg = static_cast<int64>(arg);
		}
		
		inline void setArgAsPair(std::pair<int32, int32> pairArg)
		{
			arg = *reinterpret_cast<int64*>(&pairArg);
		}

		inline void setArgAsPos(Pos posArg)
		{
			arg = *reinterpret_cast<int64*>(&posArg);
		}

		inline void setArgAsPtr(void* ptrArg)
		{
			arg = *reinterpret_cast<int64*>(&ptrArg);
		}

		inline void setArgAsFlags(int bitfield)
		{
			arg = static_cast<int64>(bitfield);
		}



		

		


		//union arg_union
		//{
		//	int64 n;
		//	Pos mousePos; // used for mouse events
		//	void *ptr;
		//} arg;

		//Event& operator =(const Event &rhs)
		//{
		//	generalType = rhs.generalType;
		//	subType = rhs.subType;
		//	mousePos = rhs.mousePos;
		//}
	};
};

#endif