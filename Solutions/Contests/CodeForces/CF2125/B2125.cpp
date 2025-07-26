#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll a, b, k; cin >> a >> b >> k;
    ll g = gcd(a, b);
    a /= g, b /= g;

    cout << 1 + ((int) (max(a, b) > k)) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}