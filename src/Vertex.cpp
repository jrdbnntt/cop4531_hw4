/**
 * Vertex implementation
 */

#include <vector>
#include "Vertex.h"

using namespace std;


ostream &operator<<(ostream &os, const AdjacentEdge &edge) {
    os << '[' <<edge.vertex->getName() << " " << edge.weight << ']';
    return os;
}

ostream& operator<<(ostream &os, const Vertex &vertex) {
    os << vertex.name << '\t';
    for (vector<AdjacentEdge *>::const_iterator it = vertex.adjacencyList.begin(); it != vertex.adjacencyList.end(); ++it) {
        os << "  " << **it;
    }
    return os;
}

bool Vertex::operator<(const Vertex *&v2) const {
    return label < v2->label;
}


Vertex::~Vertex() {
    // Clean up edges
    for (vector<AdjacentEdge *>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
        delete *it;
    }
}

void Vertex::addAdjacentEdge(Vertex *vertex, double weight) {
    AdjacentEdge *edge = new AdjacentEdge(vertex, weight);
    adjacencyList.push_back(edge);
}

const string& Vertex::getName() const {
    return name;
}

const vector<AdjacentEdge *>& Vertex::getAdjacencyList() const {
    return adjacencyList;
}




