#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k; cin >> n >> k;

    vector<array<ll,3>> d(n);
    for(auto &x : d) {
        for(auto &y : x) cin >> y;
    }

    auto work = [&](ll test) -> ll {
        ll ops = 0;
        // cout << "test : " << test << endl;
        for(auto [a, b, c] : d) {
            if(a + b + c < test) {
                if(a == b && b == c) {
                    ops += 2e18;
                } else {
                    ll rev = max(0LL, min({b - a + 1, c - b + 1, c - a + 1}));
                    ops += rev * 2 + (test - (a + b + c));
                }
            }
            // cout << "ops : " << ops << endl;
            if(ops > k) break;
        }
        return ops;
    };

    ll lo = -1e10, hi = 2e18;
    while(lo != hi) {
        ll m = (lo + hi + 1) / 2;
        if(work(m) <= k) {
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
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}