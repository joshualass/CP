#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<array<int,2>> a(n);

    vector<vector<array<int,2>>> adj(n);

    for(int i = 0; i < m; i++) {
        int o, u, v; cin >> o >> u >> v;
        o--; u--; v--;
        a[u][o]++;
        a[v][o]++;
        adj[u].push_back({v, o});
        adj[v].push_back({u, o});
    }

    queue<int> q;
    vector<int> vis(n);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            if(a[i][j] == 0) q.push(i);
        }
    }
    
    int z = n;
    vector<int> res(n);

    while(sz(q)) {
        int x = q.front();
        q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        if(a[x][0] == 0) {
            res[x] = -z--;
        } else {
            res[x] = z--;
        }
        for(auto [to, o] : adj[x]) {
            a[to][o]--;
            for(int i = 0; i < 2; i++) {
                if(a[to][i] == 0) {
                    q.push(to);
                }
            }
        }
    }

    if(count(vis.begin(), vis.end(), 1) == n) {
        cout << "YES\n";
        for(int i = 0; i < n; i++) {
            cout << res[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}