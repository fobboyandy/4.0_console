#pragma once
#include "common.h"
#include "curl_functions.h"

class vertex
{
public:
	vertex(string vtxName) :vertexName(vtxName), vertexValue(0), pValue(UNDECIDED){}
	void connect(vertex* vPtr);//add vPtr to edges, follow vPtr and add this to vPtr list of edges.
	void disconnect(vertex* vPtr);//follow it and remove the connection between this vertex and its neighbor
	void getNeighbors() const;
	string getName() const;
private:
	vector<vertex*> edges; //new edges are created when vertices are connected, deleted when neighbor vertices get deleted
	string vertexName;
	float vertexValue;
	productivity pValue;
};

class productivityNetwork
{
public:
	~productivityNetwork();
	productivity getProductivity(string searchTerm);//used for retrieving productivity of a topic
	void getNeighbors(string vertexName);
private:
	void addNetwork(string searchTerm, vector<string> searchResults); //helper fucntion for adding a vertex
	unordered_map<string, vertex*> vertexTable; //vertextable gets updated when a vertex is added
};