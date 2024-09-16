#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int p = 0;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        p += a - 1;
    }
    cout << ((p & 1) ? "errorgorn" : "maomao90") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}