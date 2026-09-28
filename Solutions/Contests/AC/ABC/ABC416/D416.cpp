#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, m; cin >> n >> m;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int l = 0, r = n - 1;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] + b[r] >= m) {
            res += (a[i] + b[r]) % m;
            r--;
        } else {
            res += (a[i] + b[l]) % m;
            l++;
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}