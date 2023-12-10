#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;
    set<ll> s(v.begin(), v.end());
    //contains duplicate ez pz
    if(s.size() != v.size()) {
        cout << "0\n";
        return;
    }
    if(k == 1) {
        ll lo = *min_element(v.begin(), v.end());
        for(int i = 0; i < n; i++) {
            ll num = v[i];
            if(s.upper_bound(num) != s.end()) {
                lo = min(lo, *s.upper_bound(num) - num);
            }
            if(s.lower_bound(num) != s.begin()) {
                lo = min(lo, num - *--s.lower_bound(num));
            }
        }
        cout << lo << '\n';
    } else if(k == 2) {
        ll lo = *min_element(v.begin(), v.end());
        for(int i = 0; i < n; i++) {
            ll num = v[i];
            if(s.upper_bound(num) != s.end()) {
                lo = min(lo, *s.upper_bound(num) - num);
            }
            if(s.lower_bound(num) != s.begin()) {
                lo = min(lo, num - *--s.lower_bound(num));
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ll num = abs(v[i] - v[j]);
                if(s.upper_bound(num) != s.end()) {
                    lo = min(lo, *s.upper_bound(num) - num);
                }
                if(s.lower_bound(num) != s.begin()) {
                    lo = min(lo, num - *--s.lower_bound(num));
                }
            }
        }
        cout << lo << '\n';
    } else {
        cout << "0\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}