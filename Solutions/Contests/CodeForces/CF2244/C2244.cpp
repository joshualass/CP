#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, x, y; cin >> n >> x >> y;
    int g = gcd(x, y);

    vector<vector<int>> groups(g);
    for(int i = 0; i < n; i++) {
        int val; cin >> val;
        groups[i % g].push_back(val);
    }
    for(auto &g : groups) {
        sort(g.begin(), g.end());
    }

    vector<int> res;

    for(int i = 0; i < n; i++) {
        res.push_back(groups[i % g][i / g]);
    }

    cout << (is_sorted(res.begin(), res.end()) ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}