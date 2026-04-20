#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<ll,2>> a(n), qs(m); // {position, utility}, workstations
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : qs) for(auto &y : x) cin >> y;

    for(int i = 0; i < m; i++) {
        ll res = LLONG_MIN;
        for(int j = 0; j < n; j++) {
            res = max(res, a[j][1] - (abs(qs[i][1]) + abs(qs[i][0] - a[j][0])));
        }
        cout << max(0LL, res) << " \n"[i == m - 1];
    }

    return 0;
}
