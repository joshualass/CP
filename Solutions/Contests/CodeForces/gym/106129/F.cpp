#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int z = 2500;
    // ll res = 0;
    // for(int i = 1; i <= z; i++) {
    //     res += z * z / i / i;
    // }

    // cout << res << '\n';

    // int res = 0;
    // for(int i = 1; i <= z; i++) {
    //     int cnt = 0;
    //     for(int j = 1; j <= i; j++) {
    //         if(i % j == 0) cnt++;
    //     }
    //     res = max(res, cnt);
    // }
    // cout << res << '\n';
    
    //40
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            a[i][j] = s[j] == '#';
        }
    }

    int g = 0;

    for(int i = 0; i < n; i++) {
        int start = -1;
        for(int j = 0; j < m; j++) {
            if(a[i][j]) {
                if(start == -1) {
                    start = j;
                }
            } else if(start != -1) {
                g = gcd(g, j - start);
                start = -1;
            }
        }
        if(start != -1) {
            g = gcd(g, m - start);
        }
    }

    for(int i = 0; i < m; i++) {
        int start = -1;
        for(int j = 0; j < n; j++) {
            if(a[j][i]) {
                if(start == -1) {
                    start = j;
                }
            } else if(start != -1) {
                g = gcd(g, j - start);
                start = -1;
            }
        }
        if(start != -1) {
            g = gcd(g, n - start);
        }
    }

    assert(g);
    cerr << "g : " << g << endl;

    int res = 0;

    auto check = [&](int x) -> int {

        auto c = a;
        auto fs = [&](int row, int col) -> bool {
            if(row + x > n || col + x > m) return 0;
            for(int i = 0; i < x; i++) {
                for(int j = 0; j < x; j++) {
                    if(c[row + i][col + j] == 0) return 0;
                    c[row + i][col + j] = 0;
                }
            }
            return 1;
        };

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(c[i][j]) {
                    if(fs(i, j) == 0) return 0;
                }
            }
        }
        return 1;
    };

    for(int i = 1; i <= g; i++) {
        if(g % i == 0) {
            if(check(i)) res = i;
        }
    }

    cout << res << '\n';

    return 0;
}
