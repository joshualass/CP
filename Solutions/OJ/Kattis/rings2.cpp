#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    queue<array<int,3>> q;
    vector<vector<int>> res(n, vector<int>(m,-1));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == '.') q.push({i,j,0});
        }
    }

    for(int i = 0; i < n; i++) q.push({i,0,1});
    for(int i = 0; i < n; i++) q.push({i,m-1,1});
    for(int i = 0; i < m; i++) q.push({0,i,1});
    for(int i = 0; i < m; i++) q.push({n-1,i,1});

    vector<int> dx = {0,0,-1,1}, dy = {-1,1,0,0};

    while(q.size()) {
        auto [x, y, t] = q.front();
        q.pop();
        if(res[x][y] != -1) continue;
        res[x][y] = t;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m) q.push({nx,ny,t+1});
        }
    }

    int maxlen = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) maxlen = max(maxlen, res[i][j]);
    if(maxlen >= 10) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(res[i][j] < 100) cout << '.';
                if(res[i][j] < 10) cout << '.';
                if(res[i][j]) cout << res[i][j];
                else cout << '.';
            }
            cout << '\n';
        }
    } else {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(res[i][j] < 10) cout << '.';
                if(res[i][j]) cout << res[i][j];
                else cout << '.';
            }
            cout << '\n';
        }
    }

    return 0;
}