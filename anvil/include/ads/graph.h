#pragma once
#include <vector>
#include <unordered_map>

typedef int GraphIdentifier;
typedef int EdgeWeight;
template<typename T> 
struct GraphVertex {
	std::vector<GraphIdentifier> connections;
};

struct GraphEdge {
	EdgeWeight weight;
};

template<typename T>
class Graph {
public:
	Graph() {}
	~Graph() {
		for (auto it = this->verticies.begin(i); it != this->verticies.end(i); ++it) {
			delete it->second;
		}
	}
	void Add(GraphIdentifier id) {
		if (this->verticies[id] == NULL) {
			this->verticies[id] = new GraphVertex<T>();
		}

	}
	void Remove(GraphIdentifier id) {
		if (this->verticies[id] != NULL) {
			delete this->verticies[id];
			this->verticies[id] = NULL;
		}
	}
	GraphVertex<T>* Get(GraphIdentifier id) {
		return this->verticies[id];
	}
	void Connect(GraphIdentifier lhs, GraphIdentifier rhs) {}
	std::unordered_map<GraphIdentifier, GraphVertex<T>*> verticies;

};