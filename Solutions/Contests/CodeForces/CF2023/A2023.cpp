#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[0] + lhs[1] < rhs[0] + rhs[1];
    });
    for(int i = 0; i < n; i++) {
        cout << a[i][0] << " " << a[i][1] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}