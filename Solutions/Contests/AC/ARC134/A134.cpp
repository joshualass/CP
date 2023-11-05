#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, l, w; cin >> n>> l >> w;

    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    vector<pair<ll,ll>> ranges;

    for(int i = 0; i < n; i++) {
        if(ranges.size() && ranges.back().second >= v[i]) {
            ll start = ranges.back().first;
            ranges.pop_back();
            ranges.push_back({start,v[i] + w});
        } else {
            ranges.push_back({v[i], v[i] + w});
        }
    }

    ll prev = 0;

    ll ans = 0;

    ranges.push_back({l, l});

    for(int i = 0; i < ranges.size(); i++) {
        ans += (ranges[i].first - prev + w - 1) / w;
        prev = ranges[i].second;
    }

    cout << ans << '\n';


    return 0;
}