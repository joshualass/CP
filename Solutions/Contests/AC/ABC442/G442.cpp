#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c; cin >> n >> c;
    vector<array<ll,3>> a(n);
    ll ws = 0;
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
        ws += x[0] * x[2];
    }
    c = min(c, ws);

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] * rhs[0] > rhs[1] * lhs[0];
    });

    ll score = 0;

    vector<array<ll,2>> adds(3);
    for(ll i = 0; i < n; i++) {
        auto [w, v, k] = a[i];
        ll add = min(c / w, k);
        if(add) {
            a[i][2] -= add;
            adds.push_back({i, add});
            score += add * v;
            c -= add * w;
        }
    }

    const ll F = 3;
    array<ll,3> unadd = {F, F, F};
    for(ll i = sz(adds) - 1; i >= 0; i--) {
        auto [idx, cnt] = adds[i];
        auto [w, v, k] = a[idx];
        ll add_back = min(cnt, unadd[w - 1]);
        
        unadd[w - 1] -= add_back;
        a[idx][2] += add_back;
        score -= 1LL * add_back * v;
        c += add_back * w;
    }

    vector<array<ll,2>> b;
    array<ll,3> consider = {F * 2, F * 2, F * 2};

    for(auto [w, v, k] : a) {
        while(k && consider[w - 1]) {
            consider[w - 1]--;
            k--;
            b.push_back({w, v});
        }
    }

    vector<ll> dp(c + 1), ndp(c + 1);
    for(auto [w, v] : b) {
        ndp.assign(c + 1, 0LL);
        for(int i = 0; i <= c; i++) {
            ndp[i] = dp[i];
            if(i >= w) ndp[i] = max(ndp[i], dp[i-w] + v);
        }
        dp = ndp;
    }

    cout << score + (*max_element(dp.begin(), dp.end())) << '\n';

    return 0;
}
