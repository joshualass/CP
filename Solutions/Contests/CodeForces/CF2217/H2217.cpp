#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()



void solve() {
    
    ll n; cin >> n;
    vector<ll> w(n);
    for(ll &x : w) cin >> x;

    vector<ll> a(n * 2);
    for(ll i = 0; i < n * 2; i++) {
        ll x; cin >> x;
        a[i] = x - 1;
    }

    vector<vector<ll>> adj(n * 2);
    for(ll i = 1; i < n * 2; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<map<ll,ll>> dp(n * 2); // {have a_i here, value to get that}
    vector<ll> ps(n * 2), d(n * 2);

    auto dfs = [&](auto self, ll i, ll p) -> void {
        for(ll c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }

        //compute parent swap
        if(i) {
            ll res = a[i] == a[p] ? w[a[i]] : 0;
            int pcol = a[p];
            for(ll c : adj[i]) {
                if(c != p) {
                    ll add = d[c];
                    if(dp[c].count(pcol)) add = max(add, dp[c][pcol] + w[pcol]);
                    res += add;
                }
            }
            ps[i] = res;
        }

        //assume defaults for everything
        map<ll, vector<array<ll,2>>> m;
        ll s = 0;
        for(ll c : adj[i]) {
            if(c != p) {
                s += d[c];
                for(auto [k, v] : dp[c]) {
                    m[k].push_back({c, v});
                }
            }
        }

        for(ll c : adj[i]) {
            if(c != p) {
                ll res = s - d[c] + ps[c];
                ll val = a[c];
                for(auto [ch, v] : m[val]) {
                    if(ch != c) {
                        ll add = max(0LL, v + w[val] - d[ch]);
                        res += add;
                    }
                }
                dp[i][val] = max(dp[i][val], res);
                d[i] = max(d[i], res);
            }
        }

        //also consider no swap case
        int val = a[i];
        for(auto [ch, v] : m[val]) {
            ll add = max(0LL, v + w[val] - d[ch]);
            s += add;
        }
        dp[i][a[i]] = max(dp[i][a[i]], s);
        d[i] = max(d[i], s);

        // cout << "i : " << i << " d[i] : " << d[i] << " ps[i] : " << ps[i] << endl;
    };

    dfs(dfs, 0, -1);
    cout << d[0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}