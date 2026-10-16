#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {

    int n, q; cin >> n >> q;

    auto difdif = [&](vector<vector<int>> &mat, int i, int j) -> int {
        return mat[i+1][j] - mat[i][j];
    };

    auto get_diff = [&](vector<vector<int>> &mat, vector<vector<int>> &mat2) -> vector<vector<int>> {
        vector<vector<int>> res;
        for(int i = 0; i < n; i++) {
            res.push_back({});
            for(int j = 0; j + 1 < n; j++) {
                res.back().push_back(mat[i][j+1] - mat[i][j] - (mat2[i][j+1] - mat2[i][j]));
            }
        }
        return res;
    };

    auto upd_status = [&](int col, vector<vector<int>> &a, vector<vector<int>> &status) -> void {
        assert(0 <= col && col < n - 1);
        for(int i = n - 1; i >= 0; i--) {
            if(i == n - 1) {
                status[i][col] = n;
            } else {
                if(difdif(a, i, col) == 0) {
                    status[i][col] = status[i+1][col];
                } else {
                    status[i][col] = i + 1;
                }
            }
        }
    };

    auto upd_upd = [&](int col, int rl, int rr, int delta, vector<vector<int>> &a, vector<vector<int>> &status) -> void {
        // cout << "upd upd col : " << col << " rl " << rl << " rr : " << rr << " delta : " << delta << endl;
        for(int i = rl; i < rr; i++) {
            a[i][col] += delta;
        }
        upd_status(col, a, status);
    };

    auto query = [&](int col, int rl, int rr, vector<vector<int>> &status) -> int {
        return status[rl][col] >= rr;
    };
    
    vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n));
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;

    vector<vector<int>> ta = a, tb = b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            swap(ta[i][j], ta[j][i]);
            swap(tb[i][j], tb[j][i]);
        }
    }

    vector<vector<int>> col_status(n, vector<int>(n - 1)), tcol_status(n, vector<int>(n - 1));

    a = get_diff(a, b);
    ta = get_diff(ta, tb);

    for(int i = 0; i + 1 < n; i++) {
        upd_status(i, a, col_status);
        upd_status(i, ta, tcol_status);
    }

    for(int qq = 0; qq < q; qq++) {
        char type; cin >> type;
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--;
        if(type == 'U') {
            int x; cin >> x;
            if(c1) {
                upd_upd(c1 - 1, r1, r2, x, a, col_status);
            }
            if(c2 != n) {
                upd_upd(c2 - 1, r1, r2, -x, a, col_status);
            }
            if(r1) {
                upd_upd(r1 - 1, c1, c2, x, ta, tcol_status);
            }
            if(r2 != n) {   
                upd_upd(r2 - 1, c1, c2, -x, ta, tcol_status);
            }
        } else {
            int ok = 1;
            for(int i = c1; i + 1 < c2; i++) {
                // ok &= query(i, r1, r2, col_status);
                ok &= col_status[r1][i] >= r2;
            }
            for(int i = r1; i + 1 < r2; i++) {
                // ok &= query(i, c1, c2, tcol_status);
                ok &= tcol_status[c1][i] >= c2;

            }
            cout << (ok ? "Yes" : "No") << '\n';
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}