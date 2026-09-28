#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int hopcroftKarp(vector<vi>& g, vi& r) {
	int n = sz(g), res = 0;
	vi l(n, -1), q(n), d(n);
	auto dfs = [&](auto f, int u) -> bool {
		int t = exchange(d[u], 0) + 1;
		for (int v : g[u])
			if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
				return l[u] = v, r[v] = u, 1;
		return 0;
	};
	for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
		rep(i,0,n) if (l[i] == -1) q[t++] = i, d[i] = 1;
		rep(i,0,t) for (int v : g[q[i]]) {
			if (r[v] == -1) f = 1;
			else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
		}
		if (!f) return res;
		rep(i,0,n) if (l[i] == -1) res += dfs(dfs, i);
	}
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> r(n, -1);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int flow = hopcroftKarp(g, r);

    cout << 1013 * (2 * n - flow) << '\n';

    return 0;
}
