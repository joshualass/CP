#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int debug = 0;

int work(vector<string> a) {

    // cout << "testing a" << endl;
    // for(auto x : a) cout << x << endl;

    auto dfs = [](auto self, vector<string> a) -> int {

        int f = 0;
        int r = sz(a), c = sz(a[0]);

        // cout << "r : " << r << " c : " << c << endl;
        // for(auto x : a) cout << x << endl;

        if(r <= 2 && c <= 2) return 1;
        for(int sr = r == 1 ? 0 : -1; sr <= 0; sr++) {
            for(int sc = c == 1 ? 0 : -1; sc <= 0; sc++) {

                int ok = 1;
                vector<string> grid(2, string(2, '#'));
                vector<string> nx;

                for(int i = 0; i + sr < r; i += 2) {
                    for(int j = 0; j + sc < c; j += 2) {
                        int cnt = 0;
                        for(int k = 0; k < 2; k++) {
                            for(int l = 0; l < 2; l++) {
                                int row = sr + i + k;
                                int col = sc + j + l;
                                if(0 <= row && row < r && 0 <= col && col < c) {
                                    cnt += a[row][col] == 'X';
                                }
                            }
                        }

                        if(cnt) {
                            for(int k = 0; k < 2; k++) {
                                for(int l = 0; l < 2; l++) {
                                    int row = sr + i + k;
                                    int col = sc + j + l;
                                    if(0 <= row && row < r && 0 <= col && col < c) {
                                        if(grid[k][l] == '#' && a[row][col] != '#') grid[k][l] = a[row][col];
                                        // if(a[row][col] != '#' && a[row][col] != grid[k][l]) ok = 0;
                                    }
                                }
                            }
                        }
                    }
                }

                for(int i = 0; i + sr < r; i += 2) {
                    nx.push_back("");
                    for(int j = 0; j + sc < c; j += 2) {
                        int oposs = 1, xposs = 1;

                        for(int k = 0; k < 2; k++) {
                            for(int l = 0; l < 2; l++) {
                                int row = sr + i + k;
                                int col = sc + j + l;
                                if(0 <= row && row < r && 0 <= col && col < c) {
                                    if(a[row][col] == 'X') oposs = 0;
                                    if(grid[k][l] != '#' && a[row][col] != '#' && grid[k][l] != a[row][col]) xposs = 0;
                                }
                            }
                        }

                        if(oposs) {
                            if(xposs) {
                                nx.back().push_back('#');
                            } else {
                                nx.back().push_back('o');
                            }
                        } else {
                            if(xposs) {
                                nx.back().push_back('X');
                            } else {
                                ok = 0;
                            }
                        }
                    }
                }

                if(ok) {
                    // cout << "sr : " << sr << " sc : " << sc << endl;
                    f |= self(self, nx);
                }
            }
        }

        return f;

    };

    return dfs(dfs, a);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    if(debug == 0) {
        int r, c; cin >> r >> c;
        vector<string> a(r);
        for(auto &x : a) cin >> x;

        // a = {string(200000, 'o')};

        cout << work(a) << '\n';
    } else {

        auto printer = [&](vector<string> a, int pattern) -> vector<string> {
            vector<string> res(sz(a) * 2);
            for(int i = 0; i < sz(a); i++) {
                for(int j = 0; j < sz(a[i]); j++) {
                    for(int k = 0; k < 2; k++) {
                        for(int l = 0; l < 2; l++) {
                            int val = (pattern >> (k * 2 + l)) & 1;
                            res[i * 2 + k].push_back(val && a[i][j] == 'X' ? 'X' : 'o');
                        }
                    }
                }
            }
            return res;
        };

        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                // for(int k = 0; k < 16; k++) {

                    vector<string> res(1, "X");
                    res = printer(res, i);
                    res = printer(res, j);
                    // res = printer(res, k);
                    // cout << "i : " << i << " j : " << j << endl;
                    // cout << "res" << endl;
                    for(auto x : res) cout << x << endl;

                    for(int rlo = 0; rlo < sz(res); rlo++) {
                        for(int rhi = rlo + 1; rhi <= sz(res); rhi++) {
                            for(int clo = 0; clo < sz(res[rlo]); clo++) {
                                for(int chi = clo + 1; chi <= sz(res[rlo]); chi++) {
                                    // cout << "rlo : " << rlo << " rhi : " << rhi << " clo : " << clo << " chi : " << chi << endl;
                                    vector<string> a;
                                    for(int k = rlo; k < rhi; k++) {
                                        a.push_back("");
                                        for(int l = clo; l < chi; l++) {
                                            a.back().push_back(res[k][l]);
                                        }
                                    }

                                    if(work(a) == 0) {
                                        cout << "missing a" << endl;
                                        for(auto x : a) cout << x << endl;
                                        assert(0);
                                    }

                                }
                            }
                        }
                    }
                // }
            }
        }

        cout << "ALL OK" << endl;

    }

    

    return 0;
}
