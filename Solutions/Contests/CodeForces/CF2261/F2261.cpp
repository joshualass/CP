#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

vector<string> test = {
"URLDUUDU",
"DRLDUUDU",
"LRLDUUDU",
"RRLDUUDU",
"ULRDUUDU",
"DLRDUUDU",
"LLRDUUDU",
"RLRDUUDU",
"URLDUDDU",
"DRLDUDDU",
"LRLDUDDU",
"RRLDUDDU",
"ULRDUDDU",
"DLRDUDDU",
"LLRDUDDU",
"RLRDUDDU",
"DLRLUDDU",
"DRLRUDDU",
"URLDULDU",
"DRLDULDU",
"LRLDULDU",
"RRLDULDU",
"ULRDULDU",
"DLRDULDU",
"LLRDULDU",
"RLRDULDU",
"URLDURDU",
"DRLDURDU",
"LRLDURDU",
"RRLDURDU",
"ULRDURDU",
"DLRDURDU",
"LLRDURDU",
"RLRDURDU",
"URLUDUUD",
"DRLUDUUD",
"LRLUDUUD",
"RRLUDUUD",
"ULRUDUUD",
"DLRUDUUD",
"LLRUDUUD",
"RLRUDUUD",
"ULRLDUUD",
"URLRDUUD",
"URLUDDUD",
"DRLUDDUD",
"LRLUDDUD",
"RRLUDDUD",
"ULRUDDUD",
"DLRUDDUD",
"LLRUDDUD",
"RLRUDDUD",
"URLUDLUD",
"DRLUDLUD",
"LRLUDLUD",
"RRLUDLUD",
"ULRUDLUD",
"DLRUDLUD",
"LLRUDLUD",
"RLRUDLUD",
"URLUDRUD",
"DRLUDRUD",
"LRLUDRUD",
"RRLUDRUD",
"ULRUDRUD",
"DLRUDRUD",
"LLRUDRUD",
"RLRUDRUD",
"UDURLURL",
"DDURLURL",
"LDURLURL",
"RDURLURL",
"UUDRLURL",
"DUDRLURL",
"LUDRLURL",
"RUDRLURL",
"UDURLDRL",
"DDURLDRL",
"LDURLDRL",
"RDURLDRL",
"UUDRLDRL",
"DUDRLDRL",
"LUDRLDRL",
"RUDRLDRL",
"UDURLLRL",
"DDURLLRL",
"LDURLLRL",
"RDURLLRL",
"UUDRLLRL",
"DUDRLLRL",
"LUDRLLRL",
"RUDRLLRL",
"RUDULRRL",
"RDUDLRRL",
"UDURLRRL",
"DDURLRRL",
"LDURLRRL",
"RDURLRRL",
"UUDRLRRL",
"DUDRLRRL",
"LUDRLRRL",
"RUDRLRRL",
"UDULRULR",
"DDULRULR",
"LDULRULR",
"RDULRULR",
"UUDLRULR",
"DUDLRULR",
"LUDLRULR",
"RUDLRULR",
"UDULRDLR",
"DDULRDLR",
"LDULRDLR",
"RDULRDLR",
"UUDLRDLR",
"DUDLRDLR",
"LUDLRDLR",
"RUDLRDLR",
"LUDURLLR",
"LDUDRLLR",
"UDULRLLR",
"DDULRLLR",
"LDULRLLR",
"RDULRLLR",
"UUDLRLLR",
"DUDLRLLR",
"LUDLRLLR",
"RUDLRLLR",
"UDULRRLR",
"DDULRRLR",
"LDULRRLR",
"RDULRRLR",
"UUDLRRLR",
"DUDLRRLR",
"LUDLRRLR",
"RUDLRRLR"
};

void work() {

    int use_lo = 0;
    int use_hi = 1;
    vector<vector<string>> boards;

    const int n = 3;
    vector<string> cur(n, string(n, '1'));

    auto dfs = [&](auto self, vector<string> cur, int row, int col, int use) -> void {
        // cout << "row : " << row << " col : " << col << endl;
        if(row == n) {
            if(use_lo <= use && use <= use_hi) {
                boards.push_back(cur);
            }
            return;
        }
        self(self, cur, row + (col == n - 1), (col + 1) % n, use);
        if(left) {
            cur[row][col] = '0';
            self(self, cur, row + (col == n - 1), (col + 1) % n, use + 1);
        }
    };

    dfs(dfs, cur, 0, 0, 0);
   
    int len = n * n + 1 - use_lo;
    for(int i = 0; i < 1 << (len * 2); i++) {
        string s = "";
        for(int j = 0, t = i; j < len; j++) {
            int x = t % 4;
            if(x == 0) s.push_back('U');
            if(x == 1) s.push_back('D');
            if(x == 2) s.push_back('L');
            if(x == 3) s.push_back('R');
            t /= 4;
        }
        // s[2] = 'D';
        // s[3] = 'D';
        // s[6] = 'R';
        // s[9] = 'R';
        // s[2] = 'D';
        // s[4] = 'R';
        // s[6] = 'D';
        // s[9] = 'R';
    // for(string s : test) {
        vector<vector<int>> vis(n, vector<int>(n, -1));
        for(int j = 0; j < sz(boards); j++) {
            auto board = boards[j];
            int x0 = 0, y0 = 0, x1 = n, y1 = n;
            for(int k = 0; k < 2 * n - 2; k++) {
                int sum = 0;
                for(int x = x0; x < x1; x++) {
                    for(int y = y0; y < y1; y++) {
                        sum += board[x][y] == '1';
                    }
                }
                assert(sum < sz(s));
                char c = s[sum];
                if(c == 'U') x0++;
                if(c == 'D') x1--;
                if(c == 'L') y0++;
                if(c == 'R') y1--;
            }
            if(x0 + 1 == x1 && y0 + 1 == y1) {
                vis[x0][y0] = j;
            }
        }
        int allg = 1;
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(vis[j][k] == -1) {
                    allg = 0;
                } else {
                    cnt++;
                }
            }
        }
        int f = 0;
        for(int i = 0; i < n; i++) {
            int ok = 1;
            if(i != 1) {
                for(int j = 0; j < n; j++) {
                    if(vis[i][j] == -1) ok = 0;
                }
                if(ok) f = 1;
            }
        }
        // if(s.front() == 'U') {
        //     cout << "\"" << s << "\",\n";
        //     for(auto x : vis) {
        //         for(auto y : x) cout << y << " ";
        //         cout << '\n';
        //     }
        // }
        // if(allg) {
        // if(cnt >= 3) {
        if(f) {
            cout << "allg with s : " << s << endl;
            for(auto x : vis) {
                for(auto y : x) cout << y << " ";
                cout << '\n';
            }
            // for(int x = 0; x < n; x++) {
            //     for(int y = 0; y < n; y++) {
            //         cout << x << " " << y << endl;
            //         if(vis[x][y] == -1) {
            //             cout << "-1\n";
            //         } else {
            //             for(auto x : boards[vis[x][y]]) cout << x << endl;
            //             cout << endl;
            //         }
            //     }
            // }
            // return;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    work();

    // int n; cin >> n;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         vector<string> a(n, string(n, '0'));

    //         if(j == 0) {
    //             int left = 3;
    //             if(i != n - 1) {
    //                 a[i+1][0] = '1';
    //                 left--;
    //             }
    //             for(int k = 0; k < left; k++) {
    //                 a[k][1] = '1';
    //             }
    //         } else if(j == n - 1) {
    //             int left = 2;
    //             if(i != n - 1) {
    //                 a[i+1][n - 1] = '1';
    //                 left--;
    //             }
    //             for(int k = 0; k < left; k++) {
    //                 a[k][n - 2] = '1';
    //             }
    //         } else {
    //             int left = 3;
    //             if(i != n - 1) {
    //                 left--;
    //                 a[i+1][j] = '1';
    //             }
    //             a[0][j+1] = '1';
    //             left--;
    //             for(int k = 0; k < left; k++) {
    //                 a[k][j-1] = '1';
    //             }
    //         }
    //         for(string s : a) cout << s << '\n';
    //         cout << '\n';
    //     }
    // }

    // string res = "UDLR" + string(n * n + 1 - 4, 'L');
    // cout << res << '\n';

    return 0;
}
