#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto get_sum = [&](ll l, ll r) -> ll {
        ll res = 0;
        for(ll i = l; i < r; i++) res += a[i];
        return res;
    }; 

    ll res;

    if(n == 1) {
        res = get_sum(0, n);
    } else {
        res = get_sum(0, n - 1) ^ get_sum(1, n) ^ get_sum(0, n) ^ get_sum(1, n - 1);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}