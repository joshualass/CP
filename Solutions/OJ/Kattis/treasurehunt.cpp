#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

map<char, array<int,2>> m = {
    {'E', {0, 1}},
    {'W', {0, -1}},
    {'N', {-1,0}},
    {'S', {1,0}}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;
    vector<string> board(r);
    for(auto &x : board) cin >> x;
    vector<vector<int>> vis(r, vector<int>(c));
    int cx = 0, cy = 0;
    int moves = 0;
    while(1) {
        if(cx < 0 || cx == r || cy < 0 || cy == c) {
            cout << "Out\n";
            return 0;
        }
        if(vis[cx][cy]) {
            cout << "Lost\n";
            return 0;
        }
        if(board[cx][cy] == 'T') {
            cout << moves << '\n';
            return 0;
        }
        vis[cx][cy] = 1;
        auto add = m[board[cx][cy]];
        cx += add[0], cy += add[1];
        moves++;
    }

    return 0;
}
