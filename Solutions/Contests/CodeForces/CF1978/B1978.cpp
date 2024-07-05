#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, a, b; cin >> n >> a >> b;
    ll bb = max(0LL, min(n, b - a + 1));
    ll aa = n - bb;
    // cout << "bb : " << bb << '\n';
    cout << bb * (b + b - (bb - 1)) / 2 + aa * a << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}