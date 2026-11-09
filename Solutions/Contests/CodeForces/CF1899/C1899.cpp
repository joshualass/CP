#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    ll res = LLONG_MIN, cur = 0;
    int p = -1;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        if(i && (x - p) % 2 == 0) {
            cur = 0;
        }
        cur = max(x, cur + x);
        res = max(res, cur);
        p = x;
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