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
    vector<array<ld,2>> a(n), b(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;

    vector<vector<ld>> d(n, vector<ld>(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        d[i][j] = sqrtl((a[i][0] - b[j][0]) * (a[i][0] - b[j][0]) + (a[i][1] - b[j][1]) * (a[i][1] - b[j][1]));
    }

    ld l = 0, r = 64;

    while(r - l > 1e-9) {
        ld m = (l + r) / 2;
        // cout << "m : " << m << endl;
        vector<vector<int>> g(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(d[i][j] <= powl(2, m)) g[i].push_back(j);
            }
        }
        vector<int> btoa(n, -1);
        if(dfsMatching(g, btoa) == n) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << fixed << setprecision(10) << powl(2, l) << '\n';

    return 0;
}
