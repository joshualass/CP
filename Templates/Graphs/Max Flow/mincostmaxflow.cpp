//3 different mcmf, have had situations where last mcmf is best

// //constructor: MinCostFlow<int, int> mcmf(n)
// //res  : mcmf.minCostMaxFlow(source, sink)
// //trace: add one more instance "real" to class Edge to note if it is the original edge
// //for (auto e: G[i]) (i, e.to, mcmf.getFlow(e)) = (u, v, cap)
 
// // tested: https://open.kattis.com/problems/mincostmaxflow
// template<typename flow_t = int, typename cost_t = int>
// struct MinCostFlow {
//     struct Edge {
//         cost_t c;
//         flow_t f;
//         int to, rev;
//         Edge(int _to, cost_t _c, flow_t _f, int _rev) : c(_c), f(_f), to(_to), rev(_rev) {}
//     };
 
//     int N;
//     vector<vector<Edge> > G;
//     // MinCostFlow(int _N, int _S, int _T) : N(_N), S(_S), T(_T), G(_N), eps(0) {}
//     MinCostFlow(int _N): N(_N), G(_N), eps(0) {}
//     void addEdge(int a, int b, flow_t cap, cost_t cost) {
//         assert(cap >= 0);
//         assert(a >= 0 && a < N && b >= 0 && b < N);
//         if (a == b) { assert(cost >= 0); return; }
//         cost *= N;
//         eps = max(eps, abs(cost));
//         G[a].emplace_back(b, cost, cap, G[b].size());
//         G[b].emplace_back(a, -cost, 0, G[a].size() - 1);
//     }
 
//     flow_t getFlow(Edge const &e) {
//         return G[e.to][e.rev].f;
//     }
 
//     pair<flow_t, cost_t> minCostMaxFlow(int S, int T) {
//         cost_t retCost = 0;
//         for (int i = 0; i<N; ++i) {
//             for (Edge &e : G[i]) {
//                 retCost += e.c*(e.f);
//             }
//         }
//         //find max-flow
//         flow_t retFlow = max_flow(S, T);
//         h.assign(N, 0); ex.assign(N, 0);
//         isq.assign(N, 0); cur.assign(N, 0);
//         queue<int> q;
//         for (; eps; eps >>= scale) {
//             //refine
//             fill(cur.begin(), cur.end(), 0);
//             for (int i = 0; i < N; ++i) {
//                 for (auto &e : G[i]) {
//                     if (h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
//                 }
//             }
//             for (int i = 0; i < N; ++i) {
//                 if (ex[i] > 0){
//                     q.push(i);
//                     isq[i] = 1;
//                 }
//             }
//             // make flow feasible
//             while (!q.empty()) {
//                 int u = q.front(); q.pop();
//                 isq[u]=0;
//                 while (ex[u] > 0) {
//                     if (cur[u] == G[u].size()) {
//                         relabel(u);
//                     }
//                     for (unsigned int &i=cur[u], max_i = G[u].size(); i < max_i; ++i) {
//                         Edge &e = G[u][i];
//                         if (h[u] + e.c - h[e.to] < 0) {
//                             push(e, ex[u]);
//                             if (ex[e.to] > 0 && isq[e.to] == 0) {
//                                 q.push(e.to);
//                                 isq[e.to] = 1;
//                             }
//                             if (ex[u] == 0) break;
//                         }
//                     }
//                 }
//             }
//             if (eps > 1 && eps>>scale == 0) {
//                 eps = 1<<scale;
//             }
//         }
//         for (int i = 0; i < N; ++i) {
//             for (Edge &e : G[i]) {
//                 retCost -= e.c*(e.f);
//             }
//         }
//         return make_pair(retFlow, retCost / 2 / N);
//     }
 
// private:
//     static constexpr cost_t INFCOST = numeric_limits<cost_t>::max()/2;
//     static constexpr int scale = 2;
 
//     cost_t eps;
//     vector<unsigned int> isq, cur;
//     vector<flow_t> ex;
//     vector<cost_t> h;
//     vector<vector<int> > hs;
//     vector<int> co;
 
//     void add_flow(Edge& e, flow_t f) {
//         Edge &back = G[e.to][e.rev];
//         if (!ex[e.to] && f) {
//             hs[h[e.to]].push_back(e.to);
//         }
//         e.f -= f; ex[e.to] += f;
//         back.f += f; ex[back.to] -= f;
//     }
 
//     void push(Edge &e, flow_t amt) {
//         if (e.f < amt) amt = e.f;
//         e.f -= amt; ex[e.to] += amt;
//         G[e.to][e.rev].f += amt; ex[G[e.to][e.rev].to] -= amt;
//     }
 
//     void relabel(int vertex){
//         cost_t newHeight = -INFCOST;
//         for (unsigned int i = 0; i < G[vertex].size(); ++i){
//             Edge const&e = G[vertex][i];
//             if(e.f && newHeight < h[e.to] - e.c){
//                 newHeight = h[e.to] - e.c;
//                 cur[vertex] = i;
//             }
//         }
//         h[vertex] = newHeight - eps;
//     }
 
//     flow_t max_flow(int S, int T) {
//         ex.assign(N, 0);
//         h.assign(N, 0); hs.resize(2*N);
//         co.assign(2*N, 0); cur.assign(N, 0);
//         h[S] = N;
//         ex[T] = 1;
//         co[0] = N-1;
//         for (auto &e : G[S]) {
//             add_flow(e, e.f);
//         }
//         if (hs[0].size()) {
//             for (int hi = 0; hi>=0;) {
//                 int u = hs[hi].back();
//                 hs[hi].pop_back();
//                 while (ex[u] > 0) { // discharge u
//                     if (cur[u] == G[u].size()) {
//                         h[u] = 1e9;
//                         for(unsigned int i = 0; i < G[u].size(); ++i) {
//                             auto &e = G[u][i];
//                             if (e.f && h[u] > h[e.to]+1) {
//                                 h[u] = h[e.to]+1, cur[u] = i;
//                             }
//                         }
//                         if (++co[h[u]], !--co[hi] && hi < N) {
//                             for (int i = 0; i < N; ++i) {
//                                 if (hi < h[i] && h[i] < N) {
//                                     --co[h[i]];
//                                     h[i] = N + 1;
//                                 }
//                             }
//                         }
//                         hi = h[u];
//                     } else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to]+1) {
//                         add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
//                     } else {
//                         ++cur[u];
//                     }
//                 }
//                 while (hi>=0 && hs[hi].empty()) {
//                     --hi;
//                 }
//             }
//         }
//         return -ex[S];
//     }
// };

/*
UCF Min Cost Max Flow
that was faster than the others in contest. 
*/

struct MCMF {
    const ll INF = LLONG_MAX >> 2;

    struct Edge {
        int v;
        ll cap, flow, cost;
    };

    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<pair<int, int>> par;
    vector<int> in_q;
    vector<ll> dist, pi;

    MCMF(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        int idx = edges.size();
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }

    bool find_path(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(in_q.begin(), in_q.end(), 0);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        in_q[s] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = 0;

            for (int idx : adj[cur]) {
                Edge& e = edges[idx];
                int nxt = e.v;
                ll cap = e.cap, fl = e.flow, wt = e.cost;
                ll nxtD = dist[cur] + wt;

                if (fl >= cap || nxtD >= dist[nxt]) continue;

                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};

                if (!in_q[nxt]) {
                    q.push(nxt);
                    in_q[nxt] = 1;
                }
            }
        }
        return dist[t] < INF;
    }

    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;

        while (find_path(s, t)) {
            for (int i = 0; i < n; i++) {
                pi[i] = min(pi[i] + dist[i], INF);
            }

            ll f = INF;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                f = min(f, edges[i].cap - edges[i].flow);
            }

            flow += f;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
            }
        }

        for (size_t i = 0; i < edges.size() / 2; i++) {
            cost += edges[i * 2].cost * edges[i * 2].flow;
        }

        return {flow, cost};
    }
};