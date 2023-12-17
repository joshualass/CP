#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, M, k; cin >> n >> M >> k;
    vector<pair<ll,ll>> cows(n);

    for(int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }

    sort(cows.rbegin(), cows.rend());
    ll ans = 0;
    map<ll,ll> m;

    for(int i = 0; i < n; i++) {

        ll weight = cows[i].first;
        ll cowcnt = cows[i].second;

        while(cowcnt != 0 && m.lower_bound(weight + k) != m.end()) {
            auto it = m.lower_bound(weight + k);
            ll adds = min(cowcnt, (*it).second);
            ans += adds;
            cowcnt -= adds;
            m[(*it).first] -= adds;
            if(m[(*it).first] == 0) {
                m.erase((*it).first);
            }
            m[weight] += adds;
        }

        ll newstackcnt = min(cowcnt, M);
        ans += newstackcnt;
        m[weight] += newstackcnt;
        M -= newstackcnt;

    }

    cout << ans << '\n';

    return 0;
}