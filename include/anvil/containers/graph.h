#pragma once
#include "anvil/containers/list.h"
#include "anvil/containers/map.h"
#include "anvil/option.h"
#include "anvil/pair.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

typedef i64_t GRAPH_VERTEX_KEY;

/*
template <typename T>
struct Hashable<Vertex> {
    static long Hash(Vertex vert) {
        return Hashable<GRAPH_VERTEX_KEY>::Hash(vert.key);
    }
};
*/

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

template <typename T>
struct Graph {
   public:
    struct Vertex {
        Vertex(){};
        Vertex(GRAPH_VERTEX_KEY key, T data) : key(key), data(data) {}
        ~Vertex() {}
        Vertex(const Vertex& v) {
            key = v.key;
            data = v.data;
        }
        Vertex& operator=(const Vertex& v) {
            key = v.key;
            data = v.data;
            return *this;
        }
        GRAPH_VERTEX_KEY key;
        T data;
    };
    struct Edge {
    };
    Graph() {
    }

    ~Graph() {
        m_verticies.Clear();
    }

    Option<Vertex> GetVertex(GRAPH_VERTEX_KEY key) const {
        Option<Vertex> v;
        Option<Pair<Vertex, List<Edge>>> item = m_verticies[key];
        if (item.result == Option<Pair<Vertex, List<Edge>>>::Some) {
            v.result = Option<Vertex>::Some;
            v.value = item.value.first;
        }

        return v;
    }

    bool AddVertex(Vertex x) {
        Pair<Vertex, List<Edge>> p;
        p.first = x;

        return m_verticies.Insert(x.key, p);
    }

    Option<Vertex> RemoveVertex(GRAPH_VERTEX_KEY key) {
        Option<Vertex> v;
        Option<Pair<Vertex, List<Edge>>> item = m_verticies.Remove(key);

        if (item.result == Option<Pair<Vertex, List<Edge>>>::Some) {
            v.result = Option<Vertex>::Some;
            v.value = item.value.first;
        }

        return v;
    }
    /*
    bool AddEdge(GRAPH_VERTEX_KEY x, GRAPH_VERTEX_KEY y) {
        Option<Pair<Vertex, List<Edge>>> item = m_verticies[x];
        if (item.result == Option<Pair<Vertex, List<Edge>>>::Some) {
            m_verticies[x].second.Insert(Edge());
        }

        return false;
    }
    */
    /*
    bool RemoveEdge(const Vertex& x, const Vertex& y);
    
    bool Adjacent(const Vertex& x, const Vertex& y) const;
    List<Vertex&> Neighbors(const Vertex& x);
    */

   private:
    Map<GRAPH_VERTEX_KEY, Pair<Vertex, List<Edge>>> m_verticies;
};

/*
bool Graph::AddEdge(const Vertex& x, const Vertex& y) {
    return false;
}

bool Graph::RemoveEdge(const Vertex& x, const Vertex& y) {
    return false;
}

bool Graph::Adjacent(const Vertex& x, const Vertex& y) {
    return false;
}

List<Vertex&> Graph::Neighbors(const Vertex& x) {
}
*/

}  // namespace containers
}  // namespace anvil
