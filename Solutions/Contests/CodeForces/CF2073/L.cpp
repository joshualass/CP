#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c, n, p; cin >> r >> c >> n >> p;
    vector<vector<int>> board(r,vector<int>(c));
    vector<array<int,2>> coords(n);

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> board[i][j];
            board[i][j]--;
            if(board[i][j] != -1) {
                coords[board[i][j]] = {i,j};
            }
        }
    }

    vector<int> vis(n);

    vector<int> dx = {0,0,1,-1}, dy = {1,-1,0,0};

    for(int i = 0; i < p; i++) {
        int diff = p - i - 1;
        auto [x, y] = coords[i];
        for(int j = 0; j < 4; j++) {
            int nx = dx[j] + x, ny = dy[j] + y;
            if(nx >= 0 && nx < r && ny >= 0 && ny < c) {
                if(board[nx][ny] != -1 && board[nx][ny] + diff >= 0 && board[nx][ny] + diff < n) {
                    // cout << "i : " << i << " nx : " << nx << " ny : " << ny << " val : " << board[nx][ny] + diff << '\n';
                    vis[board[nx][ny] + diff] = 1;
                }
            }
        }
    }

    int cnt = count(vis.begin(), vis.end(), 1);
    cout << cnt << "/" << (n - 1) << '\n';

    return 0;
}