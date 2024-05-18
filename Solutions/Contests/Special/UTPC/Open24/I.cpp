#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    map<ll,ll> ma;
    for(ll i = 0; i < n; i++) {
        string s; cin >> s;
        ll num; cin >> num;
        ma[s.size()] = max(ma[s.size()], num);
    }
    vector<pair<ll,ll>> v; // {size, value}
    for(auto [a, b] : ma) {
        v.push_back({a,b});
    }

    vector<ll> dp(m+1);

    for(ll i = 1; i < m + 1; i++) {
        for(auto x : v) {
            if(i-x.first >= 0) {
                dp[i] = max(dp[i], dp[i-x.first] + x.second);
            }
        }
    }
    cout << dp.back() << '\n';
    return 0;
}