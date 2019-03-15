#pragma once
#include <vector>
#include <string>

using namespace std;

/******************************************************************/
/* This algorithm was posted by Mahmoud Al-Qudsi to StackOverflow */
/* http://stackoverflow.com/questions/10051679/c-tokenize-string  */
/* 4/7/2012                                                       */
/******************************************************************/

vector<string> inline StringSplit(const string &source,
	const char *delimiter = " ",
	bool keepEmpty = false)
{
	vector<string> results;

	size_t prev = 0;
	size_t next = 0;

	while ((next = source.find_first_of(delimiter, prev)) != string::npos)
	{
		if (keepEmpty || (next - prev != 0))
		{
			results.push_back(source.substr(prev, next - prev));
		}
		prev = next + 1;
	}

	if (prev < source.size())
	{
		results.push_back(source.substr(prev));
	}

	return results;
}