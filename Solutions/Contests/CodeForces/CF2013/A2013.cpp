#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n; cin >> n;
    int x, y; cin >> x >> y;
    int limiting = min(x,y);
    cout << (n + limiting - 1) / limiting << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}