#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll recur(ll l, ll r, vector<ll> &pos, vector<vector<ll>> &dp, ll &h) {
    if(r-l<= 1) return 0;
    if(dp[l][r] == -1) {
        ll res = LLONG_MAX;
        for(ll i = l; i < r; i++) {
            ll left = min(h, (pos[i] - pos[l] - 1) / 2);
            ll right = min(h, (pos[r] - pos[i+1] - 1) / 2);
            res = min(res, left + recur(l,i,pos,dp,h) + right + recur(i+1,r,pos,dp,h));
        }
        dp[l][r] = res;
    }
    return dp[l][r];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, h; cin >> n >> h;

    vector<ll> pos(n);
    for(ll &x : pos) cin >> x;
    vector<vector<ll>> dp(n,vector<ll>(n,-1)); //left, right, 0 - start from left, 1 - left is constructed

    ll start = h + min(h, (pos[n-1]-pos[0]-1)/2);
    cout << recur(0, n - 1, pos, dp, h) + start << '\n';

    return 0;
}