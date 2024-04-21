#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    if(n == 1) {
        cout << k << '\n';
        return;
    }
    ll start = 1;
    while(start * 2 + 1 <= k) {
        start = start * 2 + 1;
    }
    cout << start << " " << k - start;
    for(int i = 2; i < n; i++) {
        cout << " 0";
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}