// 4.0_console.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include <string>
#include <windows.h>
#include <clocale>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef UNICODE | _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

using namespace std;

string fn = "productivity_record.bin";
typedef enum
{
	NOT_PRODUCTIVE,
	PRODUCTIVE,
	UNDECIDED
}productivity;

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
productivity getProductivity(wstring searchTerm)
{
	wfstream data(fn, ios::in | ios::binary);
	tstring curr_line;
	productivity pr(UNDECIDED);
	if (data.good())
	{
		while (getline(data, curr_line)) //keep reading new lines until searchterm is found
		{
			wcout << _T("curr line = ") << curr_line << endl;
			if (getTitle(curr_line) == searchTerm) //found
			{
				cout << "found, value = ";
				wcout << curr_line[curr_line.size() - 1] << endl; 
				switch (curr_line[curr_line.size() - 1])
				{
				case _T('0'):
					pr = NOT_PRODUCTIVE;
					break;
				case _T('1'):
					pr = PRODUCTIVE;
					break;
				default:
					pr = UNDECIDED;
					break;
				}
				return pr; 
			}
		}
	}

	cout << "not found, undecided = ";
	cout << UNDECIDED << endl;
	return UNDECIDED;
}
productivity analyze(const TCHAR window_title[], size_t title_max_length)
{
	//remove all spaces
	return NOT_PRODUCTIVE;
}


void WriteUnicodetoFile(const char* myFile, tstring& ws) {
	std::ofstream outFile(myFile, std::ios::app |::ios::out | std::ios::binary);
	outFile.write((char *)ws.c_str(), ws.length() * sizeof(TCHAR));
	outFile.close();
}

int main(int argc, _TCHAR* argv[])
{
	TCHAR window_title[256]; //tchar automatically defined to be wchar due to macros. always use tchar consistently
	for (size_t i = 0; i < 256; i++) //initialization
		window_title[i] = _T('\0');
	while(1)
	{
		
		Sleep(500);
	}
	system("PAUSE");
}