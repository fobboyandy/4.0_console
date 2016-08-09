#pragma once

#include "stdafx.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <TCHAR.h>
#include <vector>

using namespace std;

#if defined(UNICODE) || defined(_UNICODE)
typedef wstring tstring;
#else
typedef  string tstring;
#endif // UNICODE | _UNICODE

class monitor
{
public:
	enum productivity
	{
		PRODUCTIVE = 0,
		NOT_PRODUCTIVE = 1,
		UNDECIDED = 2,
		NOT_FOUND = 3
	};
	monitor(string saveFile);
	productivity lookUp(tstring window_title);
	void save(tstring window_title, productivity p);
	~monitor();
private:
	struct dataStorage_t
	{
		//members
		wfstream data; //used for title look up
		string saveFile;
		size_t initSize;
		vector<pair<tstring, productivity>> dataMem;
		//functions
		tstring readLine();
		productivity getProductivity(TCHAR pValueChar);
		void save(tstring window_title, monitor::productivity pValue);
	}dataStorage;
	vector<pair<tstring, productivity>> newData;
};