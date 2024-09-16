#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1000000007;

void solve() {
    int n; cin >> n;
    ll res = 1;
    for(int i = 3; i <= n * 2; i++) {
        res *= i;
        res %= MOD;
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