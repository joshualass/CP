#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

#include <bits/extc++.h>
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
typedef pair<int, int> pii;
typedef vector<ll> VL;
const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}
    
	pair<ll, ll> maxflow(int s, int t, ll max_flow = INF) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t] && totflow < max_flow) {
			ll fl = max_flow - totflow;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int source) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[source] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector a(n,vector<int>(m)), b(n,vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> b[i][j];
            if((i == 0 || i == n - 1) && b[i][j]) b[i][j]--;
            if((j == 0 || j == m - 1) && b[i][j]) b[i][j]--; 
        }
    }

    vector<vector<int>> vid(n,vector<int>(m-1)), hid(n-1,vector<int>(m)), nid(n,vector<int>(m));

    int idp = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m - 1; j++) {
            vid[i][j] = idp++;
        }
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < m; j++) {
            hid[i][j] = idp++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            nid[i][j] = idp++;
        }
    }

    int s = idp++;
    int t = idp++;
    int aux = idp++;

    MCMF mcmf(idp);

    

    MCMF mcmf(n * m + n * (m - 1) + m * (n - 1) + 3);
    int s = n * m + n * (m - 1) + m * (n - 1);
    int t = s + 1;
    int aux = t + 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int left = n * m + (i * (m - 1) + j - 1);
            int right = n * m + (i * (m - 1) + j);
            int down = n * m + n * (m - 1) + ((i - 1) * m + j);
            int up = n * m + n * (m - 1) + (i * m + j);
            int node = i * m + j;
            // cout << "left : " << left << " right : " << right << " up : " << up << " down : " << down << '\n';
            //edge from source to cell
            mcmf.addEdge(s,node,b[i][j],0);
            //add to left window
            if(j) mcmf.addEdge(node,left,1,0);
            //add to right window
            if(j != m - 1) mcmf.addEdge(node,right,1,0);
            //add down
            if(i) mcmf.addEdge(node,down,1,0);
            //add up
            if(i != n - 1) mcmf.addEdge(node,up,1,0);
        }
    }

    //L-R / vertical windows 
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < m; j++) {
            int window = n * m + (i * (m - 1) + j - 1);
            mcmf.addEdge(window,t,1,0);
            if(!(j == 0 || j == m)) {
                mcmf.addEdge(window,aux,1,a[i][j] * a[i][j-1]);
            }
        }
    }

    //U-D / horizontal windows
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int window = n * m + (n * (m - 1)) + ((i - 1) * m + j);
            mcmf.addEdge(window,t,1,0);
            if(!(i == 0 || i == n)) {
                mcmf.addEdge(window,aux,1,a[i][j] * a[i-1][j]);
            }
        }
    }

    mcmf.addEdge(aux,t,50*50*2,0);

    auto [f, c] = mcmf.maxflow(s,t);
    cout << c << '\n';

    return 0;
}
//https://meet.google.com/eto-yiwx-frm christian.lim@icpc.global

