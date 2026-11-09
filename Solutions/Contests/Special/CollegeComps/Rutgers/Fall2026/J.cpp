#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        b[i] = min(b[i], a[i]);
    }

    vector<int> c(n);
    iota(c.begin(), c.end(), 0);
    sort(c.begin(), c.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return a[lhs] - b[lhs] < a[rhs] - b[rhs];
    });

    ll left = k - accumulate(b.begin(), b.end(), 0LL);
    int res = 0;
    for(int x : c) {
        ll test = a[x] - b[x];
        if(left >= test) {
            res++;
            // left -= test;
        }
    }

    cout << res << '\n';

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