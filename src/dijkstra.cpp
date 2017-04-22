#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

void readGraph(Graph &graph, const char *fileName);
void printResults(Vertex *end);
void dijkstra(Graph &graph, Vertex *start);

int main(int argc, const char **argv) {
    // Basic argument validation
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input-graph-file-name> <u> <w>\n";
        exit(1);
    }

    // Read the graph
    Graph graph;
    readGraph(graph, argv[1]);

    // Check start & end
    Vertex *start = graph.get(argv[2]);
    Vertex *end = graph.get(argv[3]);

    if (start == nullptr) {
        cerr << "Error: start node '" << argv[2] << "' not in graph\n";
        exit(2);
    }

    if (end == nullptr) {
        cerr << "Error: end node '" << argv[3] << "' not in graph\n";
        exit(2);
    }

    // Determine distance for each vertex
    dijkstra(graph, start);

    // Print shortest path
    printResults(end);

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


/**
 * Print the total weight and then the path's names in order.
 */
void printResults(Vertex *end) {
    cout << end->label << '\n';

    // Build list starting from back
    vector<Vertex *> reversePath;
    reversePath.push_back(end);

    while (end->prev != nullptr) {
        end = end->prev;
        reversePath.push_back(end);
    }

    // Print from start to end
    for (vector<Vertex *>::reverse_iterator rit = reversePath.rbegin(); rit != reversePath.rend()-1; ++rit) {
        cout << (*rit)->getName() << " ";
    }
    cout << reversePath[0]->getName() << '\n';
}


/**
 * Preforms the Dijkstra algorithm on the graph to find the shortest path
 */
void dijkstra(Graph &graph, Vertex *start) {
    Vertex *v, *u;
    AdjacentEdge *edge;
    vector<AdjacentEdge *> adj;
    double newTotal;

    // Initialize start
    start->label = 0;

    // Initialize priority queue
    priority_queue<Vertex *> q;
    unordered_map<string, Vertex *> vertices = graph.getVertices();
    for (unordered_map<string, Vertex *>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        q.push((*it).second);
    }

    while (q.size() != 0) {
        // Extract next in queue
        v = q.top();
        q.pop();

        // Update neighbors
        adj = v->getAdjacencyList();
        for (vector<AdjacentEdge *>::iterator it = adj.begin(); it != adj.end(); ++it) {
            edge = *it;
            u = edge->vertex;

            if (u->final) {
                continue;
            }

            newTotal = v->label + edge->weight;
            if (u->label > newTotal) {
                // Relax the adj vertex
                u->label = newTotal;
                u->prev = v;

                // TODO update queue (Fib. heap)? Current method results in double checking b/c cannot remove
                q.push(u);
            }
        }

    }
}