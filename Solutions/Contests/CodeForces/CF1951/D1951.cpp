#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    if(k > n) {
        cout << "NO\n";
        return;
    }
    if(n == k) {
        cout << "YES\n1\n1\n";
        return;
    }
    ll t = n - k + 1;
    if(n / t > 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n2\n" << t << " " << "1\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}