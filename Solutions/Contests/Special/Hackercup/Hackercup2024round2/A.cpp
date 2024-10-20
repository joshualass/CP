#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

    vector<ll> nums;


void solve() {
    ll a, b, m; cin >> a >> b >> m;

    int cnt = 0;

    for(ll &x : nums) {
        if(x >= a && x <= b && x % m == 0) cnt++;
    }

    cout << cnt << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto dfsdown = [&](auto self, int m, int k, ll curr, vector<ll> &s) -> void {
        if(k == 0) {
            s.push_back(curr);
            return;
        }

        curr *= 10;
        for(int i = 1; i <= m; i++) {
            self(self, i, k - 1, curr + i, s);
        }

    };

    auto dfsup = [&](auto self, int m, int stop, int k, ll curr, vector<ll> &s) -> void {
        if(k == 0) {
            s.push_back(curr);
            return;
        }

        curr *= 10;
        for(int i = m; i <= stop; i++) {
            self(self, i, stop, k - 1, curr + i, s);
        }

    };

    for(int m = 1; m <= 9; m++) {
        for(int k = 0; k <= 8; k++) {
            vector<ll> fronts;
            ll curr = 0;

            dfsup(dfsup, 1, m - 1, k, curr, fronts);

            // cout << "fronts size : " << fronts.size() << '\n';
            ll c = 0;

            for(ll c : fronts) {
                c = c * 10 + m;
                dfsdown(dfsdown, m - 1, k, c, nums);
            }
        }
        // cout << "m : " << m << endl;
    }

    // cout << "nums : " << nums.size() << endl;

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}