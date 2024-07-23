#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, x; cin >> n >> x;
    vector<ll> a(n);
    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i-1];
        p[i] = p[i-1] + a[i-1];
    }

    ll res = 0;
    vector<ll> ways(n+1);
    for(int i = n - 1; i >= 0; i--) {
        int lo = i, hi = n;
        while(lo != hi) {
            int m = (lo + hi) / 2;
            if(p[m + 1] - p[i] > x) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }
        if(lo != n) {
            ways[i] = ways[lo+1] + 1;
            res += ways[i];
        }

    }

    cout << n * (n + 1) / 2 - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}