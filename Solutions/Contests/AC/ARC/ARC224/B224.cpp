#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n; cin >> n;
    ll sn = sqrtl(n);

    while(sn * sn > n) sn--;
    while((sn + 1) * (sn + 1) <= n) sn++;

    ll rem = n - sn * sn;
    ll remone = min(rem, sn);
    ll remtwo = rem - remone;

    cout << 2 * sn * (sn - 1) + (remone ? 2 * remone - 1 : 0LL) + (remtwo ? 2 * remtwo - 1 : 0LL) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}