#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;
    bool ok = 0;
    for(int i = 0; i < n; i++) {
        if(c[i] != a[i] && c[i] != b[i]) ok = 1;
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}