#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];

    auto find_cost = [&](ll center) -> ll {
        vector<ll> b;
        int centers = 0;
        for(auto [left, right] : a) {
            if(right < center) {
                b.push_back(right);
            } else if(left > center) {
                b.push_back(left);
            } else {
                b.push_back(center);
            }
        }
        ll res = 0;
        ll cost = 0;
        sort(b.begin(), b.end());

        for(int i = 0; i < n; i++) {
            res += i * b[i] - cost;
            cost += b[i];
        }

        return res;
    };

    ll l = 1, r = 1e7;
    while(r - l > 5) {
        ll m1 = l + (r - l) / 3;
        ll m2 = l + (r - l) * 2 / 3;
        if(find_cost(m1) > find_cost(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }

    ll res = LLONG_MAX;
    for(int i = l; i <= r; i++) {
        res = min(res, find_cost(i));
    }

    cout << res << '\n';

    return 0;
}