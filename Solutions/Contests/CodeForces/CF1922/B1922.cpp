#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    // int n; cin >> n;


    int n; cin >> n;
    map<int,ll> m;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        m[a]++;
    }
    ll ans = 0;
    ll past = 0;
    for(pair<int,ll> p : m) {
        ans += p.second * (p.second - 1) * (p.second - 2) / 6;
        ans += (past) * (p.second) * (p.second - 1) / 2;
        past += p.second;

    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}