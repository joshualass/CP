#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e18;

ll solve_slow(int n, int a, int b, int sr, int sc) {

    vector<vector<ll>> res(n - sr + 1, vector<ll>(n - sc + 1, inf));

    res[0][0] = 0;
    for(int i = 0; i < n - sr + 1; i++) {
        for(int j = 0; j < n - sc + 1; j++) {
            if(i) {
                res[i][j] = min(res[i][j], res[i-1][j] + gcd(i + sr, a) + gcd(j + sc, b));
            }
            if(j) {
                res[i][j] = min(res[i][j], res[i][j-1] + gcd(i + sr, a) + gcd(j + sc, b));
            }
        }
    }

    return res[n - sr][n - sc];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b; cin >> n >> a >> b;
    
    vector<array<int,2>> path;
    int sr = n, sc = n;
    while(gcd(sr, a) > 1) sr--;
    while(gcd(sc, b) > 1) sc--;

    path.push_back({0, sr - 1});
    path.push_back({1, sc - 1});
    
    ll res = 2; //start at (1, 1)

    int row = 1, col = 1;
    for(auto [dir, cnt] : path) {
        for(int i = 0; i < cnt; i++) {
            if(dir == 0) {
                row++;
            } else {
                col++;
            }
            res += gcd(row, a);
            res += gcd(col, b);
        }
    }

    res += solve_slow(n, a, b, sr, sc);
    cout << res << '\n';

    // cout << "solve slow" << endl;
    // cout << solve_slow(n, a, b, 1, 1) << endl;

    return 0;
}
