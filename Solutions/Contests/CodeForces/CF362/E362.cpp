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



// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>

// using namespace std;

// const int INF = 1e9;

// struct Edge {
//     int to, cap, cost, flow, rev;
// };

// vector<vector<Edge>> adj;
// vector<int> dist, pot, p;

// void add_edge(int u, int v, int cap, int cost) {
//     adj[u].push_back({v, cap, cost, 0, (int)adj[v].size()});
//     adj[v].push_back({u, 0, -cost, 0, (int)adj[u].size() - 1});
// }

// bool spfa(int s, int t, int &flow, int &cost) {
//     dist.assign(adj.size(), INF);
//     p.assign(adj.size(), -1);
//     vector<bool> in_queue(adj.size(), false);
//     queue<int> q;

//     dist[s] = 0;
//     q.push(s);
//     in_queue[s] = true;

//     while (!q.empty()) {
//         int u = q.front();
//         q.pop();
//         in_queue[u] = false;

//         for (Edge &e : adj[u]) {
//             if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost + pot[u] - pot[e.to]) {
//                 dist[e.to] = dist[u] + e.cost + pot[u] - pot[e.to];
//                 p[e.to] = &e - &adj[u][0];
//                 if (!in_queue[e.to]) {
//                     q.push(e.to);
//                     in_queue[e.to] = true;
//                 }
//             }
//         }
//     }

//     if (dist[t] == INF) return false;

//     for (int i = 0; i < adj.size(); ++i) {
//         if (dist[i] != INF) pot[i] += dist[i];
//     }

//     int push = INF;
//     for (int v = t; v != s; v = adj[v][p[v]].to) {
//         push = min(push, adj[v][p[v]].rev);
//     }

//     for (int v = t; v != s; v = adj[v][p[v]].to) {
//         adj[adj[v][p[v]].to][adj[v][p[v]].rev].flow += push;
//         adj[v][p[v]].flow -= push;

//     }

//     flow += push;
//     cost += push * pot[t];
//     return true;
// }


// int main() {

//     cout << "ok1" << endl;
//     int n, k;
//     cin >> n >> k;

//     vector<vector<int>> c(n, vector<int>(n));
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             cin >> c[i][j];
//         }
//     }

//     cout << "ok2" << endl;

//     int initial_max_flow = 0;
    

//     int l = 0, r = 1000000000;
//     while(l <= r){
//         int mid = l + (r - l)/2;
//         cout << "mid : " << mid << endl;
//         adj.assign(n + 2, vector<Edge>());
//         int s = n, t = n + 1;
//         for(int i = 0; i < n; ++i){
//             for(int j = 0; j < n; ++j){
//                 if(c[i][j] > 0){
//                     add_edge(i, j, c[i][j], 0);
//                     add_edge(i, j, k, 1);
//                 }
//             }
//         }
//         add_edge(s, 0, mid, 0);
//         add_edge(n-1, t, mid, 0);

//         int flow = 0, cost = 0;
//         pot.assign(n + 2, 0);
//         cout << "start mcmf" << endl;
//         while (spfa(s, t, flow, cost));
//         cout << "end mcmf" << endl;
//         if(flow == mid && cost <= k) {
//             initial_max_flow = mid;
//             l = mid + 1;
//         } else {
//             r = mid - 1;
//         }
//     }

//     cout << initial_max_flow << endl;

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<class T>
// T edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;

//     for(;;) {
//         fill(par.begin(), par.end(), -1);
//         par[source] = 0;
//         int ptr = 1;
//         q[0] = source;

//         for(int i = 0; i < ptr; i++) {
//             int x = q[i];
//             for(auto e : graph[x]) {
//                 if(par[e.first] == -1 && e.second > 0) {
//                     par[e.first] = x;
//                     q[ptr++] = e.first;
//                     if(e.first == sink) goto out;
//                 }
//             }
//         }
//     return flow;
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         }
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     vector<vector<int>> pipes(n, vector<int>(n));
//     vector<unordered_map<int,int>> adj(n);

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             cin >> pipes[i][j];
//             adj[i][j] = pipes[i][j];
//         }
//     }

//     int flo = edmondsKarp(adj, 0, n - 1);

//     while(1) {
//         vector<int> p(n,-2);
//         vector<int> d(n,-1);
//         queue<array<int,3>> q1, q2;
//         q1.push({0,0,-1});
//         while(q1.size()) {
//             q2.push(q1.front());
//             q1.pop();
//             while(q2.size()) {
//                 auto [i, dist, par] = q2.front();
//                 q2.pop();
//                 if(p[i] != -2) continue;
//                 // cout << "i : " << i << '\n';
//                 p[i] = par;
//                 d[i] = dist;
//                 for(int j = 0; j < n; j++) {
//                     if(pipes[i][j]) {
//                         q1.push({j, dist + 1, i});
//                     }
//                 }
//                 for(auto [j, f] : adj[i]) {
//                     if(f) {
//                         q2.push({j, dist, i});
//                     }
//                 }
//             }
//         }
//         if(d[n-1] == -1 || d[n-1] > k) break;   

//         // cout << "last d : " << d[n-1] << '\n';

//         k -= d[n-1];
//         int c = n - 1;
//         while(c != 0) {
//             int par = p[c];
//             if(adj[par][c] == 0) {
//                 adj[par][c]++;
//             }
//             c = par;
//         }
//         flo += edmondsKarp(adj, 0, n - 1);
//     }

//     cout << flo << '\n';

//     return 0;
// }