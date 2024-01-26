#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, M; cin >> n >> M;
    vector<pair<ll,ll>> v(n);
    for(auto &p : v) cin >> p.first >> p.second;

    ll l = 1, r = 2e9;
    while(l != r) {
        ll m = (l + r) / 2;
        ll stocks = 0;
        for(auto &p : v) {
            ll profit = p.first * m - p.second;
            if(profit > 0) stocks += profit;
            if(stocks >= M) break;
        }
        // cout << "m : " << m << " stocks : " << stocks << '\n';
        if(stocks >= M) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';

    return 0;
}