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
	void save(const tstring &window_title, const monitor::productivity &pValue);
	productivity analyze(const tstring &window_title);
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

	productivity lookUp(const tstring &window_title);
	productivity predict(tstring page_name);
	vector<pair<tstring, productivity>> newData;
	vector<tstring> browsers;
};