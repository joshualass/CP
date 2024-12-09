#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x, y, k; cin >> x >> y >> k;

    cout << "0 0 " << min(x,y) << " " << min(x,y) << '\n';
    cout << "0 " << min(x,y) << " " << min(x,y) << " 0" << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}