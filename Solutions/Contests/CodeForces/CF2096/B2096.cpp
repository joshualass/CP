#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, k; cin >> n >> k;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];

    vector<ll> b(n);
    ll res = 0;
    for(int i = 0; i < n; i++) {
        res += max(a[i][0], a[i][1]);
        b[i] = min(a[i][0], a[i][1]);
    }

    sort(b.rbegin(), b.rend());
    for(int i = 0; i < k - 1; i++) res += b[i];
    res++;

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}