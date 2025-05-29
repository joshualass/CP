#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int s, t, w; cin >> s >> t >> w;
        s--; t--;
        adj[s].push_back({t, w});
    }

    ll l = 0, r = 1e18;
    while(l != r) {

        ll m = (l + r) / 2;

        vector<ll> b(n);
        for(int i = 0; i < n; i++) {    
            if(b[i] || i == 0) b[i] = min(m, b[i] + a[i]);
            for(auto [to, w] : adj[i]) {
                if(b[i] >= w) {
                    b[to] = max(b[to], b[i]);
                }
            }
        }

        if(b.back()) {
            r = m;
        } else {
            l = m + 1;
        }

    }

    cout << (l == 1e18 ? -1 : l) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}