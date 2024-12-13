#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int res = 0;
    auto solve = [&](int start) {
        int l = start, r = l - 2;
        set<int> vis;
        while(r + 3 < n) {
            if(a[r+2] == a[r+3] && vis.count(a[r+2]) == 0) {
                vis.insert(a[r+2]);
                r += 2;
            } else {
                vis.erase(a[l]);
                l += 2;
                r = max(r, l - 2);
            }
            res = max(res, r - l + 2);
        }
    };

    solve(0);
    solve(1);

    cout << res << '\n';

    return 0;
}