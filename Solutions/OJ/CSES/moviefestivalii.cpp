#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    multiset<int> ms;

    for(int i = 0; i < k; i++) ms.insert(0);

    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) {
        return lhs[1] < rhs[1];
    });

    int res = 0;

    for(auto [b, c] : a) {
        if(ms.upper_bound(b) != ms.begin()) {
            res++;
            ms.erase(--ms.upper_bound(b));
            ms.insert(c);
        }
    }

    cout << res << '\n';

    return 0;
}
