#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

map<string,array<int,2>> m;

void solve() {
    string s; cin >> s;
    for(int i = 0; i < 9; i++) {
        if(s[i] == 'X') s[i] = '0';
        if(s[i] == 'O') s[i] = '1';
    }
    if(m.count(s)) {
        cout << m[s][0] << " " << m[s][1] << '\n';
    } else {
        cout << "-1 -1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto check_win = [](string board) -> int {

        for(int i = 0; i < 3; i++) {
            int ok = board[i*3] != '.';
            for(int j = 1; j < 3; j++) {
                if(board[i*3+j] != board[i*3]) {
                    ok = 0;
                }
            }
            if(ok) {
                return board[i*3] - '0';
            }
        }

        for(int i = 0; i < 3; i++) {
            int ok = board[i] != '.';
            for(int j = 1; j < 3; j++) {
                if(board[j * 3 + i] != board[i]) ok  = 0;
            }
            if(ok) {
                return board[i] - '0';
            }
        }
        int ok = board[0] != '.';
        for(int i = 1; i < 3; i++) {
            if(board[i * 3 + i] != board[0]) ok = 0;
        }
        if(ok) return board[0] - '0';

        ok = board[2] != '.';
        for(int i = 1; i < 3; i++) {
            if(board[2] != board[(i + 1) * 2]) ok = 0;
        }
        if(ok) return board[2] - '0';
        return -1;
    };

    auto dfs = [&](auto self, string board) -> void {
        if(m.count(board)) return;
        int cw = check_win(board);
        // cout << "board : " << board << " cw : " << cw << '\n';
        if(cw != -1) {
            if(cw == 0) {
                m[board] = {1,0};
            } else {
                m[board] = {0,1};
            }
            return;
        }
        int dc = count(board.begin(), board.end(), '.');
        m[board] = {0,0};
        if((9 - dc) % 2 == 0) {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(board[i*3+j] == '.') {
                        string nb = board;
                        nb[i*3+j] = '0';
                        self(self, nb);
                        if(m.count(nb)) {
                            for(int k = 0; k < 2; k++) {
                                m[board][k] += m[nb][k];
                            }
                        }
                    }
                }
            }
        } else {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(board[i*3+j] == '.') {
                        string nb = board;
                        nb[i*3+j] = '1';
                        self(self, nb);
                        if(m.count(nb)) {
                            for(int k = 0; k < 2; k++) {
                                m[board][k] += m[nb][k];
                            }
                        }
                    }
                }
            }
        }
    };

    dfs(dfs, string(9,'.'));

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}