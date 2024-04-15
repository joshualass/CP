#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    ll res = 0;
    for(ll i = 1; i <= n; i++) {
        res += i * (i * 2 - 1);
    }
    cout << res << " " << n * 2 << '\n';
    for(int i = 1; i <= n; i++) {
        cout << 1 << " " << i << " ";
        for(int j = n; j >= 1; j--) {
            cout << j << " \n"[j == 1];
        }
        cout << 2 << " " << i << " ";
        for(int j = n; j >= 1; j--) {
            cout << j << " \n"[j == 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}