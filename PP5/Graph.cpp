#include "Graph.hpp"

void Graph::addVertex(string label){
	vertexList.push_back(label); 								//add label into vertex vector
}

void Graph::removeVertex(string label){
	Edge *newEdge = new Edge(); 								//create a new edge

	for (unsigned long i = 0; i < vertexList.size(); i++){
		if (vertexList[i] == label){
			vertexList.erase(vertexList.begin() + i); 			//remove the first edge			
			for (unsigned int j = 0; j < vertexEdge.size(); j++){
				newEdge = vertexEdge[j];
				if ((newEdge -> dist1 == label) || (newEdge -> dist2 == label)){
					vertexEdge.erase(vertexEdge.begin() + j); 	//remove the second edge
				}
			}
		}
	}
}

void Graph::addEdge(string label1, string label2, unsigned long weight){
	Edge *newEdge = new Edge(); 								//create a new edge	

	newEdge -> dist1 = label1; 									//labeling 
	newEdge -> dist2 = label2;
	newEdge -> weight = weight;
	vertexEdge.push_back(newEdge); 								//add edge into vertexEdge vector
}

void Graph::removeEdge(string label1, string label2){
	Edge *newEdge = new Edge(); 								//create a new edge
	
	for (unsigned long i = 0; i < vertexEdge.size(); i++){
		newEdge = vertexEdge[i];
		if ((newEdge -> dist1 == label1) && (newEdge -> dist2 == label2)){
			vertexEdge.erase(vertexEdge.begin() + i); 			//create the edge
		}
	}
}

unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string> &path){
	priority_queue<pair<unsigned long, string>, vector<pair<unsigned long, string>>, greater<pair<unsigned long, string>>> pq;

	map<string, unsigned long> distance; 						//a map to hold distance
	map<string, string> vertices; 								//a map to hold vertices
	
	for(const auto label : vertexList){
		distance[label] = 4294967295; 							//distance could be infinity
		vertices[label] = "STOP";
	}
	
	pq.push(make_pair(0, startLabel)); 						//first label has distance of 0
	distance[startLabel] = 0; 									//first label has distance of 0

	while (!pq.empty()){
		string temp = pq.top().second;
		pq.pop(); 											//pop value off

		string str2;

		for (auto curr : vertexEdge){
			if (curr -> dist1 == temp){
				str2 = curr -> dist2;
			}else if (curr -> dist2 == temp){
				str2 = curr->dist1;
			}else{
				continue;
			}
			unsigned long weight = curr -> weight;

			if (distance[str2] > (distance[temp] + weight)){
				vertices[str2] = temp;
				distance[str2] = distance[temp] + weight;
				pq.push(make_pair(distance[str2], str2));
			}
		}
	}	
	path.push_back(startLabel);
	findPath(vertices, endLabel, path);
	
	return distance[endLabel];
}

void Graph::findPath(map<string, string> startLabel, string endLabel, vector<string> &path){
	if (startLabel[endLabel] == "STOP"){
		return;
	}	
	findPath(startLabel, startLabel[endLabel], path); 			//creating path
	path.push_back(endLabel);
}
