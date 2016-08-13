#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;
#if defined(UNICODE) || defined(_UNICODE)
typedef wstring tstring;
#else
typedef  string tstring;
#endif // UNICODE | _UNICODE

enum productivity
{
	PRODUCTIVE = 0,
	NOT_PRODUCTIVE = 1,
	UNDECIDED = 2,
	NOT_FOUND = 3
};

