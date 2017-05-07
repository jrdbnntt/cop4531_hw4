
#include <vector>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

#ifndef COP4531_HW4_VERTEX_H
#define COP4531_HW4_VERTEX_H

class Vertex;

struct AdjacentEdge {
    Vertex *vertex;
    double weight;

    friend ostream& operator<<(ostream& os, const AdjacentEdge &edge);

    AdjacentEdge(Vertex *v, double w) {
        vertex = v;
        weight = w;
    }

};

class Vertex {
public:
    /**
     * Prints the vertices like the input provides. This is for debugging purposes in order to validate that the input
     * was properly read.
     */
    friend ostream& operator<<(ostream& os, const Vertex &vertex);

    /**
     * Comparison for sorting. Uses the name.
     */
    bool operator<(const Vertex *&v2) const;

    Vertex(const string &name) : name(name), label(numeric_limits<double>::max()) {
        prev = nullptr;
        proxy = nullptr;
        final = false;
    }
    ~Vertex();

    void addAdjacentEdge(Vertex *vertex, double weight);

    const string& getName() const;
    const vector<AdjacentEdge *>& getAdjacencyList() const;

    // Weight tracking label, updated as the route is found
    double label;

    // Previous vertex for tracking shortest path. Null if origin or not visited
    Vertex *prev;

    // Pointer to valid proxy in the priority queue
    Vertex **proxy;

    bool final;

private:
    string name;
    vector<AdjacentEdge *> adjacencyList;
};


struct CompareVertexProxy {
    bool operator()(Vertex **v1, Vertex **v2) {
        return (*v1)->label > (*v2)->label;
    }
};


#endif //COP4531_HW4_VERTEX_H
