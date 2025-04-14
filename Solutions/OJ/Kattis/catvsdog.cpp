#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
We can transform this problem into a maximum independent set problem on a bipartite graph which is equivalent to the complement of the minimum vertex cover problem. 
We create a node for each voter and as the sets of voters that conflict is bipartite, we can form a bipartite graph. Then, create an edge between the 2 vertices if they have a conflicting interest. 
Then run cover algorithm. 
*/

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

void solve() {
    
    int c, d, v; cin >> c >> d >> v;
    vector<array<int,2>> lhs, rhs;
    for(int i = 0; i < v; i++) {
        string a, b; cin >> a >> b;
        int na = stoi(a.substr(1)), nb = stoi(b.substr(1));
        if(a[0] == 'C') {
            lhs.push_back({na, nb});
        } else {
            swap(na, nb);
            rhs.push_back({na, nb});
        }
    }

    vector<vector<int>> g(v);
    for(int i = 0; i < lhs.size(); i++) {
        for(int j = 0; j < rhs.size(); j++) {
            if(lhs[i][0] == rhs[j][0] || lhs[i][1] == rhs[j][1]) {
                g[i].push_back(j);
            }
        }
    }

    vector<int> cov = cover(g, lhs.size(), rhs.size());

    cout << v - cov.size() << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}