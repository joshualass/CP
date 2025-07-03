#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;
    vector<string> board(r);

    for(auto &x : board) cin >> x;

    vector<vector<int>> winning(r,vector<int>(c));

    for(int i = r - 1; i >= 0; i--) {
        for(int j = c - 1; j >= 0; j--) {
            if(board[i][j] == 'B') {
                winning[i][j] = 1;
            } else {
                if(i != r - 1) {
                    if(j != c - 1) {
                        if(winning[i+1][j+1] == 0) {
                            winning[i][j] = 1;
                        }
                    }
                    if(winning[i+1][j] == 0) {
                        winning[i][j] = 1;
                    }
                }
                if(j != c - 1) {
                    if(winning[i][j+1] == 0) {
                        winning[i][j] = 1;
                    }
                }
            }
        }
    }

    cout << (winning[0][0] ? "Alice" : "Bob") << '\n';

    return 0;
}