#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
heuristic backtracking problem :)

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    vector<vector<bool>> vis(7, vector<bool>(7));

    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    vector<char> b = {'D', 'U', 'R', 'L'};
    int res = 0;
    int c = 0;

    string p;
    vector<string> paths;

    auto dfs = [&](auto self, int i, int j, int len) -> void {
        c++;

        if(len == 48) {
            if(i == 6 && j == 0) {
                res++;
                paths.push_back(p);
            }
            return;
        }

        if(i == 0) {
            for(int k = 0; k < j; k++) {
                if(vis[i][k] == 0) return;
            }
        }
        if(i == 6) { 
            for(int k = j + 1; k < 7; k++) {
                if(vis[i][k] == 0) return;
            }
        }
        if(j == 0) {
            for(int k = 0; k < i; k++) {
                if(vis[k][j] == 0) return;
            }   
        }
        if(j == 6) {
            for(int k = i - 1; k >= 0; k--) {
                if(vis[k][j] == 0) return;
            }
        }

        vector<int> need_go;

        for(int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && vis[ni][nj] == 0) {
                if(ni != 6 || nj) {
                    int cnt = 0;
                    for(int l = 0; l < 4; l++) {
                        int nni = ni + dx[l], nnj = nj + dy[l];
                        if(nni >= 0 && nni < 7 && nnj >= 0 && nnj < 7) {
                            cnt += vis[nni][nnj] == 0;
                        }
                    }
                    if(cnt == 0) return;
                    if(cnt == 1) need_go.push_back(k);
                }
            }
        }

        if(need_go.empty()) {
            for(int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                // if(ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && vis[ni][nj] == 0) {
                if(ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && vis[ni][nj] == 0 && (s[len] == b[k] || s[len] == '?')) {
                    vis[ni][nj] = 1;
                    p.push_back(b[k]);
                    self(self, ni, nj, len + 1);
                    p.pop_back();
                    vis[ni][nj] = 0;
                }
            }
        } else if(need_go.size() == 1) {
            int k = need_go[0];
            int ni = i + dx[k], nj = j + dy[k];
            // if(ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && vis[ni][nj] == 0) {
            if(ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && vis[ni][nj] == 0 && (s[len] == b[k] || s[len] == '?')) {
                vis[ni][nj] = 1;
                p.push_back(b[k]);
                self(self, ni, nj, len + 1);
                p.pop_back();
                vis[ni][nj] = 0;
            }
        }

    };

    vis[0][0] = 1;
    dfs(dfs, 0, 0, 0);

    cout << res << '\n';

    // cout << "c : " << c << '\n';

    return 0;
}