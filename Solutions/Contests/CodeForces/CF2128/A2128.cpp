#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, c; cin >> n >> c;

    int res = n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.rbegin(), a.rend());

    for(int i = 0; i < n; i++) {
        int cost = 0;
        for(ll j = 0, m = 1; j < n; j++, m *= 2) {
            if(a[(i + j) % n] * m > c) cost++;
        }
        res = min(res, cost);
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