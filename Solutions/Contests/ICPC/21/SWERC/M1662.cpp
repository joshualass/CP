#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    int maxr = 0, maxw = 0;
    for(int i = 0; i < m; i++) {
        int r, w; cin >> r >> w;
        maxr = max(r,maxr);
        maxw = max(w,maxw);
    }
    if(maxr + maxw <= n) {
        string res = "";
        for(int i = 0; i < maxr; i++) {
            res.push_back('R');
        }
        while(res.size() != n) {
            res.push_back('W');
        }
        cout << res << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}