#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool bridge;
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) {
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridge = true;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    bridge = false;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(true) {
        int c; cin >> n >> c;
        if(n == 0 && c == 0) {
            break;
        }
        adj.clear(); adj.resize(n);
        for(int i = 0; i < c; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        find_bridges();
        cout << (bridge ? "Yes" : "No") << "\n";
    }

    return 0;
}