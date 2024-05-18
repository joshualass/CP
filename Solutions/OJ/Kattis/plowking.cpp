#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;

    ll lo = 1;
    ll res = 0;
    for(ll i = 2; i <= n; i++) {
        res += lo;
        ll use = min((m - lo) - (n - i - 1), i - 1);
        lo += use;
    }

    cout << res << '\n';

    return 0;
}