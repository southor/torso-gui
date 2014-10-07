#include "functions.h"
#include "function_templates.inl"

#include "basic_includes.h"
#include "macros.h"

#include <iostream>

namespace SGui
{
	
	int strNEq(const char *str1, const char *str2)
	{
		dAssert(str1 && str2);
		
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
		return (strNEq(shortStr, longStr) == strlenLimit(shortStr));
	}

	bool beginEq(const char *shortStr, int shortStrLength, const char *longStr)
	{
		dAssert(shortStrLength >= 0);
		dAssert(std::strlen(shortStr) == shortStrLength);

		return (strNEq(shortStr, longStr) == shortStrLength);
	}

	int strlenLimit(const char *str, int limit)
	{
		dAssert(str);
		int i;
		for (i = 0; i<limit; ++i)
		{
			if (str[i] == 0) break;
		}
		return i;
	}

	bool atLeastLength(const char *str, int lengthToCheck)
	{
		return (strlenLimit(str, lengthToCheck) == lengthToCheck);
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
			dAssert(false); // not an acceptable character
			return 0;
		}
	}

	char getHexChar(int n)
	{
		restrain(n, 0, 15);
		if (n < 10) return static_cast<char>('0' + n);
		else return static_cast<char>('a' + n - 10);
	}

	int readHexByte(const char *str)
	{
		dAssert(atLeastLength(str, 2));

		int returnVal = 0;
		returnVal += readHexChar(str[0]) * 16;
		returnVal += readHexChar(str[1]);

		return returnVal;
	}

	void writeHexByte(int n, char *str)
	{
		dAssert(atLeastLength(str, 2));
		str[0] = getHexChar(n / 16);
		str[1] = getHexChar(n % 16);
	}

	void pln(const std::string &str)
	{
		std::cout << str << std::endl;
	}

	void pln(const char *str)
	{
		std::cout << str << std::endl;
	}

};
