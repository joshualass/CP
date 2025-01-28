#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    ll n; cin >> n;
    vector<ll> a(n+1);
    for (ll i = 1; i <= n; ++i)
        cin >> a[i];
    
    vector<vector<ll>> f(n+1, vector<ll>(505, -1));
    
    vector<vector<ll>> adj(n+1);

    for (ll i = 0; i < n-1; ++i) {
        ll a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<int>> gg(5005, vector<int>(5005));

    for (int i = 1; i <= 5000; ++i) {
        for (int j = 1; j <= 5000; ++j)
            gg[i][j] = gcd(i, j);
    }

    vector<vector<int>> divs(5005);

    for (int i = 2; i <= 5000; i++) {
        for (int j = 2; j <= 5000; ++j) {
            if (i % j == 0)
                divs[i].push_back(j);
            if (j % i == 0)
                divs[i].push_back(j);
        }
    }

    auto dfs = [&](auto dfs, ll v, ll p, ll val) -> void {
        // cerr << "v : " << v << endl;
        if (f[v][val] != -1)
            return;

        ll cnt = 0;
        if (val != a[v])
            cnt = val;
        
        for (auto nei : adj[v]) {
            if (nei == p)
                continue;
            ll nei_mn = 1e9;
            for (auto j : divs[val]) {
                if (gg[val][j] == 1)
                    continue;
                if (f[nei][j] == -1)
                    dfs(dfs, nei, v, j);
                nei_mn = min(nei_mn, f[nei][j]);
            }
            cnt += nei_mn;
        }
        f[v][val] = cnt;
    };

    // cerr << "f : " << f[2][2] << endl;

    for (ll i = 1; i <= 5000; ++i) {
        dfs(dfs, 1, -1, i);
    }


    ll cnt = 1e9;

    for (ll i = 1; i <= 500; ++i) {
        if (f[1][i] == -1)
            continue;
        cnt = min(cnt, f[1][i]);
    }

    cout << cnt << endl;
    
    return 0;
}