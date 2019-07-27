#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "GraphBase.hpp"

using namespace std;

class Edge{
	public:
		string dist1, dist2;
		unsigned long weight;
		Edge(){dist1 = ""; dist2 = ""; weight = 0;};
		~Edge(){};
};

class Graph : public GraphBase{
	public:
		friend class Edge;
		
		vector<string> vertexList;
		vector<Edge*> vertexEdge;
		
		void addVertex(string label);
		void removeVertex(string label);
		void addEdge(string label1, string label2, unsigned long weight);	
		void removeEdge(string label1, string label2);
		unsigned long shortestPath(string startLabel, string endLabel, vector<string> &path);
		void findPath(map<string, string> startLabel, string endLabel, vector<string> &path);

};

#endif
