
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <sstream>

using namespace std;

struct SimpleVertex;

struct SimpleEdge {
    double weight;
    SimpleVertex *vertex;

    friend ostream &operator<<(ostream &os, const SimpleEdge &edge);

    SimpleEdge(SimpleVertex *vertex, double weight) : vertex(vertex), weight(weight) {}
};

struct SimpleVertex {
    string name;
    vector<SimpleEdge*> edges;

    SimpleVertex(string &name) : name(name) {}
    ~SimpleVertex() {
        for (vector<SimpleEdge*>::iterator it = edges.begin(); it != edges.end(); ++it) {
            delete *it;
        }
    }

    friend ostream& operator<<(ostream &os, const SimpleVertex &vertex) {
        os << vertex.name << ' ';
        for (vector<SimpleEdge *>::const_iterator it = vertex.edges.begin(); it != vertex.edges.end(); ++it) {
            os << "  " << **it;
        }
        return os;
    }

};

double MAX_WEIGHT = 1000.0;

int randInt(int min, int max);
double randDouble(double min, double max);
char randChar();
string randString(int len);

int main(int argc, const char **argv) {
    int maxWordSize = atoi(argv[1]);
    int totalVertices = atoi(argv[2]);
    int maxEdgesPer = atoi(argv[3]);
    int totalEdges;

    int actualEdges = 0;

    vector<SimpleVertex*> graph;
    SimpleVertex *v, *u;
    SimpleEdge *edge, *edgeReverse;
    string name;

    srand((unsigned int) time(NULL));

    // Generate vertices
    for (int i = 0; i < totalVertices; ++i) {
        name = randString(randInt(1, maxWordSize));
        v = new SimpleVertex(name);
        graph.push_back(v);
    }

    // Randomly assign edges
    bool canAdd;
    for (int i = 0; i < totalVertices; ++i) {
        v = graph[i];
        totalEdges = randInt(1, maxEdgesPer);

        for (int j = 0; j < totalEdges; ++j) {
            // Get a non-existent edge
            do {
                canAdd = true;
                u = graph[randInt(0, (int) graph.size()-1)];

                if (u->edges.size() >= maxEdgesPer) {
                    canAdd = false;
                    continue;
                }

                for (vector<SimpleEdge *>::const_iterator it = v->edges.begin(); it != v->edges.end(); ++it) {
                    if ((*it)->vertex == u) {
                        canAdd = false;
                        break;
                    }
                }
            } while (!canAdd);

            // Add it to both
            edge = new SimpleEdge(u, randDouble(1.0, MAX_WEIGHT));
            v->edges.push_back(edge);
            edgeReverse = new SimpleEdge(v, edge->weight);
            u->edges.push_back(edgeReverse);

            actualEdges += 1;
        }
    }

    // Print
    cout << totalVertices << '\n';
    for (vector<SimpleVertex *>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        cout << **it << '\n';
    }

    printf("Total Vectors: %d\t\tTotal Edges %d\n", totalVertices, actualEdges);

    // Free
    for (vector<SimpleVertex*>::iterator it = graph.begin(); it != graph.end(); ++it) {
        delete *it;
    }

}


char randChar() {
    switch (randInt(1, 3)) {
        case 1: return (char) randInt('0', '9');
        case 2: return (char) randInt('A', 'Z');
        default: return (char) randInt('a', 'z');
    }
}

string randString(int len) {
    stringstream ss;
    for (int i = 0; i < len; ++i) {
        ss << randChar();
    }
    return ss.str();
}

ostream &operator<<(ostream &os, const SimpleEdge &edge) {
    os << edge.vertex->name << " " << edge.weight;
    return os;
}

int randInt(int min, int max) {
    return rand()%(max-min + 1) + min;
}
double randDouble(double min, double max) {
    double n = (double) rand() / RAND_MAX;
    return min + n * (max - min);
}
