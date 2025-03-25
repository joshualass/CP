/*
Solution Idea
Considered dynamic programming approaches and max flow approaches. 
For the dp approaches, we would have to convert to a DAG, but it is still not easy, so we should consider max flow.
Considered a lot of normal max flow, mcmf, and flow with demand. 
We should give each node in the graph 2 nodes in the flow graph with a low and high node. and have a flow from low to high with capacity one 
to demonstrate the flow of a messenger. 
We should ultimately observe that the source should never have an edge to the low node, as this allows us to have extra messengers. 
Then, we need to maximize the number of cities visited by messengers with a copy. 
We can give a negative cost for satisfying a city, as to maximize the number, but we should also ensure that every city gets a messenger. 
Therefore, we give every low to high a -1 flow and the cities with no messengers, a large extra constant of -10000 as they are necessary for this to be possible. 
Then, we run MCMF. 
*/

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// //not in the range. 

// template<class T>
// pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>> graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;
//     vector<unordered_map<int,T>> trace(graph.size());

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
//     return {flow,trace};
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         trace[p][y] += inc;
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         trace[y][p] -= inc;
//         }
//     }
// }

// void solve() {
//     int n, m; cin >> n >> m;

//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<vector<int>> adj(n);
//     for(int i = 0; i < m; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         adj[a].push_back(b);
//     }

//     vector<unordered_map<int,int>> graph(n * 2 + 2);
//     int s = n * 2, t = n * 2 + 1;

//     for(int i = 0; i < n; i++) {
//         graph[s][i * 2 + 1] = a[i] + 1;
//         graph[i * 2][i * 2 + 1] = 200;
//         graph[i * 2][t] = 1;
//         for(int x : adj[i]) {
//             graph[i * 2 + 1][x * 2] = 200;
//         }
//     }

//     int messengers = 0;
//     while(1) {
//         auto [flow, trace] = edmondsKarp(graph, s, t);
//         // cout << "messengers : " << messengers << " flow : " << flow << '\n';
//         if(flow + messengers == n) break;
//         messengers++;
//         for(int i = 0; i < n; i++) {
//             if(trace[i][t] == 0) {
//                 graph[i * 2].erase(t);
//                 graph[s][i * 2 + 1] = a[i];
//                 break;
//             }
//         }
//     }

//     cout << messengers << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();    

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<class T>
// pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;
//     vector<unordered_map<int,T>> trace(graph.size());

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
//     return {flow,trace};
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         trace[p][y] += inc;
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         trace[y][p] -= inc;
//         }
//     }
// }

// pair<bool, vector<unordered_map<int,ll>>> flowdemand(vector<unordered_map<int,array<ll,2>>> &adj, int s, int t, ll w) {
    
//     int n = adj.size();
//     vector<ll> indemand(n), outdemand(n);
//     ll demand_sum = 0;

//     vector<unordered_map<int,ll>> graph(n + 2);

//     for(int i = 0; i < n; i++) {
//         for(auto [to, edge] : adj[i]) {
//             outdemand[i] += edge[1];
//             indemand[to] += edge[1];
//             graph[i][to] = edge[0] - edge[1];
//             demand_sum += edge[1];
//         }
//     }

//     int S = n, T = n + 1;
//     for(int i = 0; i < n; i++) {
//         if(outdemand[i]) {
//             graph[i][T] = outdemand[i];
//         }
//         if(indemand[i]) {
//             graph[S][i] = indemand[i];
//         }
//     }

//     graph[t][s] = w;
//     auto [flow, trace] = edmondsKarp(graph, S, T);
//     return {flow == demand_sum, trace};
// }

// ll minflowdemand(vector<unordered_map<int,array<ll,2>>> &adj, int s, int t) {
    
//     ll demand_sum = 0;
//     int n = adj.size();
//     for(int i = 0; i < n; i++) {
//         for(auto [to, edge] : adj[i]) {
//             demand_sum += edge[1];
//         }
//     }

//     ll l = 0, r = demand_sum + 1;
//     while(l != r) {
//         ll m = (l + r) / 2;
//         auto [poss, trace] = flowdemand(adj, s, t, m);
//         if(poss) {
//             r = m;
//         } else {
//             l = m + 1;
//         }
//     }

//     if(l == demand_sum + 1) return -1;
//     return l;
// }



// pair<vector<vector<int>>, vector<int>> compress_SCC(vector<vector<int>> &adj) {

// }

// void solve() {
    
//     int n, m; cin >> n >> m;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;





//     vector<unordered_map<int, array<ll,2>>> adj(n * 2 + 2);

//     int s = n * 2, t = n * 2 + 1;
    
//     for(int i = 0; i < n; i++) {
//         int l = i * 2, h = i * 2 + 1;
//         adj[s][l] = {1, 0};
//         adj[l][h] = {n * n, 1};
//         adj[h][t] = {n * n, 0};
//         adj[s][h] = {a[i], a[i]};
//     }

//     for(int i = 0; i < m; i++) {
//         int u, v; cin >> u >> v;
//         u--; v--;
//         adj[u * 2 + 1][v * 2] = {n * n, 0};
//     }

//     int mfd = minflowdemand(adj, s, t);

//     cout << mfd << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct Edge {
        int from, to, rev;
        ll cap, cost, flow;
    };

    int N;
    vector<vector<Edge>> adj;
    vector<int> seen;
    vector<ll> dist, potential;
    vector<Edge*> parent;

    MCMF(int nodes) : N(nodes), adj(nodes), seen(nodes), dist(nodes), potential(nodes), parent(nodes) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        adj[from].push_back({from, to, static_cast<int>(adj[to].size()), cap, cost, 0});
        adj[to].push_back({to, from, static_cast<int>(adj[from].size()) - 1, 0, -cost, 0});
    }

    void path(int source) {
        fill(seen.begin(), seen.end(), 0);
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;

        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (seen[u]) continue;
            seen[u] = 1;

            ll adjusted_dist = dist[u] + potential[u];

            for (Edge &e : adj[u]) {
                if (!seen[e.to] && e.cap > e.flow) {
                    ll new_dist = adjusted_dist + e.cost - potential[e.to];

                    if (new_dist < dist[e.to]) {
                        dist[e.to] = new_dist;
                        parent[e.to] = &e;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (dist[i] < INF) {
                potential[i] = min(potential[i] + dist[i], INF);
            }
        }
    }

    pair<ll, ll> maxflow(int source, int sink) {
        ll total_flow = 0, total_cost = 0;

        while (true) {
            path(source);
            if (!seen[sink]) break;

            ll flow = INF;
            for (Edge* e = parent[sink]; e; e = parent[e->from]) {
                flow = min(flow, e->cap - e->flow);
            }

            total_flow += flow;
            for (Edge* e = parent[sink]; e; e = parent[e->from]) {
                e->flow += flow;
                adj[e->to][e->rev].flow -= flow;
            }
        }

        for (int i = 0; i < N; ++i) {
            for (Edge &e : adj[i]) {
                total_cost += e.cost * e.flow;
            }
        }

        return {total_flow, total_cost / 2};
    }

    void setPotential(int source) {
        fill(potential.begin(), potential.end(), INF);
        potential[source] = 0;
        bool changed = true;
        int iterations = N;

        while (changed && iterations--) {
            changed = false;
            for (int i = 0; i < N; ++i) {
                if (potential[i] == INF) continue;
                for (Edge &e : adj[i]) {
                    if (e.cap && potential[i] + e.cost < potential[e.to]) {
                        potential[e.to] = potential[i] + e.cost;
                        changed = true;
                    }
                }
            }
        }

        assert(iterations >= 0); // Ensure no negative cost cycle exists
    }
};


void kdfs(int i, vector<vector<int>> &adj, vector<int> &order, vector<int> &vis) {
    vis[i] = 1;
    for(int x : adj[i]) {
        if(vis[x] == 0) {
            kdfs(x,adj,order,vis);
        }
    }
    order.push_back(i);
}

void sdfs(int i, vector<vector<int>> &adj, vector<int> &vis, vector<vector<int>> &sccs) {
    vis[i] = 2;
    sccs.back().push_back(i);
    for(int x : adj[i]) {
        if(vis[x] == 1) {
            sdfs(x,adj,vis,sccs);
        }
    }
}

vector<vector<int>> kosarajus(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> tp(n);
    for(int i = 0; i < n; i++) {
        for(int x : adj[i]) {
            tp[x].push_back(i);
        }
    }
    vector<int> order(n);
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            kdfs(i,adj,order,vis);
        }
    }
    reverse(order.begin(), order.end());
    vector<vector<int>> sccs;
    for(int i = 0; i < n; i++) {
        if(vis[order[i]] == 1) {
            sccs.push_back({});
            sdfs(order[i],tp,vis,sccs);
        }
    }
    return sccs;
}

pair<vector<vector<int>>, vector<int>> compress_SCC(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> a(n);

    vector<vector<int>> sccs = kosarajus(adj);

    vector<int> scc_id(n);
    for(int i = 0; i < sccs.size(); i++) {
        for(int x : sccs[i]) {
            scc_id[x] = i;
        }
    }

    vector<vector<int>> upd_adj(sccs.size());
    set<array<int,2>> edges;
    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) {
            int i_id = scc_id[i], to_id = scc_id[to];
            if(i_id != to_id && edges.count({i_id,to_id}) == 0) {
                upd_adj[i_id].push_back(to_id);
                edges.insert({i_id,to_id});
            }
        }
    }
    return {upd_adj, scc_id};
}

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    auto p = compress_SCC(adj);
    adj = p.first;
    vector<int> ids = p.second;

    vector<int> b(adj.size());
    for(int i = 0; i < n; i++) {
        b[ids[i]] += a[i];
    }

    int v = adj.size();

    MCMF mcmf(v * 2 + 2);
    int s = v * 2, t = v * 2 + 1;

    for(int i = 0; i < v; i++) {
        int l = i * 2, h = i * 2 + 1;

        mcmf.addEdge(l,h,1,-1 + (b[i] == 0 ? -10000 : 0));
        mcmf.addEdge(l,h,n * n,0);
        mcmf.addEdge(s,h,b[i],0);
        for(int to : adj[i]) {
            mcmf.addEdge(h,to*2,n * n,0);
        }
        mcmf.addEdge(h,t,n * n,0);
    }

    mcmf.setPotential(s);
    auto [flow, cost] = mcmf.maxflow(s,t);

    // cout << "flow : " << flow << '\n';
    int res = v + count(b.begin(), b.end(), 0) * 10000 + cost;
    if(res > 1000) {
        cout << "-1\n";
    } else {
        cout << res << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}