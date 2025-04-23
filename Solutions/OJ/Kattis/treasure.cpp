#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<string> board(n);
    for(auto &x : board) cin >> x;

    int sx = -1, sy = -1, ex = -1, ey = -1;;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 'S') {
                sx = i;
                sy = j;
            }
            if(board[i][j] == 'G') {
                ex = i;
                ey = j;
            }
        }
    }

    queue<array<int,4>> q;
    q.push({sx, sy, k, 1});

    vector<vector<vector<int>>> vis(n, vector<vector<int>>(m, vector<int>(k + 1, -1)));
    while(q.size()) {
        auto [x, y, stm, d] = q.front();
        q.pop();
        if(vis[x][y][stm] != -1) continue;
        vis[x][y][stm] = d;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int cost = 0;
                switch(board[nx][ny]) {
                    case '.' : cost = 1; break;
                    case 'F' : cost = 2; break;
                    case 'M' : cost = 3; break;
                    case '#' : cost = k + 1; break;
                    case 'G' : cost = 1; break;
                    case 'S' : cost = 1; break;
                }
                if(stm - cost >= 0) q.push({nx, ny, stm - cost, d});
            }
        }
        q.push({x, y, k, d + 1});
    }

    int res = INT_MAX;

    for(int i = 0; i <= k; i++) {
        if(vis[ex][ey][i] != -1) res = min(res, vis[ex][ey][i]);
    }

    cout << (res == INT_MAX ? -1 : res) << '\n';

    return 0;
}
