#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c; cin >> n >> m >> c;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n, 0);
    map<int,int> singles;
    vector<set<int>> b;

    auto dfs = [&](auto self, int i, set<int> &s) -> void {
        if(vis[i]) return;
        vis[i] = 1;
        s.insert(a[i]);
        for(int x : adj[i]) self(self, x, s);
    };

    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            set<int> s;
            dfs(dfs, i, s);
            if(s.size() == 1) {
                singles[a[i]]++;
            } else {
                b.push_back(s);
            }
        }
    }

    if(singles.size()) {
        if(singles.size() > 1) {
            cout << "-1\n";
            return 0;
        }
        int color = singles.begin()->first;
        int ok = 1;
        for(set<int> s : b) if(s.count(color) == 0) ok = 0;
        cout << (ok ? (int) b.size() : -1) << '\n';
    } else {
        set<int> t = b[0];
        for(int i = 1; i < b.size(); i++) {
            for(set<int>::iterator it = t.begin(); it != t.end();) {
                if(b[i].count(*it) == 0) {
                    it = t.erase(it);
                } else {
                    it++;
                }
            }
        }
        cout << (t.size() ? (int) b.size() : -1) << '\n';
    }

    return 0;
}
