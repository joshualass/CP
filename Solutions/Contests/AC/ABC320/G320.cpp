#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

//ok should continue to optimize for all cases. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector reels(n, vector<vector<int>>(10));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            reels[i][s[j] - '0'].push_back(j);
        }
    }

    int l = 0, r = 1e9;
    while(l != r) {
        int mid = (l + r) / 2;
        int f = 0;
        for(char i = 0; i <= 9; i++) {
            map<int,vector<int>> edges;
            for(int j = 0; j < n; j++) {
                if(reels[j][i].size()) {
                    for(int k = 0; k < (n + reels[j][i].size() - 1) / reels[j][i].size(); k++) {
                        for(int l = 0; l < reels[j][i].size() && k * reels[j][i].size() + l < n; l++) {
                            edges[k * m + reels[j][i][l]].push_back(j);
                        }
                    }
                }
            }
            vector<vector<int>> adj;
            vector<int> btoa(n,-1);
            for(auto [_, edge] : edges) {
                if(_ <= mid) {
                    adj.push_back(edge);
                }
            }
            int flow = hopcroftKarp(adj, btoa);
            if(flow == n) f = 1;
        }
        if(f) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << (l == 1e9 ? -1 : l) << '\n';

    return 0;
}