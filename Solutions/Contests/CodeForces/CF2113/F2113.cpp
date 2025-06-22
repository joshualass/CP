#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
1
3
1 3 3 
2 2 4
*/

void solve() {
    
    int n; cin >> n;
    vector<map<int,set<int>>> adj(n * 2);
    vector<int> a(n), b(n);
    for(auto &x : a) {
        cin >> x;
        x--;
    }
    for(auto &x : b) {
        cin >> x;
        x--;
    }

    for(int i = 0; i < n; i++) {
        adj[a[i]][b[i]].insert(i);
        adj[b[i]][a[i]].insert(i);
    }

    vector<int> vis(n * 2);

    auto dfs = [&](auto self, int i, int t) -> void {

        if(vis[i]) return;
        vis[i] = 1;

        while(adj[i].size()) {
            int to = adj[i].begin()->first;
            int edge_id = *adj[i][to].begin();

            if(t == 0) {
                a[edge_id] = i;
                b[edge_id] = to;
            } else {
                a[edge_id] = to;
                b[edge_id] = i;
            }


            adj[i][to].erase(edge_id);
            adj[to][i].erase(edge_id);
            if(adj[i][to].empty()) {
                adj[i].erase(to);
                adj[to].erase(i);
            }

            self(self, to, t);

            t ^= 1;

        }

    };

    for(int i = 0; i < n; i++) dfs(dfs, i, 0);
    set<int> as(a.begin(), a.end()), bs(b.begin(), b.end());
    cout << as.size() + bs.size() << '\n';
    for(int i = 0; i < n; i++) cout << a[i] + 1 << " \n"[i == n - 1];
    for(int i = 0; i < n; i++) cout << b[i] + 1 << " \n"[i == n - 1];


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// #define rep(i, a, b) for(int i = a; i < (b); ++i)
// #define all(x) begin(x), end(x)
// #define sz(x) (int)(x).size()
// typedef long long ll;
// typedef pair<int, int> pii;
// typedef vector<int> vi;

// bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
// 	if (A[a] != L) return 0;
// 	A[a] = -1;
// 	for (int b : g[a]) if (B[b] == L + 1) {
// 		B[b] = 0;
// 		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
// 			return btoa[b] = a, 1;
// 	}
// 	return 0;
// }

// int hopcroftKarp(vector<vi>& g, vi& btoa) {
// 	int res = 0;
// 	vi A(g.size()), B(btoa.size()), cur, next;
// 	for (;;) {
// 		fill(all(A), 0);
// 		fill(all(B), 0);
// 		/// Find the starting nodes for BFS (i.e. layer 0).
// 		cur.clear();
// 		for (int a : btoa) if(a != -1) A[a] = -1;
// 		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
// 		/// Find all layers using bfs.
// 		for (int lay = 1;; lay++) {
// 			bool islast = 0;
// 			next.clear();
// 			for (int a : cur) for (int b : g[a]) {
// 				if (btoa[b] == -1) {
// 					B[b] = lay;
// 					islast = 1;
// 				}
// 				else if (btoa[b] != a && !B[b]) {
// 					B[b] = lay;
// 					next.push_back(btoa[b]);
// 				}
// 			}
// 			if (islast) break;
// 			if (next.empty()) return res;
// 			for (int a : next) A[a] = lay;
// 			cur.swap(next);
// 		}
// 		/// Use DFS to scan for augmenting paths.
// 		rep(a,0,sz(g))
// 			res += dfs(a, 0, g, btoa, A, B);
// 	}
// }

// void solve() {
    
//     int n; cin >> n;

//     vector<int> a(n), b(n);
//     map<int,int> m;

//     for(int &x : a) {
//         cin >> x;
//         x--;
//     }

//     for(int &x : b) {
//         cin >> x;
//         x--;
//     }

//     vector<vector<int>> g(n);
//     for(int i = 0; i < n; i++) {
//         g[i].push_back(a[i]);
//         g[i].push_back(b[i]);
//     }

//     vector<int> btoa(n * 2, -1);

//     // for(int i = 0; i < n; i++) cout << "i : " << i << " g[i] : " << g[i] << '\n';

//     int match = hopcroftKarp(g, btoa);

//     // cout << "match : " << match << '\n';
//     cout << "btoa : " << btoa << '\n';

//     // for(int i = 0; i < n * 2; i++) {
//     //     if(btoa[i] != -1) {
//     //         if(a[btoa[i]] != i) {
//     //             swap(a[btoa[i]], b[btoa[i]]);
//     //         }
//     //     }
//     // }

//     for(int i = 0; i < n; i++) {
//         if(btoa[a[i]] != -1 && btoa[a[i]] != i) swap(a[i], b[i]);
//         if(btoa[b[i]] != -1 && btoa[b[i]] == i) swap(a[i], b[i]);
//     }

//     set<int> as(a.begin(), a.end()), bs(b.begin(), b.end());

//     cout << as.size() + bs.size() << '\n';
//     for(int i = 0; i < n; i++) {
//         cout << a[i] + 1 << " \n"[i == n - 1];
//     }

//     for(int i = 0; i < n; i++) {
//         cout << b[i] + 1 << " \n"[i == n - 1];
//     }

//     // int res = 0;
//     // set<int> as, bs;
//     // for(int i = 0; i < n; i++) {
//     //     if(c[i] )
//     // }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }