#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> dir(n,vector<int>(m,-1));

    for(int i = 0; i < n; i++) {
        dir[i][m-1] = 0;
    }
    k -= n;
    for(int i = 0; i + 1 < n; i += 2) {
        for(int j = m - 1; j > 0; j--) {
            if(k >= 2) {
                dir[i][j] = 3;
                dir[i][j-1] = 0;
                dir[i+1][j-1] = 1;
                k -= 2;
            }
        }
    }

    if(n & 1) {
        int i = n - 2;
        for(int j = 0; j + 1 < m; j += 2) {
            if(k >= 2) {
                dir[i][j] = 0;
                dir[i+1][j] = 1;
                dir[i+1][j+1] = 2;
                k -= 2;
            }
        }
    }

    // cout << "durr\n" << dir;

    if(k == 0) {
        vector<vector<char>> mat(2 * n + 1, vector<char>(2 * m + 1, '+'));

        for(int i = 1; i < 2 * n; i += 2) {
            for(int j = 2; j < 2 * m; j += 2) {
                mat[i][j] = '|';
            }
        }

        for(int i = 2; i < 2 * n; i += 2) {
            for(int j = 1; j < 2 * m; j += 2) {
                mat[i][j] = '-';
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int x = i * 2 + 1, y = j * 2 + 1;
                // cout << "i : " << i << " j : " << j << " x : " << x << " y : " << y << '\n';
                mat[x][y] = 'o';
                if(dir[i][j] == 0) {
                    mat[x+1][y] = '.';
                } else if(dir[i][j] == 1) {
                    mat[x][y+1] = '.';
                } else if(dir[i][j] == 2) {
                    mat[x-1][y] = '.';
                } else if(dir[i][j] == 3) {
                    mat[x][y-1] = '.';
                }
            }
        }
        mat[0][2 * m - 1] = 'S';
        mat[2 * n][2 * m - 1] = 'G';

        cout << "Yes\n";
        for(auto x : mat) {
            for(auto y : x) cout << y;
            cout << '\n';
        }

    } else {
        cout << "No\n";
    }


    return 0;
}