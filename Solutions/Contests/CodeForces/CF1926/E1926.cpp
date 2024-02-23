#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    ll start = 1;
    ll inc = 2;
    
    while(k > (n + start) / inc) {
        k -= (n + start) / inc;
        start *= 2;
        inc *= 2;
    }

    cout << start + (k - 1) * inc << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}