#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<set<int>> adj(n);

    vector<int> a(k);
    for(int &x : a) {
        cin >> x;
        x--;    
    }

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<array<int,2>> res;

    if(adj[0].count(a[0]) == 0 && a[0]) {
        int u = 0, v = a[0];            
        adj[u].insert(v);
        adj[v].insert(u);
        res.push_back({u + 1, v + 1});        
    }

    for(int i = 1; i < k; i++) {
        if(adj[a[i]].count(a[i-1]) == 0) {
            int u = a[i], v = a[i-1];
            adj[u].insert(v);
            adj[v].insert(u);
            res.push_back({u + 1, v + 1});
        }
    }

    queue<array<int,2>> q;
    q.push({0,0});
    vector<int> d(n, -1);
    while(q.size()) {
        auto [i, dis] = q.front();
        q.pop();
        if(d[i] != -1) continue;
        d[i] = dis;
        for(int to : adj[i]) {
            q.push({to, dis + 1});
        }
    }

    int ok = 1;
    for(int i = 1; i < k; i++) {
        if(d[a[i-1]] >= d[a[i]]) ok = 0;
    }

    if(ok) {
        cout << res.size() << '\n';
        for(auto x : res) {
            for(auto y : x) cout << y << " ";
            cout << '\n';
        }
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}