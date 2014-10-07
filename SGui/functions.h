#ifndef _STATE_GUI_FUNCTIONS_H_
#define _STATE_GUI_FUNCTIONS_H_

#include "declares.h"

#include <string>
#include <limits>

namespace SGui
{
	int strNEq(const char *str1, const char *str2);

	/**
	 * tests if the begin of long string is equal to short string.
	 * If the short string has length zero true is returned.
	 * Max string length that can be tested is equal to max of int 
	 */
	bool beginEq(const char *shortStr, const char *longStr);

	bool beginEq(const char *shortStr, int shortStrLength, const char *longStr);

	/**
	 * checks the length of a string, but only up to a certain number of characters.
	 * If string is shorter than limit, the length wil be returned.
	 * If string is at least as long as limit, limit will be returned.
	 */
	int strlenLimit(const char *str, int limit = std::numeric_limits<int>::max());

	// returns true if the string is at least as long as lengthToCheck
	bool atLeastLength(const char *str, int lengthToCheck);

	int readHexChar(char hexChar);
	char getHexChar(int n);

	int readHexByte(const char *str);
	void writeHexByte(int n, char *str);

	void pln(const std::string &str);
	void pln(const char *str);

};

#endif