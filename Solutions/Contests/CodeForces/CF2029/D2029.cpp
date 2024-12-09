#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    vector<set<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<array<int,3>> ops;

    auto done = [&]() -> void {
        cout << ops.size() << '\n';
        for(auto op : ops) {
            cout << op[0] + 1 << " " << op[1] + 1 << " " << op[2] + 1 << '\n';
        }
        return;
    };

    auto toggle = [&](int a, int b, int c) -> void {
        ops.push_back({a,b,c});
        auto toggle_edge = [&](int d, int e) -> void  {
            if(adj[d].count(e)) {
                adj[d].erase(e);
                adj[e].erase(d);
            } else {
                adj[d].insert(e);
                adj[e].insert(d);
            }
        };
        toggle_edge(a,b);
        toggle_edge(c,b);
        toggle_edge(a,c);
    };

    queue<int> q;
    for(int i = 0; i < n; i++) {
        q.push(i);
    }
    while(q.size()) {
        int i = q.front();
        q.pop();
        while(adj[i].size() >= 2) {
            int b = *adj[i].begin();
            int c = *++adj[i].begin();
            toggle(i,b,c);
            q.push(b);
            q.push(c);
        }
    }

    int find_idx = -1;
    for(int i = 0; i < n; i++) {
        if(adj[i].size()) {
            find_idx = i;
        }
    }

    if(find_idx == -1) {
        done();
        return;
    }

    vector<int> vis(n);

    auto visit = [&](auto self, int i, int p) -> void {
        vis[i] = 1;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
    };

    visit(visit,find_idx,-1);

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            visit(visit,i,-1);
            int b = *adj[find_idx].begin();
            toggle(i,find_idx,b);
        }
    }

    done();

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}