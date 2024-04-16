#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

/*
this is the only version that works
*/
 
bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		// rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
        for(int i = 0; i < g.size(); i++) {
            if(A[i] == 0) {
                cur.push_back(i);
            }
        }
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
		// rep(a,0,sz(g))
		// 	res += dfs(a, 0, g, btoa, A, B);
        for(int i = 0; i < g.size(); i++) {
            res += dfs(i, 0, g, btoa, A, B);
        }
	}
}

//you're fixed at location 0, friends location is passed in. 
map<int, vector<int>> m;
bool check_valid(vector<int>& x, vector<int>& y, int circ, int loc, int n) {
    vector<vector<int>> g(n);
    vector<int> btoa(n,-1);
    for(int i = 0; i < n; i++) {
        int p0 = (loc + y[i]) % circ;
        int p1 = (loc + circ - y[i]) % circ;
        vector<int> locs = {p0, p1};
        bool found = 0;
        for(int j = 0; j < 2; j++){
            int pos = locs[j];
            if(m.find(pos) == m.end()) {
                continue;
            }
            for(int k = 0; k < m[pos].size(); k++){
                // c[y_node[m[pos][k]]].push_back({f_node[i], 1});
                // dinics.add_edge(y_node[m[pos][k]], f_node[i], 1);
                g[m[pos][k]].push_back(i);
                found = 1;
            }
        }
        if(!found) return 0;
    }
    return hopcroftKarp(g,btoa) == n;
}
 
int mirror(int x, int c) {
    bool odd = false;
    if(c % 2 == 1){
        odd = true;
        x *= 2;
        c *= 2;
    }
    if(x >= c / 2){
        x -= (x - (c / 2)) * 2;
    }
    else {
        x += ((c / 2) - x) * 2;
    }
    if(odd){
        x /= 2;
    }
    return x;
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, c;
    cin >> n >> c;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
        m[x[i]].push_back(i);
        m[c - x[i]].push_back(i);
    }
    int miny = 1e9;
    for(int i = 0; i < n; i++){
        cin >> y[i];
        miny = min(miny, y[i]);
    }
    // cout << "1 " << mirror(1, c) << "\n";
    set<int> works;
    int ptr = 0;
    for(int i = 0; i < n; i++){
        int p0 = (x[i] + miny) % c;
        int p1 = (x[i] + c - miny) % c;
        vector<int> t = {p0, p1};
        for(int j = 0; j < t.size(); j++){
            if(check_valid(x, y, c, t[j], n)) {
                works.insert(t[j]);
                works.insert(mirror(t[j], c) % c);
                // cout << "WORKS : " << t[j] << " " << mirror(t[j], c) << "\n";
            }
        }
    }
    cout << works.size() << "\n";
    
    return 0;
}