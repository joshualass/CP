#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h, w; cin >> h >> w;

    vector<string> board(h);

    for(auto &x: board) cin >> x;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(board[i][j] == '.') {
                vector<bool> used(5);
                for(int k = 0; k < 4; k++) {
                    int newh = i + dy[k];
                    int neww = j + dx[k];
                    if(newh >= 0 && newh < h && neww >= 0 && neww < w && board[newh][neww] >= '1') {
                        used[board[newh][neww] - '1'] = true;
                    }
                }
                for(int k = 0; k < 5; k++) {
                    if(!used[k]) {
                        board[i][j] = '1' + k;
                    }
                }
            }
        }
    }

    for(auto x : board) cout << x << '\n';

    return 0;
}