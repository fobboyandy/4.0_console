// 4.0_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "monitor.h"
#include <iostream>

using namespace std;

tstring removeSpaces(const TCHAR original[], size_t max_length)
{
	tstring stringBuffer;
	for (size_t i = 0; i < max_length && original[i] != TEXT('\0'); i++)
	{
		if (original[i] != _T(' '))
			stringBuffer.push_back(original[i]);
	}
	return stringBuffer;
}

tstring getTitle(const tstring &curr_line)
{
	tstring title;
	size_t i = 0;
	while (curr_line[i] != _T(' '))
	{
		title.push_back(curr_line[i]);
		i++;
	}
	return title;
}
string translate(monitor::productivity productivityCode)
{
	switch (productivityCode)
	{
	case monitor::productivity::NOT_PRODUCTIVE:
		return "NOT PRODUCTIVE";
	case monitor::productivity::PRODUCTIVE:
		return "PRODUCTIVE";
	case monitor::productivity::NOT_FOUND:
		return "NOT FOUND";
	case monitor::productivity::UNDECIDED:
		return "UNDECIDED";
	default:
		return "INVALID";
	}
}

tstring toString(TCHAR titleArray[], size_t max_length)
{
	tstring titleStr;
	for (size_t i = 0; titleArray[i] != _T('\0') && i < max_length; i++)
		titleStr.push_back(titleArray[i]);
	return titleStr;
}
int main(int argc, _TCHAR* argv[])
{
	string fn = "save.txt";
	monitor monitorObj(fn);
	TCHAR title[256];
	int userResponse;
	while (1)
	{
		Sleep(5);
		GetWindowText(GetForegroundWindow(), title, 256);
		tstring window_title = toString(title, 256);
		monitor::productivity prod = monitorObj.lookUp(window_title);
		if (prod == monitor::productivity::NOT_FOUND)
		{
			userResponse = MessageBox(NULL, (_T("Is ") + window_title + _T(" productive?")).c_str(), _T("4.0 Productivity Monitor"), MB_YESNO);
			if (userResponse == IDYES)
				monitorObj.save(window_title, monitor::productivity::PRODUCTIVE);
			else
				monitorObj.save(window_title, monitor::productivity::NOT_PRODUCTIVE);
		}
		else
			cout << translate(prod) << endl;
	}

	//find a way to get destructor to be called upon close
}