#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[b].push_back(a);
    }
    vector<array<int,2>> vis(n);
    for(int i = 0; i < n; i++) {
        vis[i] = {-1, i};
    }

    queue<array<int,2>> q;
    q.push({0,1});

    while(q.size()) {
        auto [i, size] = q.front();
        q.pop();
        if(vis[i][0] != -1) continue;
        vis[i][0] = size;
        for(int c : adj[i]) {
            if(vis[c][0] == -1) {
                q.push({c, size + 1});
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(vis[i][0] == -1) {
            cout << "INFINITE\n";
            return;
        }
    }

    sort(vis.begin(), vis.end());

    vector<int> res;
    
    while(1) {
        bool found = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(vis[i][0]) {
                res.push_back(vis[i][1]);
                vis[i][0]--;
                found = 1;
            }
        }
        if(!found) break;
    }
    cout << "FINITE\n";
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] + 1 << " \n"[i == res.size() - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}