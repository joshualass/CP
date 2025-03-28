#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    ll score = 0;
    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        if(i == n - 2) {
            score -= a;
        } else {
            score += a;
        }
    }
    cout << score << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}