// 4.0_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "monitor.h"
#include "curl_functions.h"
#include "productivityNetwork.h"
#include <unordered_map>
#include "curl.h"
#include "common.h"

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
	//string searchTerm;
	//search:
	//getline(cin, searchTerm);
	//vector<string> urlList = googleSearch(searchTerm, 6);
	//for (size_t i = 0; i < urlList.size(); i++)
	//	cout << urlList[i] << endl;
	//goto search;


	//string searchTerm1 = "cs1.6";
	//vector<string> cs16;
	//cs16.push_back("gamebanana");
	//cs16.push_back("wikipedia");
	//cs16.push_back("twitchtv");
	//cs16.push_back("csdownload");
	//cs16.push_back("steampowered");

	//vector<string> csgo;
	//csgo.push_back("counterstrike.net");
	//csgo.push_back("steampowered");
	//csgo.push_back("reddit");
	//csgo.push_back("csgolounge");
	//csgo.push_back("gamebanana");

	//unordered_map<string, vertex*> vertexTable; //vertextable gets updated when a vertex is added

	//auto lookUp = vertexTable.find("cs1.6");//first look for searchTerm vertex
	//if (lookUp == vertexTable.end())//searchTerm vertex not found, need to create a new one
	//{
	//	vertex* searchTermVertexPtr = new vertex(searchTerm1);
	//	vertexTable[searchTerm1] = searchTermVertexPtr;//add searchtermvertex to table
	//	for (size_t i = 0; i < cs16.size(); i++)
	//	{
	//		lookUp = vertexTable.find(cs16[i]);
	//		if (lookUp == vertexTable.end())//vertex not found
	//		{
	//			vertex* newVertex = new vertex(cs16[i]);
	//			vertexTable[cs16[i]] = newVertex;
	//			searchTermVertexPtr->connect(newVertex);
	//		}
	//		else
	//			searchTermVertexPtr->connect(lookUp->second);//if the vertex exist then connect the searchTerm vertex to the existing vertex
	//	}
	//}
	//cout << endl << endl;
	//lookUp = vertexTable.find("csgo");//first look for searchTerm vertex
	//if (lookUp == vertexTable.end())//searchTerm vertex not found, need to create a new one
	//{
	//	vertex* searchTermVertexPtr = new vertex("csgo");
	//	vertexTable["csgo"] = searchTermVertexPtr;//add csgo to table
	//	for (size_t i = 0; i < csgo.size(); i++)
	//	{
	//		lookUp = vertexTable.find(csgo[i]);
	//		if (lookUp == vertexTable.end())//vertex not found
	//		{
	//			vertex* newVertex = new vertex(csgo[i]);
	//			vertexTable[csgo[i]] = newVertex;
	//			searchTermVertexPtr->connect(newVertex);
	//		}
	//		else
	//			searchTermVertexPtr->connect(lookUp->second);//if the vertex exist then connect the searchTerm vertex to the existing vertex
	//	}
	//}
	//
	//vertexTable["gamebanana"]->getNeighbors();

	//for (auto it = vertexTable.begin(); it != vertexTable.end(); it++)
	//	delete it->second;



	productivityNetwork pnetwork;

	pnetwork.getProductivity("csgo");
	pnetwork.getProductivity("cs source");


	pnetwork.getNeighbors("http://www.counter-strike.net/");
	cout << endl << endl << endl;

	system("pause");
	//find a way to get destructor to be called upon close
}