#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
Code currently fails the following testcase
5 3 4 3
ft. Andwerp
fix 3x3 square magically works. gg
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sn = 0, sm = 0;
    int n, m, a, b; cin >> n >> m >> a >> b;
    vector<string> res(n,string(m,'.'));

    auto greedy_strategy = [&]() -> bool {
        int ta = a, tb = b, tn = n - sn, tm = m - sm;
        if(tn & 1) ta -= min(tm / 2, ta);
        if(tm & 1) tb -= min(tn / 2, tb);
        if((tn / 2) * (tm / 2) < (ta + 1) / 2 + (tb + 1) / 2) return 0;

        // cout << "greedy ok a : " << a << " b : " << b << " sn : " << sn << " n : " << n << " sm : " << sm << " m : " << m << '\n';

        if(tn & 1) {
            for(int i = sm; i + 1 < m; i += 2) { 
                if(a) {
                    a--;
                    res[n-1][i] = '<';
                    res[n-1][i+1] = '>';
                }
            }
            n--;
        }

        if(tm & 1) {
            for(int i = sn; i + 1 < n; i += 2) {
                if(b) {
                    b--;
                    res[i][m-1] = '^';
                    res[i+1][m-1] = 'v';
                }
            }
            m--;
        }

        for(int i = sn; i < n; i += 2) {
            for(int j = sm; j < m; j += 2) {
                if(a) {
                    res[i][j] = '<';
                    res[i][j+1] = '>';
                    a--;
                    if(a) {
                        res[i+1][j] = '<';
                        res[i+1][j+1] = '>';
                        a--;
                    }
                } else if(b) {
                    res[i][j] = '^';
                    res[i+1][j] = 'v';
                    b--;
                    if(b) {
                        res[i][j+1] = '^';
                        res[i+1][j+1] = 'v';
                        b--;
                    }
                }
            }
        }

        return 1;
    };

    // auto spiral_strategy = [&]() -> bool {
    //     int ta = a, tb = b, tn = n - sn, tm = m - sm;
    //     if(ta < tm - 1 || tb < tn - 1) return 0;

    //     a -= tm - 1;
    //     b -= tn - 1;

    //     for(int i = sm; i + 1 < m - 1; i += 2) {
    //         res[sn][i] = '<';
    //         res[sn][i+1] = '>';
    //     }
    //     for(int i = sm + 1; i < m - 1; i += 2) {
    //         res[n-1][i] = '<';
    //         res[n-1][i+1] = '>';
    //     }
    //     for(int i = sn; i + 1 < n - 1; i += 2) {
    //         res[i][m-1] = '^';
    //         res[i+1][m-1] = 'v';
    //     }
    //     for(int i = sn + 1; i < n - 1; i += 2) {
    //         res[i][sm] = '^';
    //         res[i+1][sm] = 'v';
    //     }
    //     return 1;
    // };

    auto threeXthree_strategy = [&]() -> bool {
        int ta = a, tb = b, tn = n - sn, tm = m - sm;
        if(tn < 3 || tm < 3) return 0;
        ta -= min(ta, 2 + (tm - 3) / 2);
        tb -= min(tb, 2 + (tn - 3) / 2);
        if((ta + 1) / 2 + (tb + 1) / 2 > (tn / 2) * (tm / 2) - 1) return 0;

        for(int i = sm; i + 1 < m - 3; i += 2) { 
            res[n-1][i] = '<';
            res[n-1][i+1] = '>';
        }

        for(int i = sn; i + 1 < n - 3; i += 2) {
            res[i][m-1] = '^';
            res[i+1][m-1] = 'v';
        }

        res[n-3][m-3] = '<';
        res[n-3][m-2] = '>';
        res[n-3][m-1] = '^';
        res[n-2][m-1] = 'v';
        res[n-1][m-1] = '>';
        res[n-1][m-2] = '<';
        res[n-1][m-3] = 'v';
        res[n-2][m-3] = '^';

        a -= 2 + (m - 3) / 2;
        b -= 2 + (n - 3) / 2;

        n--;
        m--;

        return 1;
    };

    if((n & 1) && (m & 1)) { 
        while(1) {
            if(!greedy_strategy()) {
                // cout << "greedy fail go to 3x3\n";
                // cout << "a : " << a << " b : " << b << " sn : " << sn << " n : " << n << " sm : " << sm << " m : " << m << '\n';
                if(!threeXthree_strategy()) {
                    // cout << "3x3 fail\n";
                    break;
                } else {
                    // cout << "3x3 ok\n";
                }
            } else {
                // cout << "g ok\n";
                break;
            }
        }
    } else {
        greedy_strategy();
    }

    if(a == 0 && b == 0) {
        cout << "YES\n";
        for(auto row : res) cout << row << '\n';
    } else {
        cout << "NO\n";
    }

    return 0;
}