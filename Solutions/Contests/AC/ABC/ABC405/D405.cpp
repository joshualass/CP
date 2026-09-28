#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    queue<array<int,3>> q;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == 'E') {
                q.push({i, j, -1});
            }
        }
    }

    while(q.size()) {
        auto [x, y, p] = q.front();
        q.pop();
        if(a[x][y] != 'E' && a[x][y] != '.') continue;
        if(p == 0) {
            a[x][y] = '^';
        } else if(p == 1) {
            a[x][y] = 'v';
        } else if(p == 2) {
            a[x][y] = '<';
        } else if(p == 3) {
            a[x][y] = '>';
        }
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == '.') q.push({nx,ny,i});
        }
    }
    for(auto x : a) cout << x << '\n';

    return 0;
}
