#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll res = 0, c = 0;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        res += c * x;
        c += x;
    }    

    cout << res << '\n';

    return 0;
}
