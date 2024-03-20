#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int a, b, c; cin >> a >> b >> c;
    if(a == b) {
        cout << c << '\n';
    }
    if(a == c) {
        cout << b << '\n';
    }
    if(b == c) {
        cout << a << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}