#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    vector<pair<int,ll>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].second;
    }
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].first = abs(v[i].first);
    }
    sort(v.begin(),v.end());
    bool ok = 1;
    ll total_health = 0;
    for(int i = 0; i < n; i++) {
        total_health += v[i].second;
        if((total_health - 1) / k >= v[i].first) {
            ok = 0;
            break;
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}