#include "stdafx.h"
#include "monitor.h"

monitor::monitor(string saveFile)
{
	browsers = {_T("- Google Chrome"), _T("- Microsoft Edge"), _T("- Internet Explorer"), _T("- Mozilla Firefox")};
	dataStorage.saveFile = saveFile;
	dataStorage.data.open(saveFile, ios::in);
	if(dataStorage.data)
	{
		while (!dataStorage.data.eof())
		{
			tstring window_title = dataStorage.readLine();
			if(!dataStorage.data.eof())
			{
				tstring pValueStr = dataStorage.readLine();
				productivity p = dataStorage.getProductivity(pValueStr[0]);
				pair<tstring, monitor::productivity> curr_pair(window_title, p);
				dataStorage.dataMem.push_back(curr_pair);
			}
		}
	}
	else
		dataStorage.data.open(saveFile, ios::out); //creates a file if doesn't exist

	dataStorage.data.close();
}
//save new data upon close
monitor::~monitor()
{
	dataStorage.data.open(dataStorage.saveFile, ios::out | ios::trunc);
	for (size_t i = 0; i < newData.size(); i++)
		dataStorage.save(newData[i].first, newData[i].second);
	dataStorage.data.close();
}

tstring monitor::dataStorage_t::readLine()
{
	tstring curr_line;
	TCHAR curr_char;
	if (dataStorage_t::data.good())
	{
		curr_char = dataStorage_t::data.get();
		while (curr_char != _T('\n') && !data.eof())
		{
			curr_line.push_back(curr_char);
			curr_char = dataStorage_t::data.get();
		}
	}
	return curr_line;
}

void monitor::dataStorage_t::save(tstring window_title, monitor::productivity pValue)
{
	dataStorage_t::data.clear();
	dataStorage_t::data.seekg(ios::beg);//reset before saving
	if (dataStorage_t::data.good())
	{
		dataStorage_t::data << window_title << endl;
		dataStorage_t::data << pValue << endl; //output as character instead of value
	}
}

monitor::productivity monitor::lookUp(const tstring &window_title)
{
	//go through stored data
	for (size_t i = 0; i < dataStorage.dataMem.size(); i++)
	{
		if (dataStorage.dataMem[i].first == window_title)
			return dataStorage.dataMem[i].second;
	}
	//go through new data
	for (size_t i = 0; i < newData.size(); i++)
	{
		if (newData[i].first == window_title)
			return newData[i].second;
	}
	return NOT_FOUND; //if reach here then end of vector so not found
}

monitor::productivity monitor::dataStorage_t::getProductivity(TCHAR pValueChar)
{
	switch (pValueChar)
	{
	case _T('0'):
		return PRODUCTIVE;
	case _T('1'):
		return NOT_PRODUCTIVE;
	case _T('2'):
		return UNDECIDED;
	default:
		return UNDECIDED;
	}
	return UNDECIDED;
}

void monitor::save(const tstring &window_title, const monitor::productivity &pValue)
{
	newData.push_back(pair<tstring, monitor::productivity>(window_title, pValue));
}

monitor::productivity monitor::analyze(const tstring &window_title)
{
	//first check memory then check if its a browser, if yes make prediction and update memory. if not then 
	monitor::productivity p = lookUp(window_title);
	if (p != monitor::productivity::NOT_FOUND)
		return p;

	bool isBrowser = false;
	for (size_t i = 0; i < browsers.size(); i++)
	{
		if (window_title.find(browsers[i]))
			isBrowser = true;
	}
	if (isBrowser)
	{
		//use searches to make prediction and use prediction to update pages
	}
	else
	{
		//look in memory
	}
	return p;
}

monitor::productivity monitor::predict(tstring page_name)
{
	return monitor::productivity();
}