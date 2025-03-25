#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int ops = 0;
    if(n & 1) {
        n -= k;
        ops++;
        if(n & 1) n++;
    }
    k = k / 2 * 2;
    cout << ops + (n + k - 1) / k << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}