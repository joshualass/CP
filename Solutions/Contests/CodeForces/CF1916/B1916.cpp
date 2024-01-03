#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll a, b; cin >> a >> b;
    ll g = gcd(a,b);
    a /= g;
    b /= g;
    ll div = -1;
    if(b % a == 0) {
        div = b / a;
    } else {
        div = 1;
    }
    cout << a * b * div * g << '\n';
    // ll temp = a;
    // bool ok = 1;
    // while(temp != 1) {
    //     if(temp % div != 0) {
    //         ok = 0;
    //         break;
    //     }
    //     temp /= div;
    // }
    // cout << b * div * g << '\n';
    // return;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}