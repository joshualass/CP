#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];

    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[1] - lhs[0] < rhs[1] - rhs[0];
    });

    ll extra = 0;
    int ok = 1;
    for(int i = 0; i < n; i++) {
        if(a[i][1] - a[i][0] > extra) {
            ok = 0;
            break;
        }
        extra += a[i][0];
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}