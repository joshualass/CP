#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, m, k; cin >> n >> m >> k;

    vector<vector<int>> a(n, vector<int>(m));

    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }

    vector<ll> dp(m, inf), nx(m, inf);
    dp[0] = 0;



    for(int i = 0; i < n; i++) {
        nx.assign(m, inf);

        for(int shift = 0; shift < m; shift++) {
            ll cost = inf;
            for(int j = 0; j < m; j++) {
                cost = min(cost, dp[j]) + a[i][(j + shift) % m];
                nx[j] = min(nx[j], cost + 1LL * shift * k);
            }
        }
        swap(dp, nx);

        // cout << "i : " << i << " dp : " << dp << endl;
    }

    cout << dp[m - 1] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}