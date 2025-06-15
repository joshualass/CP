#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<array<int,3>> res;
    for(int i = 0; i < n; i++) {
        if(i) {
            res.push_back({i, 0, i - 1});
            res.push_back({i, i, n - 1});
        } else {
            res.push_back({i, 0, n - 1});
        }
    }

    cout << res.size() << '\n';
    for(auto x : res) cout << x[0] + 1 << " " << x[1] + 1 << " " << x[2] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}