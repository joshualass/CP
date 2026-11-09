#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<int> q;
    vector<int> cnts(n);
    for(int i = 0; i < n; i++) {
        cnts[i] = sz(adj[i]);
        if(cnts[i] < k) {
            q.push(i);
        }
    }

    vector<int> vis(n);

    while(!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 1;
        for(int c : adj[x]) {
            cnts[c]--;
            if(cnts[c] == k - 1) q.push(c);
        }
    }

    cout << (count(vis.begin(), vis.end(), 1) == n ? "NO" : "YES") << '\n';

    return 0;
}
