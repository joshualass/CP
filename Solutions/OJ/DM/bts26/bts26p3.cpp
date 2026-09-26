#include <bits/stdc++.h>
#include <cassert>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = 0; i < n; i++) sort(a[i].begin(), a[i].end());

    if((n & 1) && (m & 1)) {
        cout << "RED\n";
        return 0;
    }

    ll red = 0, blue = 0;

    if(m & 1) {
        vector<int> b;
        for(int i = 0; i < n; i++) {
            b.push_back(a[i][0]);
            a[i].erase(a[i].begin());
        }
        sort(b.begin(), b.end());
        assert(sz(b) % 2 == 0);
        for(int i = 0; i < sz(b); i += 2) {
            blue += b[i];
            red += b[i + 1];
        }
        m--;
    }

    assert(m % 2 == 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j += 2) {
            red += a[i][j];
            blue += a[i][j+1];
        }
    }

    if(red > blue) {
        cout << "RED\n";
    } else if(red == blue) {
        cout << "TIE\n";
    } else {
        cout << "BLUE\n";
    }

    return 0;
}
