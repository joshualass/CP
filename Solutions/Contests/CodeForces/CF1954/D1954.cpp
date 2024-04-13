#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll dp[5001];

void add(ll x) {
    for(ll i = 5000; i >= 0; i--) {
        if(i - x >= 0) {
            dp[i] = (dp[i] + dp[i-x]) % MOD;
        }
    }
}

void remove(ll x) {
    for(ll i = 0; i <= 5000; i++) {
        if(i - x >= 0) {
            dp[i] = (dp[i] + MOD - dp[i-x]) % MOD;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(dp,0,sizeof(dp));
    ll n; cin >> n;
    vector<ll> v(n);
    for(ll i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    dp[0] = 1;
    ll res = 0;

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j <= 5000; j++) {
            ll c = j + v[i];
            ll wb = (j + v[i] + 1) / 2;
            if(v[i] >= wb) {
                res = (res + (v[i] - wb) * dp[j]) % MOD;
            }
        }
        add(v[i]);
    }

    for(ll i = 0; i <= 5000; i++) {
        res = (res + dp[i] * ((i + 1) / 2)) % MOD;
    }

    cout << res << '\n';

    return 0;
}