#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    a.insert(a.begin(), 0);
    a.push_back(0);
    
    ll res = 0;
    for(int i = 1; i + 1 < sz(a); i++) {
        ll sub = max(0LL, min(a[i] - a[i-1], a[i] - a[i+1]));
        a[i] -= sub;
        res += sub;
    }

    for(int i = 1; i < sz(a); i++) res += abs(a[i] - a[i-1]);
    
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}