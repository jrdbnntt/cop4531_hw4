/**
 * Graph implementation
 */
#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

ostream &operator<<(ostream &os, const Graph &graph) {
    for (unordered_map<string, Vertex *>::const_iterator it = graph.vertices.begin(); it != graph.vertices.end(); ++it) {
        os << *(it->second) << '\n';
    }
    return os;
}

Graph::~Graph() {
    // Cleanup vertices
    for (unordered_map<string, Vertex *>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
        delete it->second;
    }
}

Vertex *Graph::insertOrGet(string name) {
    Vertex *v = get(name);

    if (v == nullptr) {
        // Not found, create it
        v = new Vertex(name);
        vertices[name] = v;
    }

    return v;
}

const unordered_map<string, Vertex *>& Graph::getVertices() {
    return vertices;
}

Vertex * Graph::get(string name) {
    unordered_map<string, Vertex *>::const_iterator it = vertices.find(name);
    return it == vertices.end()? nullptr : it->second;
}
