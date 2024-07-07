#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<vector<ll>> rotate(vector<vector<ll>> mat) {
    ll n = mat.size();
    vector<vector<ll>> r(n,vector<ll>(n));
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            r[j][n-i-1] = mat[i][j];
        }
    }
    return r;
}

vector<vector<ll>> flip(vector<vector<ll>> mat) {
    int n = mat.size();
    vector flipped(n,vector<ll>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            flipped[i][n-j-1] = mat[i][j];
        }
    }
    return flipped;
}

vector<vector<ll>> getprefs(vector<vector<ll>> mat) {
    int n = mat.size();
    vector prefs(n + 1, vector<ll>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            prefs[i + 1][j + 1] = prefs[i][j+1] + prefs[i+1][j] - prefs[i][j] + mat[i][j];
        }
    }
    return prefs;
}

vector<vector<vector<ll>>> getdp(vector<vector<ll>> mat, int m) {
    int n = mat.size();
    vector dp(4,vector(n,vector<ll>(n)));

    auto prefs = getprefs(mat);
    for(int i = 1; i <= 3; i++) { //iterate through using squares 1-3
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                //set prev max
                if(r != 0) {
                    dp[i][r][c] = max(dp[i][r][c], dp[i][r-1][c]);
                }
                if(c != 0) {
                    dp[i][r][c] = max(dp[i][r][c], dp[i][r][c-1]);
                }
                //try putting square here
                if(r + 1 >= m && c + 1 >= m) {
                    //pm stores best square before
                    ll pm = 0;
                    if(r - m >= 0) {
                        pm = max(pm, dp[i-1][r-m][c]);
                    }
                    if(c - m >= 0) {
                        pm = max(pm, dp[i-1][r][c-m]);
                    }
                    r++;
                    c++;
                    ll v = prefs[r][c] - prefs[r-m][c] - prefs[r][c-m] + prefs[r-m][c-m];
                    r--;
                    c--;
                    dp[i][r][c] = max(dp[i][r][c], pm + v);
                }

            }
        }
    }
    return dp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    vector mat(n,vector<ll>(n));
    for(auto &x : mat) for(auto &y : x) cin >> y;
    ll res = 0;
    for(ll t = 0; t < 8; t++) {
        auto dp1 = getdp(mat,m);
        auto rotated = rotate(rotate(mat));
        auto dp2 = getdp(rotated,m);
        for(int row = -1; row < n; row++) {
            int row2 = n - row - 2;
            for(int i = 0; i < 3; i++) {
                ll dp1best = 0, dp2best = 0;
                if(row >= 0) {
                    dp1best = dp1[i][row][n-1];
                }
                if(row2 >= 0) {
                    dp2best = dp2[3 - i][row2][n-1];
                }
                res = max(res,dp1best + dp2best);
            }
        }

        mat = rotate(mat);
        if(t % 4 == 0) {
            mat = flip(mat);
        }
    }

    cout << res << '\n';

    return 0;
}