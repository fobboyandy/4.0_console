#include "stdafx.h"
#include "wikipedia_functions.h"
#include <unordered_map>
using namespace std;

unordered_map<string, bool> wikipedia_functions::filter = { { "the",false },{ "of",false },{ "an",false } ,{ "a",false } ,{ "as",false } ,{ "at",false } ,{ "but",false } ,{ "by",false } ,{ "in",false } ,{ "from",false } ,{ "off",false } ,{ "on",false } ,{ "than",false } ,{ "with",false },{ "to",false } };



string wikipedia_functions::content;
size_t wikipedia_functions::writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
  //buf is a pointer to the data that curl has for us
  //size*nmemb is the size of the buffer

	for (size_t c = 0; c<size*nmemb; c++)
		wikipedia_functions::content.push_back(buf[c]);
	return size*nmemb; //tell curl how many bytes we handled
}
string wikipedia_functions::scrape(string URL)
{
	wikipedia_functions::content.clear(); //clears content before using
	CURL* curl; //our curl object

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &wikipedia_functions::writeCallback);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return wikipedia_functions::content;
}

string wikipedia_functions::remove_tags(string html_source)
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

unordered_map<string, int> wikipedia_functions::word_sort(string html_content)
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