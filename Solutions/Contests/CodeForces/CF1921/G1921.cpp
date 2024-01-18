#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

int solve1(int n, int m, int range, vector<string> board, int i) {
    if(i & 1) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m / 2; k++) {
                swap(board[j][k], board[j][m-k-1]);
            }
        }
    }
    if((i >> 1) & 1) {
        for(int j = 0; j < n / 2; j++) {
            for(int k = 0; k < m; k++) {
                swap(board[j][k], board[n-j-1][k]);
            }
        }
    }

    vector<vector<int>> pref(n + 1, vector<int>(m + 1));

    for(int j = 0; j < n; j++) {
        for(int k = 0; k < m; k++) {
            pref[j+1][k+1] = pref[j][k+1] + pref[j+1][k] - pref[j][k] + (board[j][k] == '#');
        }
    }

    vector<vector<int>> diags(n,vector<int>(m)); 

    for(int startrow = 0; startrow < n + m - 1; startrow++) {
        for(int startcol = max(0, startrow - (n - 1)); startcol < m && startrow - startcol >= 0; startcol++) {
            int i = startrow - startcol;
            int j = startcol;

            if(i + 1 < n && j - 1 >= 0) {
                int col = pref[i+1][j+1] - pref[i+1][j];
                diags[i][j] = diags[i+1][j-1] + col;
            } else {
                diags[i][j] = pref[i+1][j+1];
            }

        }
    }

    // cout << "board :\n";
    // for(auto b : board) {
    //     cout << b << '\n';
    // }
    // cout << "diags :\n";
    // for(auto b : diags) {
    //     cout << b << '\n';
    // }

    int ans = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int tryi = i;
            int tryj = j + range;
            int val = -1;
            // cout << "i : " << i << " j : " << j;
            if(tryj < m) {
                val = diags[tryi][tryj];

            } else {
                int newj = m - 1;
                int newi = min(tryi + tryj - newj, n - 1);
                val = diags[newi][newj];
            }

            // cout << " val : " << val;
            if(j != 0) {
                // val -= diags[min(i+1,n-1)][j-1];
                // cout << " opt sub : " << diags[min(i+1,n-1)][j-1];
                val -= diags[min(i + range + 1, n - 1)][j-1];
                // cout << " opt sub : " << diags[min(i+range+1,n-1)][j-1];
            }
            val -= pref[i][min(m,j+range+1)];
            val += pref[i][j];
            // cout << " rect remove : " << pref[i][min(m,j+range)] - pref[i][j] << ' ' << " final val : " << val << '\n';
            // cout << "i : " << i << " j : " << j << " val : " << val << '\n';
            ans = max(ans, val);
        }
    }

    return ans;

    //approach is not quite correct ... but samples help show what doesn't work for this approach

    // vector<int> diags(n+m-1);

    // for(int startrow = 0; startrow < n + m - 1; startrow++) {
    //     if(startrow != 0) {
    //         diags[startrow] += diags[startrow-1];
    //     }
    //     for(int startcol = max(0, startrow - (n - 1)); startcol < m && startrow - startcol >= 0; startcol++) {
    //         diags[startrow] += board[startrow - startcol][startcol] == '#';
    //         // cout << "r : " << startrow - startcol << " c : " << startcol << '\n';
    //     }
    // }
    // // cout << "board :\n";
    // // for(auto b : board) {
    // //     cout << b << '\n';
    // // }
    // // cout << "diags : " << diags << '\n';

    // int ans = 0;

    // for(int j = 0; j < n; j++) {
    //     for(int k = 0; k < m; k++) {
    //         int diag = diags[min(n + m - 2, j + k + range)];
    //         int v1 = pref[min(n,j+1+range)][k];
    //         int v2 = pref[j][min(m,k+1+range)];
    //         int sub = pref[j][k];
    //         ans = max(ans, diag - (v1 + v2 - sub));
    //     }
    // }

    // return ans;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> board(n);
    for(string &s : board) cin >> s;
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        ans = max(ans, solve1(n,m,k,board,i));
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}