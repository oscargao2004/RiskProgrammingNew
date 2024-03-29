#pragma once
#include <vector>
#include "Vertex.h"
#include "Edge.h"
using namespace std;
class Graph
{

	vector<vector<Vertex>> adjList; 

	vector<Vertex> _vertices;
	vector<Edge> _edges;

public:
	int numVertices();
	int numEdges();
	vector<Vertex> vertices();
	vector<Edge> edges();

	int degree(Vertex);
	vector<Vertex> adjacentVertices(Vertex);
	vector<Edge> incidentEdges(Vertex);
	vector<Vertex> endVertices(Edge);
	Vertex opposite(Vertex, Edge);
};

int Graph::numVertices(){}
int Graph::numEdges(){}
vector<Vertex> Graph::vertices(){}
vector<Edge> Graph::edges(){}
int Graph::degree(Vertex v){}
vector<Vertex> Graph::adjacentVertices(Vertex v){}
vector<Edge> Graph::incidentEdges(Vertex v){}
vector<Vertex> Graph::endVertices(Edge e){}
Vertex Graph::opposite(Vertex v, Edge e){}









