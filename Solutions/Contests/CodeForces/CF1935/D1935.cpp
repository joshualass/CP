#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, c; cin >> n >> c;
    ll tp = (c + 1) * (c + 2) / 2;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    vector<ll> odds;
    vector<ll> evens;
    for(ll x : v) {
        if(x & 1) {
            odds.push_back(x);
        } else {
            evens.push_back(x);
        }
    }
    for(ll i = 0; i < n; i++) {
        tp -= 1 + v[i]/2; //num pairs of x, y where x + y == v[i]
        tp -= c - v[i] + 1;
        // ll minval = v[i];
        // ll maxval = c + c - v[i];
        // if(v[i] & 1) {
        //     ll l1 = 0, r1 = odds.size();
        //     while(l1 != r1) {
        //         ll m = (l1 + r1) / 2;
        //         if(odds[m] >= minval) {
        //             r1 = m;
        //         } else {
        //             l1 = m + 1;
        //         }
        //     }
        //     ll l2 = -1, r2 = odds.size() - 1;
        //     while(l2 != r2) {
        //         ll m = (l2 + r2 + 1) / 2;
        //         if(odds[m] <= maxval) {
        //             l2 = m;
        //         } else {
        //             r2 = m - 1;
        //         }
        //     }
        //     tp += l2 - l1 + 1;
        // } else {
        //     ll l1 = 0, r1 = evens.size();
        //     while(l1 != r1) {
        //         ll m = (l1 + r1) / 2;
        //         if(evens[m] >= minval) {
        //             r1 = m;
        //         } else {
        //             l1 = m + 1;
        //         }
        //     }
        //     ll l2 = -1, r2 = evens.size() - 1;
        //     while(l2 != r2) {
        //         ll m = (l2 + r2 + 1) / 2;
        //         if(evens[m] <= maxval) {
        //             l2 = m;
        //         } else {
        //             r2 = m - 1;
        //         }
        //     }
        //     tp += l2 - l1 + 1;
        // }
    }
    tp += odds.size() * (odds.size() + 1) / 2 + evens.size() * (evens.size() + 1) / 2;
    cout << tp << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}