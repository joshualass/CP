#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, g, b; cin >> n >> g >> b;
    ll needed_good = (n + 1) / 2;
    ll total_bad_cycles = (needed_good + g - 1) / g - 1;
    cout << max(n,needed_good + total_bad_cycles * b) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}