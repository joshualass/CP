#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<array<ll,2>> c(m);
    for(auto &x : c) for(auto &y : x) cin >> y;

    sort(c.begin(), c.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[0] - lhs[1] < rhs[0] - rhs[1];
    });

    ll res = 0;
    for(auto [a, b] : c) {
        // cout << "a : " << a << " b : " << b << '\n';
        if(n >= a) {
            ll ops = 1 + (n - a) / (a - b);
            // cout << "n : " << n << " ops : " << ops << '\n';
            res += ops;
            n -= ops * (a - b);
        }
    }

    cout << res << '\n';

    return 0;
}
