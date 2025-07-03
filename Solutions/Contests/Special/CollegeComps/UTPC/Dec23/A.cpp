#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll l, k; cin >> l >> k;
    ld area = l * l;

    for(int i = 0; i < k; i++) {
        area /= 2;
    }

    cout << fixed << setprecision(10) << area << '\n';

    return 0;
}