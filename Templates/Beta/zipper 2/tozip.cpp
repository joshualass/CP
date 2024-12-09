#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, cap, cost, flow, rev;
};

vector<vector<Edge>> adj;
vector<int> dist, pot, parent, edge_index;

void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, cap, cost, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, -cost, 0, (int)adj[u].size() - 1});
}

bool spfa(int s, int t, int &flow, int &cost) {
    dist.assign(adj.size(), INF);
    parent.assign(adj.size(), -1);
    edge_index.assign(adj.size(), -1);
    vector<bool> in_queue(adj.size(), false);
    queue<int> q;

    dist[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int i = 0; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost + pot[u] - pot[e.to]) {
                dist[e.to] = dist[u] + e.cost + pot[u] - pot[e.to];
                parent[e.to] = u;
                edge_index[e.to] = i;
                if (!in_queue[e.to]) {
                    q.push(e.to);
                    in_queue[e.to] = true;
                }
            }
        }
    }

    if (dist[t] == INF) return false;

    for (int i = 0; i < adj.size(); ++i) {
        if (dist[i] != INF) pot[i] += dist[i];
    }

    int push = INF;
    for (int v = t; v != s; v = parent[v]) {
        int u = parent[v], idx = edge_index[v];
        push = min(push, adj[u][idx].cap - adj[u][idx].flow);
    }

    for (int v = t; v != s; v = parent[v]) {
        int u = parent[v], idx = edge_index[v];
        adj[u][idx].flow += push;
        adj[v][adj[u][idx].rev].flow -= push;
    }

    flow += push;
    cost += push * pot[t];
    return true;
}


int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c[i][j];
        }
    }

    int max_flow = 0;
    int l = 0, r = 2000000; // Adjusted range for binary search

    while (l <= r) {
        int mid = l + (r - l) / 2;
        adj.assign(n + 2, vector<Edge>());
        int s = n, t = n + 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (c[i][j] > 0) {
                    add_edge(i, j, c[i][j], 0);
                    add_edge(i, j, k, 1); // Capacity k for augmenting paths
                }
            }
        }
        add_edge(s, 0, mid, 0);
        add_edge(n - 1, t, mid, 0);

        int flow = 0, cost = 0;
        pot.assign(n + 2, 0);
        while (spfa(s, t, flow, cost));

        if (flow == mid && cost <= k) {
            max_flow = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << max_flow << endl;

    return 0;
}