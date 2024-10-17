#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, x; cin >> n >> x;
    ll hi = 0, sum = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        hi = max(hi,num);
        sum += num;
    }
    cout << max(hi, (sum + x - 1) / x) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}