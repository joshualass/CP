#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll mygcd(ll x, ll y) {
    cout << "x : " << x << " y : " << y << '\n';
    ll r = x % y;
    if(r) {
        return mygcd(y,r);
    }
    return y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "gimme 2 numbers : " << endl;
    ll x, y; cin >> x >> y;
    
    mygcd(max(x,y),min(x,y));

    return 0;
}