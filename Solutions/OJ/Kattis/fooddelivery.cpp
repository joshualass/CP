#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> unlocks(n);
    ll s = 0;

    for(int i = 0; i < n; i++) {
        cin >> unlocks[i][0] >> unlocks[i][1];
        s += unlocks[i][0];
    }

    sort(unlocks.begin(), unlocks.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] > rhs[1];
    });

    ll res = LLONG_MIN;
    for(auto [p, d] : unlocks) {
        res = max(res, s - d);
        s -= p;
    }
    
    cout << res << '\n';

    return 0;
}
