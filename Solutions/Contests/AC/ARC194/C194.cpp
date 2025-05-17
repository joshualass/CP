#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<array<ll,3>> a(n);
    for(int i = 0; i < 3; i++) for(auto &x : a) cin >> x[i];

    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[2] < rhs[2];
    });

    ll sum = 0, cost = 0;
    ll ss = 0, cs = 0;
    for(int i = 0; i < n; i++) {
        if(a[i][0]) sum += a[i][2];
        ss += (a[i][0] + a[i][1]) * a[i][2];
        cs += a[i][0] ^ a[i][1];
    }

    for(int i = n - 1; i >= 0; i--) {
        if(a[i][0] && a[i][1] == 0) {
            sum -= a[i][2];
            cost += sum;
        }
    }

    for(int i = 0; i < n; i++) {
        if(a[i][0] == 0 && a[i][1]) {
            sum += a[i][2];
            cost += sum;
        }
    }

    ll res = cost;

    for(int i = n - 1; i >= 0; i--) {
        ss -= (a[i][0] + a[i][1]) * a[i][2];
        cs -= a[i][0] ^ a[i][1];

        if(a[i][0] && a[i][1]) {
            cost += ss + a[i][2];
            cost -= cs * a[i][2];
            res = min(res, cost);
        }
    }

    cout << res << '\n';

    return 0;
}
