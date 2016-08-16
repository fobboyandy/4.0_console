#pragma once
#include "common.h"
#include "curl_functions.h"

//adj list graph implementation using vectors as lists
class vertex
{
public:
	vertex(string vtxName);
	void connect(vertex* vPtr);//add vPtr to edges, follow vPtr and add this to vPtr list of edges.
	void disconnect(vertex* vPtr);//follow it and remove the connection between this vertex and its neighbor
	void getNeighbors() const;
	string getName() const;
	void setProductivity(productivity pValue); //when the productivity of a searchTerm vertex changes, the neighboring vertexValues needs to be updated
	productivity getProductivity(double threshold); //updates and retrives pValue by summing the neighbor vertex values
private:
	vector<vertex*> edges; //new edges are created when vertices are connected, deleted when neighbor vertices get deleted
	string vertexName;
	double vertexValue;
	productivity pValue;
};

class productivityNetwork
{
public:
	~productivityNetwork();
	productivity getProductivity(string searchTerm, double threshold);//used for retrieving productivity of a topic
	void setProductivity(string searchTerm, productivity pValue);
	void getNeighbors(string vertexName);
private:
	vertex* addNetwork(string searchTerm, vector<string> searchResults); //helper function for adding a vertex
	unordered_map<string, vertex*> vertexTable; //vertextable gets updated when a vertex is added
};