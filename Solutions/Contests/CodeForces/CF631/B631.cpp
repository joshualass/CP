#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<set<int>> r(n), c(m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            r[i].insert(j);
            c[j].insert(i);
        }
    }

    vector<array<int,3>> op(k);
    for(auto &x : op) for(auto &y : x) cin >> y;
    vector<vector<int>> res(n, vector<int>(m));
    for(int z = k - 1; z >= 0; z--) {
        auto [type, i, a] = op[z];
        i--;
        if(type == 1) {
            for(int x : r[i]) {
                res[i][x] = a;
                c[x].erase(i);
            }
            r[i].clear();
        } else {
            for(int x : c[i]) {
                res[x][i] = a;
                r[x].erase(i);
            }
            c[i].clear();
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << res[i][j] << " \n"[j == m - 1];
        }
    }

    return 0;
}
