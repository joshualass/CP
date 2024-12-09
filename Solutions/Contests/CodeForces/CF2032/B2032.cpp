#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    if(n == 1) {
        cout << "1\n1\n";
        return;
    }
    if(k == 1 || k == n) {
        cout << "-1\n";
        return;
    }
    if((k & 1) == 0) {
        cout << "3\n" << 1 << " " << k << " " << k + 1 << '\n';
    } else {
        cout << "3\n" << 1 << " " << k - 1 << " " << k + 2 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}