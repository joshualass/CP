#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c, x; cin >> r >> c >> x;
    vector<string> board(r);
    for(auto &x : board) cin >> x;
    vector<vector<char>> res(r * 100, vector<char>(c * 100));

    for(int i = 0; i < r * 100; i += r) {
        for(int j = 0; j < c * 100; j += c) {
            for(int k = 0; k < r; k++) {
                for(int l = 0; l < c; l++) {
                    res[i+k][j+l] = board[k][l];
                }
            }
        }
    }

    auto ismatch = [&](int cr, int cc) -> int {
        int ok = 1;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(res[i+cr][j+cc] != board[i][j]) ok = 0;
            }
        }
        return ok;
    };

    int cnt = 0;
    for(int i = 0; i + r <= r * 100; i++) {
        for(int j = 0; j + c <= c * 100; j++) {
            cnt += ismatch(i, j);
        }
    }

    auto toggle = [&](int cr, int cc) -> void {
        res[cr][cc] = (res[cr][cc] == '#' ? '.' : '#');
    };

    for(int i = r * 99; i >= 0; i--) {
        for(int j = c * 99; j >= 0; j--) {
            if(cnt > x) {
                if(ismatch(i, j)) {
                    cnt--;
                }
                if(res[i+r-1][j+c-1] == board[r-1][c-1]) toggle(i + r - 1, j + c - 1);
            }
        }
    }

    cout << r * 100 << " " << c * 100 << '\n';

    for(int i = 0; i < r * 100; i++) {
        for(int j = 0; j < c * 100; j++) {
            cout << res[i][j];
        }
        cout << '\n';
    }

    return 0;
}
