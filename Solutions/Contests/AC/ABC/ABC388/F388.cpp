#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, a, b; cin >> n >> m >> a >> b;
    vector<array<ll,2>> ranges(m);
    for(auto &x : ranges) cin >> x[0] >> x[1];
    ranges.push_back({(ll)1e18,(ll)1e18});

    auto reachable = [&](ll x) -> bool {
        ll l = 0, r = ranges.size() - 1;
        while(l != r) {
            ll m = (l + r + 1) / 2;
            if(ranges[m][0] <= x) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        return (x < ranges[l][0] || x > ranges[l][1]) && x >= 1 && x <= n;
    };

    vector<ll> dp(400);
    dp[0] = 1;
    for(ll i = 0; i < 400; i++) {
        for(ll j = a; j <= b; j++) {
            if(dp[i] && i + j < 400) {
                dp[i+j] = 1;
            }
        }
    }

    set<ll> ps;
    for(auto [l, r] : ranges) {
        for(ll i = 1; i <= 20; i++) {
            if(reachable(l-i)) {
                ps.insert(l-i);
            }
            if(reachable(r+i)) {
                ps.insert(r+i);
            }
        }
    }

    if(reachable(1)) ps.insert(1);
    if(reachable(n)) ps.insert(n);

    vector<ll> p(ps.begin(), ps.end());
    vector<ll> preach(p.size());

    auto canreach = [&](ll i, ll j) -> bool {
        ll lo = p[i], hi = p[j];
        ll diff = hi - lo;
        if(diff >= a && diff <= b) return 1;
        ll l = 0, r = ranges.size() - 1;
        while(l != r) {
            ll m = (l + r) / 2;
            if(ranges[m][0] > lo) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if(hi > ranges[l][0]) return 0;
        ll mindiff = 1e18;
        for(ll i = (hi - lo) % a; i < 400; i += a) {
            if(dp[i]) {
                mindiff = i;
                break;
            }
        }
        return lo + mindiff <= hi;
    };

    ll f = 0;
    preach[0] = 1;

    for(ll i = 0; i < p.size(); i++) {
        if(preach[i]) {
            if(p[i] == n) f = 1;
            for(ll j = i + 1; j < p.size() && j - i < 50; j++) {
                if(canreach(i,j)) {
                    preach[j] = 1;
                }
            }
        }
    }

    cout << (f ? "Yes" : "No") << '\n';

    return 0;
}