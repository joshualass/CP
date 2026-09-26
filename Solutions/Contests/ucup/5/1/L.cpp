#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

void solve() {
    
    int n; cin >> n;
    vector<array<int,3>> a(n);
    vector<vector<int>> g(n), rtri(n);
	dsubuild(n);

    for(int i = 0; i < n; i++) {
        for(auto &x : a[i]) {
            cin >> x;
            x--;
            g[i].push_back(x);
			rtri[x].push_back(i);
        }
		for(int j = 0; j < 2; j++) {
			merge(a[i][j], a[i][j+1]);
		}
    }

	if(sizes[find(0)] != n) {
		cout << "NO\n";
		return;
	}

	vector<int> r(n, -1);
	int flow = hopcroftKarp(g, r);
	assert(flow == n);

	vector<set<int>> adj(n);
	dsubuild(n);

	vector<array<int,2>> res(n, {-1,-1});

	//process all but last
	queue<int> qp, qm;
	for(int i = 0; i < n; i++) {
		vector<int> p;
		for(int j = 0; j < 3; j++) {
			if(a[i][j] != r[i]) p.push_back(j);
		}
		if(i + 1 != n) {
			adj[p[0]].insert(p[1]);
			adj[p[1]].insert(p[0]);
			res[i] = {p[0], p[1]};
		} else {
			qm.push(p[0]);
		}
	}

	while(sz(qp) || sz(qm)) {
		if(sz(qm)) {
			int x = qm.front();
			qm.pop();
			qp.push(x);
			for(int y : adj[x]) {
				if(find(y) != find(x)) {
					merge(y, x);
					qm.push(y);
				}
			}
		} else {
			assert(sz(qp));
			int x = qp.front();
			qp.pop();
			int f = 0;
			for(int i = 0; i < 3; i++) {
				int tri = rtri[x][i];
				int ok = 1;
				for(int j = 0; j < 2; j++) {
					if(x == res[tri][j]) {
						ok = 0;
					}
				}
				if(ok) {
					auto [u, v] = res[tri];
					adj[u].erase(v);
					adj[v].erase(u);
					res[tri] = {x, u};
					adj[x].insert(u);
					adj[u].insert(x);
					f = 1;
					break;
				}
			}
			if(f) {
				qm.push(x);
			}
		}
	}

	cout << "YES\n";
	for(int i = 0; i < n; i++) {
		for(int x : adj[i]) cout << x + 1 << " ";
		cout << '\n';
	}

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}