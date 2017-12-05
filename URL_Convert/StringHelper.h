#pragma once

#include <string>

using namespace std;

struct StringHelper
{
public:

	/* Find the substring in the source string, start fronm the given position, strat from 0.
	 * SourceString - the string to search.
	 * Substring - aim string to find in source string.
	 * StartPosition - the index of where to start the search in the source string.
	 * return - the position index of the sub string in the source string, -1 if not found. */
	static int FindSub(string SourceString, string SubString, int StartPostion = 0);

	/* Find the substring in the source string, start fronm tail of the string.
	* SourceString - the string to search.
	* Substring - aim string to find in source string.
	* StartPosition - the index of where to start the search in the source string, this is count fronm tail to head.
	* return - the position index of the sub string in the source string, -1 if not found. */
	static int FindSubReverse(string SourceString, string SubString, int StartPostion = 0);
};

