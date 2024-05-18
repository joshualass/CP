#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vector<pair<ll,ll>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    vector<pair<ll,ll>> u;
    while(v.size() != (k + m - 1) / m) {
        v.pop_back();
    }
    sort(v.begin(), v.end(), [] (const pair<ll,ll> &lhs, const pair<ll,ll> &rhs) -> bool {
        return lhs.second < rhs.second;
    });

    ll sum = 0;
    for(int i = 0; i < v.size(); i++) {
        sum += v[i].first;
    }
    ll sz = k - (k - 1) / m * m;
    ll ans = LLONG_MAX;
    for(ll i = 0; i < v.size(); i++) {
        ll ex = (sum - v[i].first) * m + sz * v[i].first;
    
        ll bs = i * (i - 1) * m * m / 2;
        ll bc = i * m;

        ll is = bc * sz;
        bc += sz;

        ll as = (v.size() - i - 1) * (v.size() - i - 2) * m * m / 2 + bc * m * (v.size() - i - 1);

        ll res = bs + is + as + ex;
        // cout << "i : " << i << " res : " << res << "\n";
        // cout << "bs : " << bs << " is : " << is << " as : " << as << " ex : " << ex << '\n';
        ans = min(ans, res);
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