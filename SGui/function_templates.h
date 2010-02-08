#ifndef _STATE_GUI_FUNCTION_TEMPLATES_H_
#define _STATE_GUI_FUNCTION_TEMPLATES_H_

#include "declares.h"

namespace SGui
{

	// TODO instead of uint use size_t

	/**
	 * Loops the value so that it will be inside Min, Max
	 * @param value The value to loop
	 * @param min The minimum value it can have
	 * @param max The maximum value it can have
	 * @return the looped value
	 */
	template<typename T> T loop(T value,T min,T max);
	
	/**
	 * Bounces the value so that it will be inside Min, Max
	 * @param value The value to loop
	 * @param min The minimum value it can have
	 * @param max The maximum value it can have
	 * @return the bounced value
	 */
	template<typename T> T bounce(T value, T min, T max);

	/**
	 * This function returns the minimum value of two values.	 
	 * @param a The first value.
	 * @param b The second value.
	 * @return the min value.
	 */
	template<typename T> inline T minFun(T a, T b)			{ return a < b ? a : b; }

	/**
	 * This function returns the maximum value of two values.	 
	 * @param a The first value.
	 * @param b The second value.
	 * @return the max value.
	 */
	template<typename T> inline T maxFun(T a, T b)			{ return a > b ? a : b; }

	template<typename T> T absFun(T a);

	template<typename T> int signFun(T a);

	template<typename T> int signFun(T a, int zeroSign);

	template<typename T> int bSignFun(T a);

	template<typename T> T xor(T a, T b)		{ return (a && !b) || (!a && b); }

	template<typename T> T bitXOr(T a, T b)		{ return (a & ~b) | (~a & b); }
	

	/**
	 * Applies both max and min functions.
	 * The resulting value will be between min and max.
	 * @param val The value to be limited
	 * @param min The minimum value
	 * @param max The maximum value.
	 * @return The resulting value.
	 */
	template<typename T> inline T limit(T val, T min, T max)
	{
		if (val<=min) return min;
		if (val>max) return max;
		return val;
	}

	/**
	 * Applies both max and min functions.
	 * The resulting value will be between min and max.
	 * @param val The value to be restrained, this will be modified
	 *			  to fullfill between(val, min, max) == true.
	 * @param min The minimum value
	 * @param max The maximum value.
	 * @return true if the value was changed.
	 */
	template<typename T> bool restrain(T &val, T min, T max);

	/**
	 * Checks if val is between min and max, to be exact:
	 *    min <= val <= max
	 * if this is not the case false is returned, otherwise true.
	 * The resulting value will be between min and max.
	 * @param min The minimum value
	 * @param max The maximum value.
	 * @return True if val is between the 2 values.
	 */
	template<typename T> bool between(T val, T min, T max);


	/**
	 * Swaps 2 objects.
	 * Objects must have a copy constructor and an assignment operator
	 * @param a object a
	 * @param b object b
	 */
	template<typename T> void swap(T& a, T& b);

	/**
	 * Copys nElements elements from arrFrom to arrTo, uses operator= .
	 * @param arrFrom The array to copy from.
	 * @param arrTo The array to copy to.
	 * @param nElements number of elements to copy.
	 */
	template<typename T> void copyFun(const T *fromArr, T *toArr, size_t nElements);

	/**
	 * Copys nElements elements from arrFrom to arrTo, uses operator= .
	 * @param arrFrom The array to copy from.
	 * @param arrTo The array to copy to.
	 * @param nElements number of elements to copy.
	 */
	template<typename T> void copyFun(const T *fromArr, size_t fromElementStride, T *toArr, size_t toElementStride, size_t nElements);

	/**
	 * assigns every element in the array to zero.
	 * @param arr The array
	 * @param nElements Number of elements in the array.
	 */
	template<typename T> void zeroFun(T *arr, size_t nElements);

	/**
	 * Assigns all elements in the array to value.
	 * @param arr The array.
	 * @param value The value that all elements should be assigned to.
	 * @param nElements Number of elements in the array.
	 */
	template<typename T> void assignAll(T *arr, T value, size_t nElements);

	/**
	 * Assigns all elements in the array to value.
	 * @param arr The array.
	 * @param value The value that all elements should be assigned to.
	 * @param nElements Number of elements in the array.
	 */
	template<typename T> void assignAll(T *arr, size_t stride, T value, size_t nElements);


	template<typename T> T randFun(T min, T max);

	/**
	 * @flags flags that should be tested.
	 * @allowedFlags The allowed flags.
	 * @return Returns true if flags only have allowed flags activated.
	 */	
	template<typename T> inline bool checkFlags(T flags, T allowedFlags)
	{
		return !(flags & ~allowedFlags);
	}

	template<typename T> inline bool checkAlternative(T alternative, T nAlternatives)
	{
		return (alternative < nAlternatives) && (alternative >= 0);
	}

	template<typename T, typename S>
	T myLShift(T x, S n)
	{
		if (n > 0) return x << n;
		else return x >> -n;
	}

	template<typename T, typename S>
	T myRShift(T x, S n)
	{
		if (n > 0) return x >> n;
		else return x << -n;
	}
	
	template<typename T>
	T twoToThePowerOf(int n)
	{
		T x(1);
		return myLShift<T>(x, n);
	}

	

	

};

#endif