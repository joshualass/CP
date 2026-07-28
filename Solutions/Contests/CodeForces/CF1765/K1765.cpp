#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll res = 0, lo = LLONG_MAX;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll x; cin >> x;
            res += x;
            if(i + j == n - 1) lo = min(lo, x);
        }
    }

    cout << res - lo << '\n';

    return 0;
}
