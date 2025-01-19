#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll x; cin >> x;
    ll f = 1, n = 1;
    while(f != x) {
        n++;
        f *= n;
    }    

    cout << n << '\n';

    return 0;
}