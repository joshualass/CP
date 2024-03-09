#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, b, x; cin >> n >> b >> x;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    ll largest_army = *max_element(v.begin(), v.end());
    vector<pair<ll,ll>> squads(largest_army + 1);
    for(ll x : v) {
        for(ll i = 1; i <= x; i++) {
            ll base = x / i;
            ll extra = x % i;
            ll basep = base + 1;
            ll cnt = (basep * extra * (x - basep) + base * (i - extra) * (x - base)) / 2;
            // cout << "army size : " << x << " squad cnt : " << i << " cnt : " << cnt << '\n';
            if(x != i) {
                squads[i].first += cnt;
            } else {
                squads[i].second += cnt;
            }
        }
    }
    ll ans = 0, cnt = 0;
    for(ll i = 1; i <= largest_army; i++) {
        cnt += squads[i].second;
        ans = max(ans, b * (cnt + squads[i].first) - (i - 1) * x);
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