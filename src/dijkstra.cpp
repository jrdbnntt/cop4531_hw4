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
 *
 * The main priority queue is contains proxy pointers which point to pointers that point to Vertices. This is to get
 * around the fact that the PQ cannot efficiently remove elements or rearrange itself once a Vertex's label has been
 * updated. Instead of removing it, I am swapping the real pointer out for a fake one with the same label value and
 * just push the real pointer with a new proxy, which should be placed in the correct order. When the proxy with the
 * fake pointer is retrieved, it is simply ignored and removed so that the queue can move on.
 *
 * To be honest I thought this was a ridiculous idea that I never thought I could get to work. But then it worked! :D
 */
void dijkstra(Graph &graph, Vertex *start) {
    Vertex **proxy;
    Vertex *v, *u, *f;
    AdjacentEdge *edge;
    vector<AdjacentEdge *> adj;
    double newTotal;

    // Initialize start
    start->label = 0;

    // Initialize proxy pointers to enable copy + insert (mimics priority queue deletion). 1:1 rel w/ vertex, null=old
    unordered_map<string, Vertex *> vertices = graph.getVertices();

    // Initialize priority queue with proxies
    priority_queue<Vertex **, vector<Vertex **>, CompareVertexProxy> q;

    for (unordered_map<string, Vertex *>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
        v = it->second;
        proxy = new Vertex*(v);
        v->proxy = proxy;
        q.push(proxy);
    }

    while (q.size() != 0) {
        // Extract next proxy in queue
        proxy = q.top();
        q.pop();
        v = *proxy;

        // Deallocate old proxy
        delete proxy;

        // Replaced with a fake?
        if (v->proxy == nullptr) {
            // Deallocate fake
            delete v;
            continue;
        }

        // Not a fake, update neighbors
        adj = v->getAdjacencyList();
        for (vector<AdjacentEdge *>::iterator it = adj.begin(); it != adj.end(); ++it) {
            edge = *it;
            u = edge->vertex;

            if (u->final) {
                // This adjacent vertex has already been calculated in a previous iteration
                continue;
            }

            newTotal = v->label + edge->weight;
            if (u->label > newTotal) {
                // Swap the vertex the proxy already in the queue has with a fake one to be ignored, but still has val
                f = new Vertex(u->getName());
                f->label = u->label;
                f->proxy = nullptr;
                *(u->proxy) = f;

                // Create a new proxy to push
                proxy = new Vertex*(u);
                u->proxy = proxy;

                // Relax the adj vertex
                u->label = newTotal;
                u->prev = v;

                // Push to queue
                q.push(proxy);
            }
        }

        v->final = true;
    }

}