#include "stdafx.h"
#include "StringHelper.h"

int StringHelper::FindSub(string SourceString, string SubString, int StartPostion)
{
	if (SourceString.length() <= 0 || SubString.length() <= 0 || StartPostion >= SourceString.length())
	{
		return -1;
	}
	for (int i = StartPostion; i < SourceString.length(); ++i)
	{
		for (int j = 0; j <= SubString.length(); ++j)
		{
			if (j == SubString.length())
			{
				return i;
			}
			if (i + j < SourceString.length() && SourceString[i + j] != SubString[j])
			{
				break;
			}
		}
	}
	return -1;
}

int StringHelper::FindSubReverse(string SourceString, string SubString, int StartPostion)
{
	if (SourceString.length() <= 0 || SubString.length() <= 0 || StartPostion >= SourceString.length())
	{
		return -1;
	}
	for (int i = SourceString.length() - SubString.length() - StartPostion; i >= 0; --i)
	{
		for (int j = 0; j <= SubString.length(); ++j)
		{
			if (j == SubString.length())
			{
				return i;
			}
			if (SourceString[i + j] != SubString[j])
			{
				break;
			}
		}
	}
	return -1;
}
