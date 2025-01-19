#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll w, s;
    cin >> w >> s;
    ll c = s * (s + 1) / 2;
    ll tot = c * 29260;
    ll diff = w - tot;
    ll ans = diff / 110;
    cout << ans << "\n";

    return 0;
}