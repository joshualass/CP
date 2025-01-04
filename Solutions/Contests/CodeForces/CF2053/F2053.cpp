#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<array<ll,2>>> dp(k + 1);
    vector<vector<array<ll,2>>> dpvisits(n);
    vector<map<ll,ll>> rowcnts(n);
    vector<ll> p(n);
    ll res = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            ll x; cin >> x;
            rowcnts[i][x]++;
            if(x != -1) {
                for(ll k = -1; k <= 1; k++) {
                    if(i + k >= 0 && i + k < n && (dp[x].empty() || i + k > dp[x].back()[0])) {
                        dpvisits[i + k].push_back({x, (ll) dp[x].size()});
                        dp[x].push_back({(ll) i + k, 0LL});
                    }
                }
            }
        }
        if(i) {
            p[i] = p[i-1] + rowcnts[i-1][-1] * rowcnts[i][-1];
            for(auto [x, freq] : rowcnts[i]) {
                if(x != -1) {
                    res += rowcnts[i-1][x] * freq;
                }
            }
        }
    }
    vector<ll> anyg(n), anyb(n);
    for(ll i = 0; i < n; i++) {
        if(i) {
            anyb[i] = anyb[i-1] + rowcnts[i-1][-1] * rowcnts[i][-1];
            anyg[i] = max(anyb[i-1], anyg[i-1] + rowcnts[i-1][-1] * rowcnts[i][-1]);
        }

        for(auto [x, idx] : dpvisits[i]) {
            ll s = 0;
            for(ll j = -1; j <= 1; j += 2) {
                if(i + j >= 0 && i + j < n) {
                    s += rowcnts[i + j][x] * rowcnts[i][-1];
                }
            }
            //case not coloring previous row with color x
            dp[x][idx][1] = anyg[i]+ s;

            //case colored previous row with color x
            if(i) {
                if(idx == 0) { //no previous at state. 
                    dp[x][idx][1] = max(dp[x][idx][1], anyg[i-1] + s + rowcnts[i-1][-1] * rowcnts[i][-1]);
                } else if(dp[x][idx-1][0] + 1 == dp[x][idx][0]) { //the previous row colored state exists
                    dp[x][idx][1] = max(dp[x][idx][1], dp[x][idx-1][1] + s + rowcnts[i-1][-1] * rowcnts[i][-1]);
                } else { //there exists a previous state, but it's farther back
                    dp[x][idx][1] = max(dp[x][idx][1], anyg[i-1] + s + rowcnts[i-1][-1] * rowcnts[i][-1]); //case chain from anyg
                    dp[x][idx][1] = max(dp[x][idx][1], dp[x][idx-1][1] + p[i] - p[dp[x][idx-1][0]] + s); //case chain from last at
                }
            }
            anyb[i] = max(anyb[i], dp[x][idx][1]);
        }
    }
    // cout << "anyg : " << anyg << '\n';
    // cout << "anyb : " << anyb << '\n';
    cout << res + anyb[n - 1] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}