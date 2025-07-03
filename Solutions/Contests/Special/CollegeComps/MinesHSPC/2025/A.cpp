#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;

    vector<vector<ll>> adj(n);
    for(ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto check = [&](ll bm) -> ll {
        ll ok = 1;
        for(ll i = 0; i < n; i++) {
            if((bm >> i) & 1) {
                for(ll c : adj[i]) {
                    if((bm >> c) & 1) ok = 0;
                }
            }
        }
        return ok;
    };

    ll l = (n + 1) / 2, r = n / 2;
    vector<vector<ll>> d(1 << l, vector<ll>(l + 1));
    for(ll i = 0; i < 1 << l; i++) {
        d[i][__builtin_popcount(i)] += check(i);
    }

    for(ll b = 0; b < l; b++) {
        for(ll i = 0; i < 1 << l; i++) {
            if(i & 1 << b) {
                for(ll j = 0; j < l; j++) {
                    d[i][j] += d[i ^ (1 << b)][j];
                }
            }
        }
    }

    vector<ll> res(n + 1);

    for(ll i = 0; i < 1 << r; i++) {
        if(check(i << l)) {
            int tbm = (1 << l) - 1;
            for(int j = l; j < n; j++) {
                if((i >> (j - l)) & 1) {
                    for(int c : adj[j]) {
                        tbm &= ~(1LL << c);
                    }
                }
            }
            for(int j = 0; j <= l; j++) {
                res[j + __builtin_popcount(i)] += d[tbm][j];
            }
        }
    }

    for(ll x : res) cout << x << " ";
    cout << '\n';

    return 0;
}
