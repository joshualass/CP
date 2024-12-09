#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dp[50][50][50][51][3];
int dr[]{0,1,0};
int dc[]{-1,0,1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 50; j++) {
            for(int k = 0; k < 50; k++) {
                for(int l = 0; l < 51; l++) {
                    for(int m = 0; m < 3; m++) {
                        dp[i][j][k][l][m] = -1;
                    }
                }
            }
        }
    }

    int n, m, k; cin >> n >> m >> k;

    vector<vector<char>> mat(n,vector<char>(m));

    for(auto &x : mat) for(auto &y : x) cin >> y;
    vector<string> dict(k);
    for(auto &x : dict) cin >> x;

    queue<array<int,6>> q;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < k; j++) {
            if(mat[0][i] == dict[j][0]) {
                q.push({0,i,j,1,1,1});
            }
        }
    }

    int res = INT_MAX;

    while(q.size()) {
        auto [row, col, string_id, pos,d,dir] = q.front();
        q.pop();

        if(row == n - 1 && dict[string_id].size() == pos) {
            res = min(res,d);
        }

        if(dp[row][col][string_id][pos][dir] != -1) continue;
        dp[row][col][string_id][pos][dir] = d;

        // cout << "r : " << row << " c : " << col << " s_id : " << string_id << " idx : " << pos << " prevdir : " << dir << '\n';

        for(int i = 0; i < 3; i++) {
            if(dir != i + 2 && dir != i - 2) {
                int nr = row + dr[i], nc = col + dc[i];
                if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    if(dict[string_id].size() == pos) {
                        for(int j = 0; j < k; j++) {
                            if(mat[nr][nc] == dict[j][0]) {
                                q.push({nr,nc,j,1,d+1,i});
                            }
                        }
                    } else {
                        if(mat[nr][nc] == dict[string_id][pos]) {
                            q.push({nr,nc,string_id,pos+1,d+1,i});
                        }
                    }
                }
            }
        }

    }

    cout << (res == INT_MAX ? "impossible" : to_string(res)) << '\n';

    return 0;
}