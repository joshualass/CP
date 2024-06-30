#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll INF = 1e12;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    vector dp(n+1, vector<ll>(26));
    vector<ll> p(n+1);

    auto add = [&](int i, ll v) {
        p[i] = min(p[i] + v, INF);
        for(ll &x : dp[i]) {
            x = min(x + v, INF);
        }
    };

    add(0,1);

    for(int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        for(int j = n - 1; j >= 0; j--) {
            ll v = dp[j][c];
            dp[j][c] = 0;
            add(j+1,v);
        }
    }

    // cout << p << '\n';

    ll res = 0;
    for(ll i = n; i >= 0; i--) {
        ll cnt = min(k, p[i]);
        k -= cnt;
        res += (n - i) * cnt;
    }

    if(k != 0) res = -1;
    cout << res << '\n';

    return 0;
}