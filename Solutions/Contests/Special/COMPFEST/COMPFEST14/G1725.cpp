#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll l = 1, r = 1e10;
    while(l != r) {
        ll m = (l + r) / 2;
        ll oddcnt = (m - 1) / 2;
        ll evencnt = (m - 4) / 4;
        if(oddcnt + evencnt < n) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    cout << l << '\n';
    return 0;
}