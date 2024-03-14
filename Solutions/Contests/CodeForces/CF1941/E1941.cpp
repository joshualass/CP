#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, k, d; cin >> n >> m >> k >> d;
    vector<ll> prefs(n+1);
    for(int i = 0; i < n; i++) {
        vector<ll> dp(m);
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
        ll t; cin >> t;
        pq.push({1,0});
        for(int j = 1; j < m; j++) {
            while(pq.size() && j - d - 1 > pq.top().second) pq.pop();
            ll num; cin >> num;
            dp[j] = pq.top().first + num + 1;
            pq.push({dp[j],j});
        }
        prefs[i+1] = prefs[i];
        prefs[i+1] += dp.back();
    }
    ll res = LLONG_MAX;
    for(int i = k; i <= n; i++) {
        res = min(res, prefs[i] - prefs[i-k]);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}