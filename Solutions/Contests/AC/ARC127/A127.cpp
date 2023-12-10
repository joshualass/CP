#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll solve(ll n) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;

    ll ans = 0;
    while(n != 0) {
        ans += solve(n);
        cout << "n : " << n << " solve : " << solve(n) << '\n';
        n /= 10;
    }
    cout << ans << '\n';
    return 0;
}