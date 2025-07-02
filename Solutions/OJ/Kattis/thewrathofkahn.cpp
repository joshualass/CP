#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
Path cover is a set of paths in a graph such that each node of the graph belongs to at least one path.
node-disjoint is where each node belongs to exaclyt one path. the setup is just bipartite matching with a node on lhs and rhs and an edge if there is an edge present in graph
general path cover is where we can reuse a node in the paths, we add an edge from a to be if a can reach b. 

the minimum paths is n - flow. 

from dilworth's theorem, maximum antichain = minimum general path cover. 

*/

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n), g(n);

    vector<int> ind(n);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        ind[v]++;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(ind[i] == 0) q.push(i);
    }

    vector<int> good(n);

    while(q.size()) {
        int i = q.front();
        q.pop();
        good[i] = 1;
        for(int c : adj[i]) {
            ind[c]--;
            if(ind[c] == 0) q.push(c);
        }
    }

    auto dfs = [&](auto self, int i, int start, vector<int> &vis) -> void {
        for(int c : adj[i]) {
            if(vis[c] == 0 && good[c]) {
                vis[c] = 1;
                g[start].push_back(c);
                self(self, c, start, vis);
            }
        }
    };

    for(int i = 0; i < n; i++) {
        if(good[i]) {
            vector<int> vis(n);
            dfs(dfs, i, i, vis);
        }
    }

    vector<int> btoa(n, -1);

    int flow = hopcroftKarp(g, btoa);

    cout << n - flow - count(good.begin(), good.end(), 0) << '\n';

    return 0;
}
