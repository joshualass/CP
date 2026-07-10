#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

bitset<1000> vis[100000];
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<array<int,2>> edges(m);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i] = {u, v};
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    vector<int> res(n);

    while(1) {
        shuffle(perm.begin(), perm.end(), rng);
        for(int i = 0; i < n; i++) vis[i].reset();
        int ok = 1;
        for(int x : perm) {
            int f = 0;
            for(int j = 0; j < 1000; j++) {
                if(vis[x][j] == 0) {
                    for(int to : adj[x]) {
                        vis[to][j] = 1;
                    }
                    f = 1;
                    res[x] = j;
                    break;
                }
            }
            if(f == 0) {
                ok = 0; 
                break;
            }
        }
        if(ok) {
            for(int i = 0; i < m; i++) {
                cout << res[edges[i][0]] - res[edges[i][1]] << '\n';
            }
            return 0;
        }
    }

    return 0;
}
