#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    ll gmax = 0;
    ll lmax = 0;
    ll s= 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        lmax = max(0LL, lmax + num);
        gmax = max(gmax,lmax);
        s += num;
    }
    s %= MOD;
    ll add = gmax;
    for(int i = 0; i < k; i++) {
        s += add;
        s %= MOD;
        add *= 2;
        add %= MOD;
    }

    cout << (s + MOD) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}