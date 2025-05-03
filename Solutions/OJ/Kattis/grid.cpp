#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    queue<array<int,3>> q;
    vector<vector<int>> vis(n, vector<int>(m, -1));
    q.push({0,0,0});
    while(q.size()) {
        auto [x, y, dist] = q.front();
        q.pop();
        if(vis[x][y] != -1) continue;
        vis[x][y] = dist;
        for(int i = 0; i < 4; i++) {
            int jmp = a[x][y] - '0';
            int nx = x + dx[i] * jmp, ny = y + dy[i] * jmp;
            if(nx >= 0 && nx < n && ny >= 0 && ny < m) q.push({nx, ny, dist + 1});
        }
    }

    cout << vis.back().back() << '\n';

    return 0;
}
