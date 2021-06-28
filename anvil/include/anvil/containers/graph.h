#pragma once
#include "anvil/containers/list.h"
#include "anvil/containers/map.h"
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

typedef i64_t GRAPH_VERTEX_KEY;

struct GraphVertex {
    GRAPH_VERTEX_KEY key;
};

template <>
struct Hashable<GraphVertex> {  // knuth
    static long Hash(GraphVertex vert) {
        return Hashable<GRAPH_VERTEX_KEY>::Hash(vert.key);
    }
};

struct GraphEdge {
};

/*
    adjacent(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
    neighbors(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y;
    add_vertex(G, x): adds the vertex x, if it is not there;
    remove_vertex(G, x): removes the vertex x, if it is there;
    add_edge(G, x, y): adds the edge from the vertex x to the vertex y, if it is not there;
    remove_edge(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
    get_vertex_value(G, x): returns the value associated with the vertex x;
    set_vertex_value(G, x, v): sets the value associated with the vertex x to v.
*/
struct Graph {
    Graph();
    ~Graph();

    Option<GraphVertex> GetVertex(GraphVertex x) const;
    Option<GraphVertex*> SetVertex(GraphVertex x);
    /*
    bool AddVertex(GraphVertex x);
    bool RemoveVertex(GraphVertex x);
    bool AddEdge(const GraphVertex& x, const GraphVertex& y);
    bool RemoveEdge(const GraphVertex& x, const GraphVertex& y);
    bool Adjacent(const GraphVertex& x, const GraphVertex& y);
    List<GraphVertex&> Neighbors(const GraphVertex& x);
    */

   private:
    isize_t m_size;
    Map<GraphVertex*, List<GraphEdge>> m_verticies;
    Map<GRAPH_VERTEX_KEY, GraphVertex*> m_keys_to_verticies;
};

Graph::Graph() {
    m_size = 0;
}

Graph::~Graph() {
}

Option<GraphVertex> Graph::GetVertex(GraphVertex x) const {
    Option<GraphVertex> result;
    Option<GraphVertex*> vert = m_keys_to_verticies[x.key];

    result.result = Option<GraphVertex>::None;

    if (vert.result == Option<GraphVertex*>::Some) {
        result.result = Option<GraphVertex>::Some;
        result.value = *vert.value;
    }

    return result;
}

Option<GraphVertex*> Graph::SetVertex(GraphVertex x) {
    return m_keys_to_verticies[x.key];
}

/*
bool Graph::AddVertex(GraphVertex x) {
    //m_verticies.Insert(new GraphVertex(x), List<GraphEdge>());
    //m_keys_to_verticies.Insert(x.key, new GraphVertex(x));
    return false;
}

bool Graph::RemoveVertex(GraphVertex x) {
    return false;
}

bool Graph::AddEdge(const GraphVertex& x, const GraphVertex& y) {
    return false;
}

bool Graph::RemoveEdge(const GraphVertex& x, const GraphVertex& y) {
    return false;
}

bool Graph::Adjacent(const GraphVertex& x, const GraphVertex& y) {
    return false;
}

List<GraphVertex&> Graph::Neighbors(const GraphVertex& x) {
}
*/

}  // namespace containers
}  // namespace anvil
