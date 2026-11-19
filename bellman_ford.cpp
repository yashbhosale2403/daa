#include <iostream>
using namespace std;

const long INF = 9999;
const int MAX_VERTICES = 10;
const int MAX_EDGES = 50;

struct Edge {
    int source;
    int destination;
    int weight;
};

bool bellmanFord(int numVertices, Edge edges[],
                 int numEdges, int startNode,
                 long long distances[]) {

    for (int i = 0; i < numVertices; ++i) {
        distances[i] = INF;
    }

    distances[startNode] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < numVertices - 1; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            int src = edges[j].source;
            int dest = edges[j].destination;
            int weight = edges[j].weight;

            if (distances[src] != INF &&
                distances[src] + weight < distances[dest]) {
                distances[dest] = distances[src] + weight;
            }
        }
    }

    // Check for a negative weight cycle
    for (int i = 0; i < numEdges; ++i) {
        int src = edges[i].source;
        int dest = edges[i].destination;
        int weight = edges[i].weight;

        if (distances[src] != INF &&
            distances[src] + weight < distances[dest]) {
            return false;
        }
    }

    return true;
}

int main() {
    int numVertices, numEdges;

    cout << "Enter the number of vertices (max "
         << MAX_VERTICES << "): ";
    cin >> numVertices;

    cout << "Enter the number of edges (max "
         << MAX_EDGES << "): ";
    cin >> numEdges;

    if (numVertices <= 0 || numVertices > MAX_VERTICES ||
        numEdges < 0 || numEdges > MAX_EDGES) {
        cout << "Invalid graph size. Please ensure 1 <= vertices <= "
             << MAX_VERTICES << " and 0 <= edges <= "
             << MAX_EDGES << "\n";
        return 1;
    }

    Edge edges[MAX_EDGES];
    long long distances[MAX_VERTICES];

    cout << "Enter source, destination, and weight for each edge "
         << "(0-indexed nodes):\n";

    for (int i = 0; i < numEdges; ++i) {
        cout << "Edge " << i + 1 << ": ";
        cin >> edges[i].source
            >> edges[i].destination
            >> edges[i].weight;

        if (edges[i].source < 0 ||
            edges[i].source >= numVertices ||
            edges[i].destination < 0 ||
            edges[i].destination >= numVertices) {
            cout << "Invalid node index for edge " << i + 1
                 << ". Nodes must be between 0 and "
                 << numVertices - 1 << "\n";
            return 1;
        }
    }

    int startNode;

    cout << "Enter the starting node: ";
    cin >> startNode;

    if (startNode < 0 || startNode >= numVertices) {
        cout << "Invalid starting node. Please enter a node between 0 and "
             << numVertices - 1 << "\n";
        return 1;
    }

    if (bellmanFord(numVertices, edges, numEdges,
                    startNode, distances)) {
        cout << "\nShortest distances from node "
             << startNode << ":\n";

        for (int i = 0; i < numVertices; ++i) {
            if (distances[i] == INF) {
                cout << "To node " << i << ": INF\n";
            } else {
                cout << "To node " << i << ": "
                     << distances[i] << "\n";
            }
        }
    } else {
        cout << "\nGraph contains a negative cycle. "
             << "Shortest paths cannot be determined.\n";
    }

    return 0;
}
