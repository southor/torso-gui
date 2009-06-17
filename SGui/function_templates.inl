#ifndef _STATE_GUIE_FUNCTION_TEMPLATES_CPP_
#define _STATE_GUI_FUNCTION_TEMPLATES_CPP_

#include "function_templates.h"
#include "Font.h" // test include

namespace SGui
{

	template<typename T> T loop(T value,T min,T max)
	{
		dAssert(max > 0);
		
		T B, C;
		value = value-min;
		max = max-min;
		if (value/max >= 0) {
			B = (T)(int)(value/max);
		}
		else {
			C = (T)(int)((-1)*value/max);
			B = (T)(int)(value/max+C+3)-(C+3);
		}
		value = value-B*max;
		
		return value+min;
	}
	
	template<typename T> T bounce(T value, T min, T max)
	{
		// fix displacement
		value = value-min;
		max = max-min;

		dAssert(max > 0);

		if (((int)(value/max))%2 == 0)
		{
			return min + Loop(value,0,max);
		}
		else
		{
			return min + max - Loop(value,0,max);
		}
	}

	template<typename T> bool restrain(T &val, T min, T max)
	{
		T oldVal = val;
		val = limit(val, min, max);				
		return (val != oldVal);
	}

	template<typename T> T absFun(T a)
	{
		if (a>0) return a;
		return -a;
	}

	template<typename T> int signFun(T a)
	{
		if (a>0) return 1;
		else if (a<0) return -1;
		else return 0;
	}

	template<typename T> int signFun(T a, int zeroSign)
	{
		if (a>0) return 1;
		else if (a<0) return -1;
		else return zeroSign;
	}



	template<typename T> int bSignFun(T a)
	{
		if (a>=0) return 1;
		else return -1;
	}

	template<typename T> bool between(T val, T min, T max)
	{
		if (val<min) return false;
		return (val<=max);
	}

	template<typename T> void swap(T& a, T& b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

	template<typename T> void copyFun(T *fromArr, T *toArr, uint nElements)
	{
		for(uint i=0; i<nElements; ++i)
		{
			toArr[i] = fromArr[i];
		}
	}

	template<typename T> void copyFun(T *fromArr, uint fromElementStride, T *toArr, uint toElementStride, uint nElements)
	{
		uint fromElementInterval = fromElementStride + 1;
		uint toElementInterval = toElementStride + 1;
		
		for(uint i=0; i<nElements; ++i)
		{
			toArr[i*toElementInterval] = fromArr[i*fromElementInterval];
		}
	}

	template<typename T> void zeroFun(T *arr, uint nElements)
	{
		for(uint i=0; i<nElements; i++)
		{
			arr[i] = 0;
		}
	}

	template<typename T> void assignAll(T *arr, T value, uint nElements)
	{
		for(uint i=0; i<nElements; ++i)
		{
			arr[i] = value;
		}
	}

	template<typename T> T randFun(T min, T max)
	{
		return (static_cast<T>(rand())*(max-min))/static_cast<T>(32768) + min;
	}

};

#endif
