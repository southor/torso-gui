#ifndef _STATE_GUI_FUNCTIONS_CPP_
#define _STATE_GUI_FUNCTIONS_CPP_

#include "functions.h"

#include "basic_includes.h"

namespace SGui
{
	
	int strNEq(const char *str1, const char *str2)
	{
		assert(str1 && str2);
		
		const char *originalStr1 = str1;
		while((*str1 == *str2) && (*str1 != '\0'))
		{
			++str1;
			++str2;			
		}

		//TODO must use cast to eliminate warning?
		return static_cast<int>(str1 - originalStr1);
	}

	bool beginEq(const char *shortStr, const char *longStr)
	{
		return (strNEq(shortStr, longStr) == std::strlen(shortStr));
	}

	bool beginEq(const char *shortStr, int shortStrLength, const char *longStr)
	{
		assert(shortStrLength >= 0);
		assert(std::strlen(shortStr) == shortStrLength);

		return (strNEq(shortStr, longStr) == shortStrLength);
	}

	int strLenLimit(const char *str, int limit)
	{
		assert(str);
		int i;
		for(i=0; i<limit; ++i)
		{
			if (str[i] == 0) break;
		}
		return i;
	}

	bool atLeastLength(const char *str, int lengthToCheck)
	{
		return (strLenLimit(str, lengthToCheck) == lengthToCheck);
	}

	int readHexChar(char hexChar)
	{
		if ((hexChar >= 'a') && (hexChar <= 'f'))
		{
			return (10 + static_cast<int>(hexChar) - static_cast<int>('a'));
		}
		if ((hexChar >= 'A') && (hexChar <= 'F'))
		{
			return (10 + static_cast<int>(hexChar) - static_cast<int>('A'));
		}
		if ((hexChar >= '0') && (hexChar <= '9'))
		{
			return (static_cast<int>(hexChar) - static_cast<int>('0'));
		}
		else
		{
			assert(false); // not an acceptable character
			return 0;
		}
	}

	int readHexByte(const char *str)
	{
		assert(atLeastLength(str, 2));

		int returnVal = 0;
		returnVal += readHexChar(str[0]) * 16;
		returnVal += readHexChar(str[1]);

		return returnVal;
	}

};

#endif