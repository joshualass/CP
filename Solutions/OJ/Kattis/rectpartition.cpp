#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    map<char,array<int,2>> x, y;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            char c = a[i][j];
            if(x.count(c) == 0) {
                x[c] = {INT_MAX, INT_MIN};
                y[c] = {INT_MAX, INT_MIN};
            }
            x[c][0] = min(x[c][0], i);
            x[c][1] = max(x[c][1], i);
            y[c][0] = min(y[c][0], j);
            y[c][1] = max(y[c][1], j);
        }
    }

    int ok = 1;

    for(auto [c, _] : x) {
        int xlo = x[c][0], xhi = x[c][1];
        int ylo = y[c][0], yhi = y[c][1];
        for(int i = xlo; i <= xhi; i++) {
            for(int j = ylo; j <= yhi; j++) {
                if(a[i][j] != c) ok = 0;
            }
        }
        if(!ok) break;
    }

    cout << (ok ? "YES" : "NO") << '\n';

    return 0;
}
