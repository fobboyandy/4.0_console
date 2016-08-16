#include "stdafx.h"
#include "productivityNetwork.h"

vertex::vertex(string vtxName) :vertexName(vtxName), vertexValue(0), pValue(UNDECIDED)
{

}

//this function needs to be called whenever the productivity of a search vertex is changed. 
//it takes all the neighboring vertices and recalculates the vertexValue
void vertex::setProductivity(productivity pValue)
{
	double sum = 0;
	int contribution;
	pValue == PRODUCTIVE ? contribution = 1 : contribution = -1;
	for (size_t i = 0; i < edges.size(); i++)
	{
		vertex &neighbor = *edges[i];
		//numEdges - 1 because the number of edges is incremented upon connecting. 
		cout << neighbor.vertexValue << endl;// << " " << neighbor.edges.size() << " " << contribution << endl;
		neighbor.vertexValue = (neighbor.vertexValue*(neighbor.edges.size() - 1) + contribution) / neighbor.edges.size();
	}
}

productivity vertex::getProductivity(double threshold)
{
	double sum = 0;
	for (size_t i = 0; i < edges.size(); i++)
		sum += edges[i]->vertexValue;
	if (abs(sum) > threshold)
	{
		if (sum > 0) //positive
			pValue = PRODUCTIVE;
		else
			pValue = NOT_PRODUCTIVE;
	}
	else
		pValue = UNDECIDED;
	cout << sum << endl;
	return pValue;
}

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

//improve this by adding an extra parameter of how deep the getproductivity wants to traverse for relationships
//eg. by default, only the neighboring values are summed up, but it can traverse further and look for secondary connections
productivity productivityNetwork::getProductivity(string searchTerm, double threshold)//used for retrieving the sum of the values of the neighbor nodes
{
	productivity p;
	vertex* vPtr;
	auto lookUp = vertexTable.find(searchTerm);//first look for searchTerm vertex
	if (lookUp == vertexTable.end()) //network for searchTerm doesn't exist yet, create it
	{
		vector<string> searchResults = curl_functions::googleSearch(searchTerm, 2);
		vPtr = addNetwork(searchTerm, searchResults);
		p = vPtr->getProductivity(threshold);
	}
	else // the network already exists retrive the sum of values
	{
		vPtr = lookUp->second;
		p = lookUp->second->getProductivity(threshold);
	}
	//after calculating productivity, the neighbors should be readjusted using the new experience
	if (p != NOT_PRODUCTIVE)
		vPtr->setProductivity(p);
	return p;
}

void productivityNetwork::getNeighbors(string vertexName)
{
	vertexTable[vertexName]->getNeighbors();// this can't be const because [] operator for map isn't const
}

vertex* productivityNetwork::addNetwork(string searchTerm, vector<string> searchResults) //helper fucntion for adding a vertex
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
	return vertexTable[searchTerm];
}


void productivityNetwork::setProductivity(string searchTerm, productivity pValue)
{
	vertexTable[searchTerm]->setProductivity(pValue);
}