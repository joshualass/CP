#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll solve(vector<ll> &heights, ll a, ll r, ll m, ll target_height) {
    m = min(m, a + r);
    ll sum = reduce(heights.begin(), heights.end());
    ll n = heights.size();
    ll target_bricks = n * target_height;

    if(sum >= target_bricks) { //need to move and remove bricks
        ll movecnt = 0;
        for(int i = 0; i < n; i++) {
            if(heights[i] < target_height) {
                movecnt += target_height - heights[i];
            }
        }
        return movecnt * m + (sum - target_bricks) * r;
    } else { //we need to move and add bricks
        ll movecnt = 0;
        for(int i = 0; i < n; i++) {
            if(heights[i] > target_height) {
                movecnt += heights[i] - target_height;
            }
        }
        return movecnt * m + (target_bricks - sum) * a;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, a, r, m; cin >> n >> a >> r >> m;

    vector<ll> heights(n);

    for(auto &x : heights) cin >> x;

    ll lo = 0, hi = 1e9;
    while(hi - lo > 5) {
        ll m1 = lo + (hi - lo) / 3;
        ll m2 = lo + ((hi - lo) * 2 + 1) / 3;
        ll ans1 = solve(heights, a, r, m, m1);
        ll ans2 = solve(heights, a, r, m, m2);

        if(ans1 < ans2) {
            hi = m2;
        } else {
            lo = m1;
        }

    }

    ll ans = LLONG_MAX;

    for(ll i = lo; i <= hi; i++) {
        ans = min(ans, solve(heights, a, r, m, i));
    }

    cout << ans << '\n';

    return 0;
}