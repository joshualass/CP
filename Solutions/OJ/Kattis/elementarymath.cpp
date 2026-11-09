#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $r$ should be a vector full of
 * $-1$'s of the same size as the right partition. Returns the size of
 * the matching. $r[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
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

    int n; cin >> n;
    map<ll, vector<int>> m;
    vector<array<ll,2>> ar(n);
    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        ar[i] = {a, b};
        m[a + b].push_back(i);
        m[a - b].push_back(i);
        m[a * b].push_back(i);
    }

    map<ll,ll> cm, rcm;
    int p = 0;
    for(auto [k, v] : m) {
        cm[k] = p;
        rcm[p] = k;
        p++;
    }

    vector<vector<int>> g(n);
    vector<int> r(sz(cm), -1);
    for(int i = 0; i < n; i++) {
        auto [a, b] = ar[i];
        g[i].push_back(cm[a + b]);
        g[i].push_back(cm[a - b]);
        g[i].push_back(cm[a * b]);
    }

    int flow = hopcroftKarp(g, r); 
    // cout << "flow : " << flow << endl;
    
    if(flow == n) {
        vector<char> res(n);
        vector<ll> c(n);
        for(int i = 0; i < sz(r); i++) {
            if(r[i] != -1) {
                int p = r[i];
                auto [a, b] = ar[p];
                c[p] = rcm[i];
                if(a + b == rcm[i]) {
                    res[p] = '+';
                } else if(a * b == rcm[i]) {
                    res[p] = '*';
                } else if(a - b == rcm[i]) {
                    res[p] = '-';
                } else {
                    assert(0);
                }
            }
        }
        for(int i = 0; i < n; i++) cout << ar[i][0] << " " << res[i] << " " << ar[i][1] << " = " << c[i] << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}
