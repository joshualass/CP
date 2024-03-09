#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    sort(v.begin(), v.end());
    vector<int> pref(n + 1);
    for(int i = 0; i < n; i++) {
        pref[i+1] = pref[i] + v[i];
    }
    int best = INT_MIN;
    for(int take = 0; take <= k; take++) {
        int ans = 0;
        int negative_cnt = min(x, n - take);
        int negative_idx = n - take;
        ans -= pref[negative_idx] - pref[negative_idx - negative_cnt];
        ans += pref[negative_idx - negative_cnt];
        // cout << "take : " << take << " negative cnt : " << negative_cnt << " negative_idx : " << negative_idx << " ans : " << ans << '\n';
        best = max(best, ans);
    }
    cout << best << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}