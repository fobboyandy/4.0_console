#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "common.h"
#include "curl_functions.h"
using namespace std;

class vertex
{
public:
	vertex(string vtxName) :vertexName(vtxName), vertexValue(0), pValue(UNDECIDED){}
	void connect(vertex* vPtr)//add vPtr to edges, follow vPtr and add this to vPtr list of edges.
	{
		for (size_t i = 0; i < edges.size(); i++)
			if (edges[i] == vPtr)
				return;//return if already connected;
		if (vPtr != this)//can't connect to self
		{
			edges.push_back(vPtr);
			vPtr->edges.push_back(this);
		}
	}
	void disconnect(vertex* vPtr)//follow it and remove the connection between this vertex and its neighbor
	{
		for (auto it = vPtr->edges.begin(); it != vPtr->edges.end(); it++) //delete connection to this from neighbor
			if (*it == this)
			{
				vPtr->edges.erase(it);
				break;//need to break once erased;
			}
		for (auto it = edges.begin(); it != edges.end(); it++) //delete connection to neighbor
			if (*it == vPtr)
			{
				edges.erase(it);
				break;
			}
	}
	void getNeighbors()
	{
	
		for (size_t i = 0; i < edges.size(); i++)
			cout << edges[i]->getName() << endl;
		if (edges.size() == 0)
			cout << "empty " << endl;
	}
	string getName(){ return vertexName; }
private:
	vector<vertex*> edges; //new edges are created when vertices are connected, deleted when neighbor vertices get deleted
	string vertexName;
	float vertexValue;
	productivity pValue;
};

class productivityNetwork
{
public:
	productivity getProductivity(string searchTerm)//used for retrieving productivity of a topic
	{

	}
private:
	void addVertex(string searchTerm) //helper fucntion for adding a vertex
	{

	}
	unordered_map<string, vertex*> vertexTable; //vertextable gets updated when a vertex is added
};