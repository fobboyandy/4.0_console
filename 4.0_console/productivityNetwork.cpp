#include "stdafx.h"
#include "productivityNetwork.h"

void vertex::connect(vertex* vPtr)//add vPtr to edges, follow vPtr and add this to vPtr list of edges.
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

void vertex::disconnect(vertex* vPtr)//follow it and remove the connection between this vertex and its neighbor
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

void vertex::getNeighbors() const
{
	for (size_t i = 0; i < edges.size(); i++)
		cout << edges[i]->getName() << endl;
	if (edges.size() == 0)
		cout << "empty " << endl;
}

string vertex::getName() const { return vertexName; }

productivityNetwork::~productivityNetwork()
{
	for (auto it = vertexTable.begin(); it != vertexTable.end(); it++)
		delete it->second;
}

productivity productivityNetwork::getProductivity(string searchTerm)//used for retrieving productivity of a topic
{
	vector<string> searchResults = curl_functions::googleSearch(searchTerm, 2);
	addNetwork(searchTerm, searchResults);
	return productivity();
}

void productivityNetwork::getNeighbors(string vertexName)
{
	vertexTable[vertexName]->getNeighbors();// this can't be const because [] operator for map isn't const
}

void productivityNetwork::addNetwork(string searchTerm, vector<string> searchResults) //helper fucntion for adding a vertex
{
	auto lookUp = vertexTable.find(searchTerm);//first look for searchTerm vertex
	if (lookUp == vertexTable.end())//searchTerm vertex not found, create a new one
	{
		vertex* searchTermVertexPtr = new vertex(searchTerm);
		vertexTable[searchTerm] = searchTermVertexPtr;//add searchtermvertex to table
		for (size_t i = 0; i < searchResults.size(); i++)
		{
			lookUp = vertexTable.find(searchResults[i]);
			if (lookUp == vertexTable.end())//vertex not found
			{
				vertex* newVertex = new vertex(searchResults[i]);
				vertexTable[searchResults[i]] = newVertex;
				searchTermVertexPtr->connect(newVertex);
			}
			else
				searchTermVertexPtr->connect(lookUp->second);//if the vertex exist then connect the searchTerm vertex to the existing vertex
		}
	}//if the search parameter already exists then the network has been built before and there is no need to build another
}