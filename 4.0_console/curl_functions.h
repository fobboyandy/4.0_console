#ifndef wikipedia_functions_h
#define wikipedia_functions_h

#include "stdafx.h"
#include <string>
#include <unordered_map>
#include "curl.h" //your directory may be different
using namespace std;


namespace curl_functions
{
	extern string content; //will hold the url's html content
	extern unordered_map<string, bool> filter;
	size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
	string scrape(string topic);
	string remove_tags(string html_source);
	unordered_map<string, int> word_sort(string html_content);
}

#endif
