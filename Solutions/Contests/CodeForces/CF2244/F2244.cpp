#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[p].push_back(i);
    }

    vector<int> a(n);
    for(int &x : a) cin >> x;

    int ok = 1;

    auto dfs = [&](auto self, int i) -> array<int,2> {
        if(adj[i].empty()) {
            return {a[i], a[i]};
        }

        // sort(adj[i].begin(), adj[i].end());

        vector<array<int,2>> lo;
        int minidx = -1;
        for(int j = 0; j < sz(adj[i]); j++) {
            int c = adj[i][j];
            array<int,2> val = self(self, c);
            lo.push_back(val);
            if(minidx == -1 || val < lo[minidx]) {
                minidx = j;
            }
        }
        rotate(lo.begin(), lo.begin() + minidx, lo.end());
        for(int i = 1; i < sz(lo); i++) {
            if(lo[i][0] < lo[i-1][1]) ok = 0;
        }
        array<int,2> ttfang = {inf, -inf};
        for(auto [z, zz] : lo) {
            ttfang[0] = min(ttfang[0], z);
            ttfang[1] = max(ttfang[1], zz);
        }
        return ttfang;
    };

    dfs(dfs, 0);

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}