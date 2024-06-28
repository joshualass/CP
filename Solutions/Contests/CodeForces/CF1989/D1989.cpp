#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];
    
    sort(a.begin(), a.end(), [] (const auto &lhs, const auto &rhs) -> bool {
        int ldiff = lhs[0] - lhs[1];
        int rdiff = rhs[0] - rhs[1];
        if(ldiff == rdiff) {
            return lhs[0] < rhs[0];
        } else {
            return ldiff < rdiff;
        }
    });
    
    vector<array<ll,2>> useful;
    int prevdiff = 0, preva = INT_MAX;
    for(auto x : a) {
        if(x[0] < preva && x[0] - x[1] > prevdiff) {
            useful.push_back(x);
            prevdiff = x[0] - x[1];
            preva = x[0];
        }
    }
    
    reverse(useful.begin(), useful.end());
    
    // for(auto a : useful) {
    //     cout << "a : " << a[0] << ", " << a[1] << '\n';
    // }
    
    //how much xp can be gained from this amt of ingots
    vector<ll> dp(1e6 + 1);
    
    int uptr = -1;
    for(int i = 1; i <= 1e6 + 1; i++) {
        if(uptr != useful.size() - 1 && useful[uptr+1][0] <= i) uptr++;
        dp[i] = dp[i-1];
        if(uptr >= 0) {
            dp[i] = max(dp[i],dp[i - (useful[uptr][0] - useful[uptr][1])] + 1);
        }
    }
    
    // for(int i = 0; i < 20; i++) {
    //     cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
    // }
    // cout << dp.back() << '\n';
    ll res = 0;
    array<ll,2> last = useful.back();
    for(int i = 0; i < m; i++) {
        ll c; cin >> c;
        //how many times can I use the last item in useful on this metal
        
        if(c > 1e6 + 1) {
            ll times = (c - last[0]) / (last[0] - last[1]);
            // cout << "c : " << c << " times : " << times << '\n';
            c -= times * (last[0] - last[1]);
            res += times;
        }
        res += dp[c];
    }
    
    cout << res * 2 << '\n';

    return 0;
}