// 4.0_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "monitor.h"
#include "curl_functions.h"
#include <unordered_map>
#include "curl.h"
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


vector<string> googleSearch(string searchTerm, size_t depth)
{
	string validCharSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$'()*,;=";//&+removed
	size_t pageNum = 0;
	for (size_t i = 0; i < searchTerm.size(); i++)
		if (searchTerm[i] == ' ')
			searchTerm[i] = '+';
	vector<string> urlKeep;
nextPage:
	string url = "https://www.google.com/search?q=" + searchTerm + "&start=" + to_string(pageNum); //https://www.google.com/search?q=asdf&start=00
	string pageSource = curl_functions::scrape(url);
	bool searchValid = pageSource.find(" - did not match any documents.") == std::string::npos;
	vector<string> urlList;
	//results found for search parameter
	if (searchValid)
	{
		size_t resultBegin = pageSource.find("<div class=\"sd\" id=\"resultStats\">"); //relevant results are within these bounds
		size_t resultEnd = pageSource.find("<span class=\"csb\"");
		size_t urlIdx = pageSource.find("http", resultBegin);
		string currUrl;
		while (urlIdx < resultEnd)
		{
			bool validChar = false;
			for (size_t i = 0; i < validCharSet.size(); i++)
				if (pageSource[urlIdx] == validCharSet[i])
					validChar = true;
			if (validChar)
			{
				currUrl.push_back(pageSource[urlIdx]);
				urlIdx++;//increment urlIdx by 1 to check next character
			}
			else
			{
				urlIdx = pageSource.find("http", urlIdx);//invalid character reached, jump to the next url
				urlList.push_back(currUrl);
				currUrl.clear();
			}
		}
	}
	//end urlParse//
	for (size_t i = 0; i < urlList.size(); i++)
		if (urlList[i] != "https://www.youtube.com/watch" && urlList[i] != "http://webcache.googleusercontent.com/search" && urlList[i] != "http://www.google.com/aclk?sa=l" && urlList[i] != "http://www.google.com/aclk?sa=L" && urlList[i] != "https://" && urlList[i] != "https://www" && urlList[i] != "https://www.")
			urlKeep.push_back(urlList[i]);
	if (pageNum < depth) //get depth amount of pages of results
	{
		pageNum++;
		goto nextPage;
	}

	return urlKeep;
}


int main(int argc, _TCHAR* argv[]) 
{
	//string fn = "save.txt";
	//monitor monitorObj(fn);
	//TCHAR title[256];
	string searchTerm;
	search:
	getline(cin, searchTerm);
	vector<string> urlList = googleSearch(searchTerm, 6);
	for (size_t i = 0; i < urlList.size(); i++)
		cout << urlList[i] << endl;
	goto search;
	system("pause");
	//find a way to get destructor to be called upon close
}