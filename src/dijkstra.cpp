#include <iostream>
#include <fstream>
#include <sstream>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

void readGraph(Graph &graph, const char *fileName);


int main(int argc, const char **argv) {
    // Basic argument validation
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input-graph-file-name> <u> <w>" << endl;
        exit(1);
    }

    // Read the graph
    Graph graph;
    readGraph(graph, argv[1]);
    cout << graph; // TODO remove

    return 0;
}

/**
 * Populates graph with vectors and edges from file
 */
void readGraph(Graph &graph, const char *fileName) {
    ifstream inFile;
    string line, name;
    istringstream in;
    int n;
    double weight;
    Vertex *v, *u;

    inFile.open(fileName);

    // Get n;
    getline(inFile, line);
    in = istringstream(line);
    in >> n;

    // Read each line, extract the vector labels, store rest of line that contains edges for later
    for (int i = 0; i < n; ++i) {
        getline(inFile, line);
        in = istringstream(line);

        // Get the vector
        in >> name;
        v = graph.insertOrGet(name);

        // Build adjacency list
        while (in >> name) {
            in >> weight;
            u = graph.insertOrGet(name);
            v->addAdjacentEdge(u, weight);
        }

    }

    inFile.close();
}
