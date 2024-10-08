#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;

    if(k == 1) {
        cout << n << '\n';
        return;
    }
    ll op = 0;
    while(n >= k) {
        ll p = k;
        while(p * k <= n) {
            p *= k;
        }
        op++;
        n -= p;
    }
    cout << op + n << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}