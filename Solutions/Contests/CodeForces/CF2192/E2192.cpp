#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    // vector<map<int,set<int>>> adj(n);
    vector<vector<array<int,2>>> adj(n);
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        a[i]--; b[i]--;
        // adj[a[i]][b[i]].insert(i);
        // adj[b[i]][a[i]].insert(i);
        adj[a[i]].push_back({b[i], i});
        adj[b[i]].push_back({a[i], i});
    }

    vector<int> res;

    for(int i = 0; i < n; i++) {
        int cur = i;
        while(adj[cur].size()) {
            auto [to, idx] = adj[cur].back();
            adj[cur].pop_back();
            if(vis[idx]) continue;
            vis[idx] = 1;

            if(a[idx] != cur) {
                swap(a[idx], b[idx]);
                res.push_back(idx);
            }
            cur = to;
        }
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    if(a == b) {
        cout << sz(res) << '\n';
        for(int i = 0; i < sz(res); i++) cout << res[i] + 1 << " \n"[i == sz(res) - 1];
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