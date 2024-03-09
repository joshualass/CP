#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x, n; cin >> x >> n;
    int ans = 1;
    for(int i = 1; i <= sqrt(x); i++) {
        if(x % i == 0) {
            if(x / i >= n) {
                ans = max(ans, i);
            }
            if(i >= n) {
                ans = max(ans, x / i);
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}