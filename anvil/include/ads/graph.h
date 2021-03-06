#pragma once
#include <set>
#include <unordered_map>

typedef int GraphIdentifier;
typedef int EdgeWeight;

struct GraphEdge {
	EdgeWeight weight;
	GraphIdentifier neighbor;
};

template<typename T> 
struct GraphVertex {
	std::set<GraphEdge> connections;
	bool AddConnection(GraphIdentifier id) {
		auto result = this->connections.insert({0, id});
		return result->second;
	}
	bool RemoveConnection(GraphIdentifier id) {
		return false;
	}
};



template<typename T>
class Graph {
public:
	Graph() {}
	~Graph() {
		for (auto& it = this->verticies.begin(i); it != this->verticies.end(i); ++it) {
			delete it->second;
		}
	}
	bool Add(GraphIdentifier id) {
		if (this->Get(id) == NULL) {
			this->verticies[id] = new GraphVertex<T>();
			return true;
		}
		return false;
	}
	bool Remove(GraphIdentifier id) {
		if (this->Get(id) != NULL) {
			delete this->verticies[id];
			this->verticies[id] = NULL;
			return true;
		}
		return false;
	}
	GraphVertex<T>* Get(GraphIdentifier id) {
		return this->verticies[id];
	}
	void Connect(GraphIdentifier lhs, GraphIdentifier rhs) {
		lhsVert = this->Get(lhs);
		rhsVert = this->Get(rhs);
		if (lhsVert != NULL && rhsVert != NULL) {
			lhsVert->
		}
	}
	std::unordered_map<GraphIdentifier, GraphVertex<T>*> verticies;

};