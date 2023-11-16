#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    ll maxleft = -1;
    ll minright = -1;
    for(int i = 0; i < n; i++) {
        ll l, r; cin >> l >> r;
        if(maxleft == -1) {
            maxleft = l;
            minright = r;
        } else {
            maxleft = max(maxleft, l);
            minright = min(minright, r);
        }
        cout << max(0LL, (maxleft - minright + 1) / 2) << '\n';
    }

    return 0;
}