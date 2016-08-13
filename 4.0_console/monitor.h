#pragma once

#include "stdafx.h"
#include "common.h"

using namespace std;

class monitor
{
public:
	monitor(string saveFile);
	void save(const tstring &window_title, const productivity &pValue);
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
		void save(tstring window_title, productivity pValue);
	}dataStorage;

	productivity lookUp(const tstring &window_title);
	productivity predict(tstring page_name);
	vector<pair<tstring, productivity>> newData;
	vector<tstring> browsers;
};