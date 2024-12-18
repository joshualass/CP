#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        string trash; cin >> trash;
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans += abs((i + 1) - v[i]);
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