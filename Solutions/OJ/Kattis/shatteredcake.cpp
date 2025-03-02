#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll w, n; cin >> w >> n;
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        sum += x * y;
    }
    cout << sum / w << '\n';
    return 0;
}