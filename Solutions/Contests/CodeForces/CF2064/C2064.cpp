#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {

    int n; cin >> n;
    
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<ll> p(n), s(n);
    for(int i = 0; i < n; i++) {
        p[i] += (i ? p[i-1] : 0LL);
        if(a[i] > 0) p[i] += a[i];
    }
    for(int i = n - 1; i >= 0; i--) {
        s[i] += (i == n - 1 ? 0 : s[i+1]);
        if(a[i] < 0) s[i] -= a[i];
    }
    ll res = 0;
    for(int i = 0; i < n; i++) res = max(res, p[i] + s[i]);
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}