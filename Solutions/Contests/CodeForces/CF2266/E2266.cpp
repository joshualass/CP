#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int N = 200001;

vector<int> pf[N];

void solve() {
    
    int n, k; cin >> n >> k;
    ll res = 0;
    vector<ll> dp(n + 1);
    for(int i = k + 1; i <= n; i++) {
        ll lo = LLONG_MAX;
        for(int x : pf[i]) {
            lo = min(lo, 1 + x * dp[i / x]);
        }
        dp[i] = lo;
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        res += dp[x];
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 2; i < N; i++) {
        if(pf[i].empty()) {
            for(int j = 1; i * j < N; j++) {
                pf[i * j].push_back(i);
            }
        }
    }



    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}