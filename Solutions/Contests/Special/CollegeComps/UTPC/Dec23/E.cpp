#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dy [4] = {0,0,-1,1};
int dx [4] = {-1,1,-1,1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c, q; cin >> r >> c >> q;

    vector<vector<int>> baklavas(r,vector<int>(c));

    for(auto &x: baklavas) {
        for(auto &y : x) {
            cin >> y;
        }
    }
    vector<vector<int>> ans(r, vector<int>(c));
    for(int i = 0; i < q; i++) {
        int n, m; cin >> n >> m;
        n--; m--;
        queue<pair<int,int>> q;
        vector<vector<bool>> visited(r,vector<bool>(c));
        q.push({n,m});
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            if(visited[p.first][p.second]) continue;
            visited[p.first][p.second] = 1;

            for(int i = 0; i < 4; i++) {
                int newn = p.first + dx[i];
                int newm = p.second + dy[i];
                if(newn >= 0 && newn < r && newm >= 0 && newm < c && baklavas[newn][newm] <= baklavas[n][m]) {
                    q.push({newn, newm});
                }
            }
        }
        for(int R = 0; R < r; R++) {
            for(int C = 0; C < c; C++) {
                ans[R][C] += visited[R][C];
            }
        }
    }

    array<int,3> fenofinalform = {-1,-1,-1};
    for(int R = 0; R < r; R++) {
        for(int C = 0; C < c; C++) {
            if(ans[R][C] > fenofinalform[0]) {
                fenofinalform = {ans[R][C], R, C};
            }
        }
    }

    cout << fenofinalform[1] + 1 << " " << fenofinalform[2] + 1 << " " << fenofinalform[0] << '\n';

    return 0;
}