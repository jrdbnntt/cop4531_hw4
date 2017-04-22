
#include <vector>
#include <string>
#include <iostream>

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
//    friend bool operator<(const Vertex &v1, const Vertex &v2);

    Vertex(string &name) : name(name), label(-1.0) {}
    ~Vertex();

    void addAdjacentEdge(Vertex *vertex, double weight);

    const string& getName();
    const vector<AdjacentEdge *>& getAdjacencyList() const;

private:
    string name;
    vector<AdjacentEdge *> adjacencyList;

    // Weight tracking label, updated as the route is found
    double label;
};


#endif //COP4531_HW4_VERTEX_H