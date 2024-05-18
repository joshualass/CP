#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool poss(vector<ll> &a, ll m, ll k) {
    ll needed = 0;
    ll total = m + a.size() - 1;
    for(int i = 0; i < a.size(); i++) {
        ll n = total / a.size() + (i < (total % a.size()));
        needed += max(0LL, n - a[i]);
    }
    return needed <= k;
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    
    for(ll &x : a) cin >> x;

    sort(a.rbegin(), a.rend());
    ll lo = 0, hi = 1e18;
    while(lo != hi) {
        ll m = (lo + hi + 1) / 2;
        if(poss(a,m,k)) {
            lo = m;
        } else {
            hi = m - 1;
        }
    }
    cout << lo << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}