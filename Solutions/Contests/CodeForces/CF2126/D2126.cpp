#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, k; cin >> n >> k;
    vector<array<int,3>> a(n);
    for(auto &x : a) for(int &y : x) cin >> y;
    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[2] < rhs[2];
    });

    for(auto [l, r, real] : a) {
        if(l <= k && k <= r) k = max(k, real);
    }

    cout << k << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}