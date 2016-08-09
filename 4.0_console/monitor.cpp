#include "stdafx.h"
#include "monitor.h"

monitor::monitor(string saveFile)
{
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

monitor::productivity monitor::lookUp(tstring window_title)
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

void monitor::save(tstring window_title, productivity p)
{
	newData.push_back(pair<tstring, monitor::productivity>(window_title, p));
}