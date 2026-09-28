#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<pair<ld,map<ll,ll>>> a;

    for(ll i = 0; i < n; i++) {
        ll t; cin >> t;
        map<ll,ll> m; 
        for(ll j = 0; j < t; j++) {
            ll x; cin >> x;
            m[x]++;
        }
        a.push_back({t, m});
    }

    ld res = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = i + 1; j < n; j++) {
            ld c = 0;
            if(a[i].second.size() < a[j].second.size()) {
                for(auto [v, z] : a[i].second) {
                    if(a[j].second.count(v)) {
                        c += z * a[j].second[v];
                    }
                }
            } else {
                for(auto [v, z] : a[j].second) {
                    if(a[i].second.count(v)) {
                        c += z * a[i].second[v];
                    }
                }
            }
            c /= a[j].first;
            c /= a[i].first;
            // cout << "i : " << i << " j : " << j << " c : " << c << '\n';
            res = max(res, c);
        }
    }

    cout << fixed << setprecision(15) << res << '\n';

    return 0;
}
