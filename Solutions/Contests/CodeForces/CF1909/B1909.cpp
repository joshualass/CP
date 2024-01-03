#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x : v) cin >> x;
    ll k = 2;
    while(true) {
        set<ll> s;
        for(int i = 0; i < n; i++) {
            s.insert(v[i] % k);
            if(s.size() > 2) break;
        }
        if(s.size() == 2) break;
        k *= 2;
    }
    cout << k << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}