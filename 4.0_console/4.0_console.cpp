// 4.0_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include "productivityNetwork.h"

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
string translate(productivity productivityCode)
{
	switch (productivityCode)
	{
	case productivity::NOT_PRODUCTIVE:
		return "NOT PRODUCTIVE";
	case productivity::PRODUCTIVE:
		return "PRODUCTIVE";
	case productivity::NOT_FOUND:
		return "NOT FOUND";
	case productivity::UNDECIDED:
		return "UNDECIDED";
	default:
		return "INVALID";
	}
}
//tells whether google chrome is the current window using substring
bool isGoogleChrome(tstring window_title)
{
	tstring criteria = _T("- Google Chrome");
	if (window_title.find(criteria) != std::string::npos)
		return true;
	return false;
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
	productivityNetwork pnetwork;

	pnetwork.getProductivity("references for c++");
	pnetwork.getProductivity("c++ references");

	pnetwork.getNeighbors("references for c++");
	cout << endl << endl << endl;
	pnetwork.getNeighbors("c++ references");


	
	cout << endl << endl << endl;

	system("pause");
	//find a way to get destructor to be called upon close
}