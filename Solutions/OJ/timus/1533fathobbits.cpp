#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

4
0 1 1 1
0 0 1 0
0 0 0 0
0 0 0 0

4
0 0 0 0
1 0 0 0 
1 1 0 0
1 0 0 0

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = dfsMatching(g, match);
	vector<bool> lfound(n, true), seen(m);
	for (int it : match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n; 
    vector<vector<int>> adj(n), g(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            if(x) {
                adj[i].push_back(j);
            }
        }
    }

    auto dfs = [&](auto self, int i, int start, vector<int> &vis) -> void {
        for(int c : adj[i]) {
            if(vis[c] == 0) {
                vis[c] = 1;
                // cout << "add edge i : " << start << " j : " << c << '\n';
                g[start].push_back(c);
                self(self, c, start, vis);
            }
        }
    };

    for(int i = 0; i < n; i++) {
        vector<int> vis(n);
        dfs(dfs, i, i, vis);
    }

    vector<int> btoa(n, -1);
    vector<int> cov = cover(g, n, n);

    // cout << "cov : " << cov << '\n';
    
    set<int> bad;
    for(int x : cov) bad.insert(x % n);

    cout << n - bad.size() << '\n';

    for(int i = 0; i < n; i++) {
        if(bad.count(i) == 0) cout << i + 1 << " ";
    }

    cout << '\n';

    return 0;
}
