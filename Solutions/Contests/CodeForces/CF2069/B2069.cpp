#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;
    vector<int> dx = {0,0,1,-1}, dy = {1,-1,0,0};
    int hi = 1;
    map<int,int> v;
    for(int i = 0; i < n; i++) {
        for(int j = 0;j < m; j++) {
            int c = a[i][j];
            v[c] = max(v[c], 1);
            for(int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if(ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if(a[ni][nj] == a[i][j]) {
                        v[c] = 2;
                        hi = 2;
                    }
                }
            }
        }
    }
    int res = 0;
    for(auto [c, d] : v) res += d;
    cout << res - hi << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}