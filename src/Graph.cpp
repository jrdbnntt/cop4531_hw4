/**
 * Graph implementation
 */
#include <vector>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

ostream &operator<<(ostream &os, const Graph &graph) {
    for (vector<Vertex *>::const_iterator it = graph.vertices.begin(); it != graph.vertices.end(); ++it) {
        os << **it << '\n';
    }
    return os;
}

Graph::~Graph() {
    // Cleanup vertices
    for (vector<Vertex *>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        delete *it;
    }
}

Vertex *Graph::insertOrGet(string name) {
    // TODO make this actually sorted
    Vertex *v = nullptr;
    Vertex *u;

    // Find it if exists
    for (vector<Vertex *>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        u = *it;
        if (u->getName() == name) {
            v = u;
            break;
        }
    }

    if (v == nullptr) {
        // Not found, create it
        v = new Vertex(name);
        vertices.push_back(v);
    }

    return v;
}

const vector<Vertex *>& Graph::getVertices() {
    return vertices;
}
