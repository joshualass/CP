#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//constructor: MinCostFlow<int, int> mcmf(n)
//res  : mcmf.minCostMaxFlow(source, sink)
//trace: add one more instance "real" to class Edge to note if it is the original edge
//for (auto e: G[i]) (i, e.to, mcmf.getFlow(e)) = (u, v, cap)
 
// tested: https://open.kattis.com/problems/mincostmaxflow
template<typename flow_t = int, typename cost_t = int>
struct MinCostFlow {
    struct Edge {
        cost_t c;
        flow_t f;
        int to, rev;
        Edge(int _to, cost_t _c, flow_t _f, int _rev) : c(_c), f(_f), to(_to), rev(_rev) {}
    };
 
    int N;
    vector<vector<Edge> > G;
    // MinCostFlow(int _N, int _S, int _T) : N(_N), S(_S), T(_T), G(_N), eps(0) {}
    MinCostFlow(int _N): N(_N), G(_N), eps(0) {}
    void addEdge(int a, int b, flow_t cap, cost_t cost) {
        assert(cap >= 0);
        assert(a >= 0 && a < N && b >= 0 && b < N);
        if (a == b) { assert(cost >= 0); return; }
        cost *= N;
        eps = max(eps, abs(cost));
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size() - 1);
    }
 
    flow_t getFlow(Edge const &e) {
        return G[e.to][e.rev].f;
    }
 
    pair<flow_t, cost_t> minCostMaxFlow(int S, int T) {
        cost_t retCost = 0;
        for (int i = 0; i<N; ++i) {
            for (Edge &e : G[i]) {
                retCost += e.c*(e.f);
            }
        }
        //find max-flow
        flow_t retFlow = max_flow(S, T);
        h.assign(N, 0); ex.assign(N, 0);
        isq.assign(N, 0); cur.assign(N, 0);
        queue<int> q;
        for (; eps; eps >>= scale) {
            //refine
            fill(cur.begin(), cur.end(), 0);
            for (int i = 0; i < N; ++i) {
                for (auto &e : G[i]) {
                    if (h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
                }
            }
            for (int i = 0; i < N; ++i) {
                if (ex[i] > 0){
                    q.push(i);
                    isq[i] = 1;
                }
            }
            // make flow feasible
            while (!q.empty()) {
                int u = q.front(); q.pop();
                isq[u]=0;
                while (ex[u] > 0) {
                    if (cur[u] == G[u].size()) {
                        relabel(u);
                    }
                    for (unsigned int &i=cur[u], max_i = G[u].size(); i < max_i; ++i) {
                        Edge &e = G[u][i];
                        if (h[u] + e.c - h[e.to] < 0) {
                            push(e, ex[u]);
                            if (ex[e.to] > 0 && isq[e.to] == 0) {
                                q.push(e.to);
                                isq[e.to] = 1;
                            }
                            if (ex[u] == 0) break;
                        }
                    }
                }
            }
            if (eps > 1 && eps>>scale == 0) {
                eps = 1<<scale;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (Edge &e : G[i]) {
                retCost -= e.c*(e.f);
            }
        }
        return make_pair(retFlow, retCost / 2 / N);
    }
 
private:
    static constexpr cost_t INFCOST = numeric_limits<cost_t>::max()/2;
    static constexpr int scale = 2;
 
    cost_t eps;
    vector<unsigned int> isq, cur;
    vector<flow_t> ex;
    vector<cost_t> h;
    vector<vector<int> > hs;
    vector<int> co;
 
    void add_flow(Edge& e, flow_t f) {
        Edge &back = G[e.to][e.rev];
        if (!ex[e.to] && f) {
            hs[h[e.to]].push_back(e.to);
        }
        e.f -= f; ex[e.to] += f;
        back.f += f; ex[back.to] -= f;
    }
 
    void push(Edge &e, flow_t amt) {
        if (e.f < amt) amt = e.f;
        e.f -= amt; ex[e.to] += amt;
        G[e.to][e.rev].f += amt; ex[G[e.to][e.rev].to] -= amt;
    }
 
    void relabel(int vertex){
        cost_t newHeight = -INFCOST;
        for (unsigned int i = 0; i < G[vertex].size(); ++i){
            Edge const&e = G[vertex][i];
            if(e.f && newHeight < h[e.to] - e.c){
                newHeight = h[e.to] - e.c;
                cur[vertex] = i;
            }
        }
        h[vertex] = newHeight - eps;
    }
 
    flow_t max_flow(int S, int T) {
        ex.assign(N, 0);
        h.assign(N, 0); hs.resize(2*N);
        co.assign(2*N, 0); cur.assign(N, 0);
        h[S] = N;
        ex[T] = 1;
        co[0] = N-1;
        for (auto &e : G[S]) {
            add_flow(e, e.f);
        }
        if (hs[0].size()) {
            for (int hi = 0; hi>=0;) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ex[u] > 0) { // discharge u
                    if (cur[u] == G[u].size()) {
                        h[u] = 1e9;
                        for(unsigned int i = 0; i < G[u].size(); ++i) {
                            auto &e = G[u][i];
                            if (e.f && h[u] > h[e.to]+1) {
                                h[u] = h[e.to]+1, cur[u] = i;
                            }
                        }
                        if (++co[h[u]], !--co[hi] && hi < N) {
                            for (int i = 0; i < N; ++i) {
                                if (hi < h[i] && h[i] < N) {
                                    --co[h[i]];
                                    h[i] = N + 1;
                                }
                            }
                        }
                        hi = h[u];
                    } else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to]+1) {
                        add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
                    } else {
                        ++cur[u];
                    }
                }
                while (hi>=0 && hs[hi].empty()) {
                    --hi;
                }
            }
        }
        return -ex[S];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // int n, m; cin >> n >> m;
    // MinCostFlow mcmf(n * m * 3 + n + m + 2);
    // int s = n * m * 3 + n + m;
    // int t = n * m * 3 + n + m + 1;

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         int id = (i * m + j) * 3;
    //         mcmf.addEdge(s,id,1,0);
    //         int a; cin >> a;
    //         mcmf.addEdge(id,id+1,1,a);
    //         mcmf.addEdge(id,id+2,1,a ^ 1);
    //     }
    // }

    // for(int i = 0; i < n; i++) {
    //     int a; cin >> a;
    //     a = m - a;
    //     mcmf.addEdge(n*m*3+i,t,a,0);
    //     for(int j = 0; j < m; j++) {
    //         int id = (i * m + j) * 3;
    //         mcmf.addEdge(id+1,n*m*3+i,1,0);
    //     }
    // }

    // for(int j = 0; j < m; j++) {
    //     int a; cin >> a;
    //     mcmf.addEdge(n*m*3+n+j,t,a,0);
    //     for(int i = 0; i < n; i++) {
    //         int id = (i * m + j) * 3;
    //         mcmf.addEdge(id+2,n*m*3+n+j,1,0);
    //     }
    // }

    // pair<int,int> res = mcmf.minCostMaxFlow(s,t);

    // if(res.first == n * m) {
    //     cout << res.second << '\n';
    // } else {
    //     cout << "-1\n";
    // }

    int n, m; cin >> n >> m;
    MinCostFlow mcmf(n + m + 2);
    int s = n + m, t = n + m + 1;
    vector<int> a(n), b(m);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x; cin >> x;
            sum += x;
            mcmf.addEdge(i, j + n, 1, x ^ 1);
        }
    }

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mcmf.addEdge(s, i, a[i], 0);
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
        mcmf.addEdge(i + n, t, b[i], 0);
    }

    pair<int,int> res = mcmf.minCostMaxFlow(s,t);
    if(res.first != reduce(a.begin(), a.end()) || res.first != reduce(b.begin(), b.end())) {
        cout << "-1\n";
    } else {
        cout << sum - res.first + res.second * 2 << '\n';
    }

    return 0;
}