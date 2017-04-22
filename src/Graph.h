
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Vertex.h"

using namespace std;

#ifndef COP4531_HW4_GRAPH_H
#define COP4531_HW4_GRAPH_H

class Graph {
public:
    /**
     * Prints the vertices like the input provides. This is for debugging purposes in order to validate that the input
     * was properly read.
     */
    friend ostream& operator<<(ostream& os, const Graph &graph);

    ~Graph();

    /**
     * Searches the vertices for a vertex with a matching name. If found, it is returned. Otherwise a new one is
     * created and inserted before returning it.
     * @param name Name of the vertex to get
     * @return The vertex with that name
     */
    Vertex * insertOrGet(string name);

    /**
     * Searches the vertices for a vertex with a matching name. Will return nullptr if not found.
     */
    Vertex * get(string name);

    const unordered_map<string, Vertex *>& getVertices();

private:
    // Known vertices in the graph, sorted by name
    unordered_map<string, Vertex *> vertices;

};


#endif //COP4531_HW4_GRAPH_H
