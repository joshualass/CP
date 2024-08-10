#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x, y, k; cin >> x >> y >> k;
    for(int i = 0; i < k / 2; i++) {
        cout << x + i + 1 << " " << y << "\n";
        cout << x - i - 1 << " " << y << '\n';
    }
    if(k & 1) {
        cout << x << " " << y << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}