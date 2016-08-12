#include "stdafx.h"
#include "curl_functions.h"
#include <unordered_map>
using namespace std;

unordered_map<string, bool> curl_functions::filter = { { "the",false },{ "of",false },{ "an",false } ,{ "a",false } ,{ "as",false } ,{ "at",false } ,{ "but",false } ,{ "by",false } ,{ "in",false } ,{ "from",false } ,{ "off",false } ,{ "on",false } ,{ "than",false } ,{ "with",false },{ "to",false } };

string curl_functions::content;
size_t curl_functions::writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
  //buf is a pointer to the data that curl has for us
  //size*nmemb is the size of the buffer

	for (size_t c = 0; c<size*nmemb; c++)
		curl_functions::content.push_back(buf[c]);
	return size*nmemb; //tell curl how many bytes we handled
}
string curl_functions::scrape(string URL)
{
	curl_functions::content.clear(); //clears content before using
	CURL* curl; //our curl object

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curl_functions::writeCallback);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return curl_functions::content;
}

string curl_functions::remove_tags(string html_source)
{
	string buffer; //contains the information with tags filtered out
	bool push = true;
	for (size_t i = 0; i < html_source.length(); i++)
	{
		if (html_source[i] == '<')
			push = false;
		else if (push == false && html_source[i] == '>')
		{
			push = true;
			continue;
		}
		if (push)
			buffer.push_back(html_source[i]);
	}
	return buffer;
}

unordered_map<string, int> curl_functions::word_sort(string html_content)
{
	unordered_map<string, int> frequency_dictionary;
	string word;
	word.clear();
	for (size_t i = 0; i < html_content.length(); i++)
	{
		if ((html_content[i] >= '0' && html_content[i] <= '9') || (html_content[i] >= 'a' && html_content[i] <= 'z') || (html_content[i] >= 'A' && html_content[i] <= 'Z') || html_content[i] == '-') //is forming a word
		{
			word.push_back(tolower(html_content[i])); //capture character
		}
		else if (html_content[i] == '<')
		{
			while (html_content[i] != '>')
				i++;
		}
		else //word terminated by non character
		{
			if (filter.find(word) == filter.end()) //not a filler word
				frequency_dictionary[word]++;
			word.clear();
		}
	}
	unordered_map<string, int> sorted_list;

	for (auto it = frequency_dictionary.begin(); it != frequency_dictionary.end(); it++)
		if (it->second > 5 && it->second < 15)
			sorted_list.insert(*it);

	return sorted_list;
}

vector<string> curl_functions::googleSearch(string searchTerm, size_t depth)
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