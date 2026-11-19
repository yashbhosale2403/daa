#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

struct Node {
    vector<vector<long long>> reduced;
    long long cost;
    int vertex;
    int level;
    vector<int> path;
};

// Reduce rows and return the reduction cost
long long reduce_rows(vector<vector<long long>>& mat) {
    int n = (int)mat.size();
    long long reduction = 0;

    for (int i = 0; i < n; ++i) {
        long long row_min = INF;

        for (int j = 0; j < n; ++j) {
            row_min = min(row_min, mat[i][j]);
        }

        if (row_min == INF || row_min == 0) continue;

        reduction += row_min;

        for (int j = 0; j < n; ++j) {
            if (mat[i][j] < INF) mat[i][j] -= row_min;
        }
    }

    return reduction;
}

// Reduce columns and return the reduction cost
long long reduce_cols(vector<vector<long long>>& mat) {
    int n = (int)mat.size();
    long long reduction = 0;

    for (int j = 0; j < n; ++j) {
        long long col_min = INF;

        for (int i = 0; i < n; ++i) {
            col_min = min(col_min, mat[i][j]);
        }

        if (col_min == INF || col_min == 0) continue;

        reduction += col_min;

        for (int i = 0; i < n; ++i) {
            if (mat[i][j] < INF) mat[i][j] -= col_min;
        }
    }

    return reduction;
}

// Create a child node for travelling from 'from' to 'to'
Node create_child(const Node& parent,
                  int from, int to, int start,
                  long long edge_cost) {
    Node child;
    child.reduced = parent.reduced;
    child.level = parent.level + 1;
    child.vertex = to;
    child.path = parent.path;
    child.path.push_back(to);

    // Remove the selected row and column
    for (int i = 0; i < (int)child.reduced.size(); ++i) {
        child.reduced[from][i] = INF;
        child.reduced[i][to] = INF;
    }

    // Prevent returning to the start before visiting every vertex
    child.reduced[to][start] = INF;

    long long row_reduction = reduce_rows(child.reduced);
    long long col_reduction = reduce_cols(child.reduced);

    child.cost = parent.cost + edge_cost
               + row_reduction + col_reduction;

    return child;
}

// Comparator for the priority queue (lowest bound first)
struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.cost > b.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of cities: ";
    if (!(cin >> n) || n < 2) {
        cout << "Invalid number of cities.\n";
        return 0;
    }

    vector<vector<long long>> cost(n, vector<long long>(n));
    cout << "Enter the cost matrix (-1 for no edge):\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long x;
            cin >> x;

            if (i == j || x == -1) {
                cost[i][j] = INF;
            } else if (x < -1) {
                cout << "Invalid edge cost. Use -1 or a non-negative cost.\n";
                return 0;
            } else {
                cost[i][j] = x;
            }
        }
    }

    // Initial node: start from city 0
    Node root;
    root.reduced = cost;
    root.cost = 0;
    root.vertex = 0;
    root.level = 0;
    root.path = {0};

    long long row_reduction = reduce_rows(root.reduced);
    long long col_reduction = reduce_cols(root.reduced);
    root.cost = row_reduction + col_reduction;

    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(root);

    long long best_cost = INF;
    vector<int> best_path;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // Prune nodes whose lower bound is not better
        if (current.cost >= best_cost) continue;

        // All cities visited: return to the starting city
        if (current.level == n - 1) {
            int last = current.vertex;
            long long back_cost = cost[last][0];

            if (back_cost < INF) {
                long long total = current.cost + back_cost;

                if (total < best_cost) {
                    best_cost = total;
                    best_path = current.path;
                    best_path.push_back(0);
                }
            }
            continue;
        }

        int from = current.vertex;

        // Expand feasible next cities
        for (int to = 0; to < n; ++to) {
            long long edge_cost = current.reduced[from][to];

            if (edge_cost >= INF) continue;

            Node child = create_child(current, from, to, 0, edge_cost);

            if (child.cost < best_cost) {
                pq.push(child);
            }
        }
    }

    if (best_cost == INF) {
        cout << "No Hamiltonian cycle (tour) exists.\n";
    } else {
        cout << "Minimum tour cost: " << best_cost << "\n";
        cout << "Tour: ";

        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i];
            if (i + 1 < best_path.size()) cout << " -> ";
        }
        cout << "\n";
    }

    return 0;
}
