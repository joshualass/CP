#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int board[1000][1000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    queue<array<int,3>> q;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            board[i][j] = -1;
        }
    }

    auto add = [&](int i, int j, int d) -> void {
        if(board[i][j] == -1) {
            q.push({i, j, d});
            board[i][j] = d;
        }   
    };

    add(0, 0, 0);

    vector<int> dx = {1, 2, 2, 1, -1, -2, -2, -1}, dy = {2, 1, -1, -2, -2, -1, 1, 2};
    while(q.size()) {
        auto [x, y, d] = q.front();
        q.pop();
        for(int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n) add(nx, ny, d + 1);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << " \n"[j == n - 1];
        }
    }

    return 0;
}
