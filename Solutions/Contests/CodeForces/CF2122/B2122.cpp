#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        if(d < b) {
            res += a + b - d;
        } else {
            res += max(0LL, a - c);
        }
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