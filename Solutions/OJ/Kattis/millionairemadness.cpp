#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

// int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m; 

    vector<vector<int>> mat(n,vector<int>(m));
    for(auto &x : mat) for(auto &y : x) cin >> y;

    vector<vector<bool>> vis(n,vector<bool>(m));

    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;

    pq.push({0,0,0});

    int ans = -1;
    while(pq.size()) {
        array<int,3> a = pq.top();
        pq.pop();
        if(vis[a[1]][a[2]]) continue;
        vis[a[1]][a[2]] = 1;
        if(a[1] == n - 1 && a[2] == m - 1) {
            ans = a[0];
            break;
        }

        for(int i = 0; i < 4; i++) {
            int tn = a[1] + dx[i];
            int tm = a[2] + dy[i];
            if(tn >= 0 && tn < n && tm >= 0 && tm < m && vis[tn][tm] == 0) {
                pq.push({max(a[0],mat[tn][tm] - mat[a[1]][a[2]]), tn, tm});
            }
        }

    }
    cout << ans << '\n';
    return 0;
}