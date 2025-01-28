#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int n, m;
vector<int> dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
int dfs(int cur, vector<string>& g, set<array<int, 3>>& vs, vector<vector<bool>>& v, vector<vector<int>>& _c) {
    int r = cur / m, c = cur % m;
    // cout << "DFS : " << r << " " << c << "\n";
    int ans = 0;
    for(int i = 0; i < 4; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
        if(g[nr][nc] != '#') continue;
        if(v[nr][nc]) continue;
        v[nr][nc] = true;
        vs.insert({nr, nc, cur});
    }
    ans = max(ans, (int) vs.size());
    for(int x : _c[cur]) ans = max(ans, dfs(x, g, vs, v, _c));
    for(int i = 0; i < 4; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
        if(g[nr][nc] != '#') continue;
        if(vs.erase({nr, nc, cur})) {
            v[nr][nc] = false;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    vector<vector<int>> id(n, vector<int>(m));
    int idptr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            id[i][j] = idptr ++;
        }
    }
    vector<int> indeg(idptr, 0);
    vector<vector<int>> c(idptr);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == '.' || g[i][j] == '#') continue;
            if(g[i][j] == '<' && j != 0 && g[i][j - 1] != '.' && g[i][j - 1] != '#') c[id[i][j - 1]].push_back(id[i][j]);
            if(g[i][j] == '>' && j != m - 1 && g[i][j + 1] != '.' && g[i][j + 1] != '#') c[id[i][j + 1]].push_back(id[i][j]);
            if(g[i][j] == 'v' && i != n - 1 && g[i + 1][j] != '.' && g[i + 1][j] != '#') c[id[i + 1][j]].push_back(id[i][j]);
            if(g[i][j] == '^' && i != 0 && g[i - 1][j] != '.' && g[i - 1][j] != '#') c[id[i - 1][j]].push_back(id[i][j]);
        }
    }
    vector<int> p(idptr, -1);
    for(int i = 0; i < idptr; i++){
        for(int x : c[i]) indeg[x] ++, p[x] = i;
    }
    vector<vector<bool>> v(n, vector<bool>(m, false));
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(indeg[id[i][j]] != 0) continue;
            if(g[i][j] == '.' || g[i][j] == '#') continue;
            set<array<int, 3>> vs;
            ans = max(ans, dfs(id[i][j], g, vs, v, c));
        }
    }
    //loops
    vector<bool> iv(idptr, false);
    vector<bool> isloop(idptr, false);
    for(int i = 0; i < idptr; i++){
        vector<int> path;
        int ptr = i;
        while(!iv[ptr] && ptr != -1) path.push_back(ptr), iv[ptr] = true, ptr = p[ptr];
        if(ptr == -1) {
            continue;   //not a loop
        }
        reverse(path.begin(), path.end());
        while(path.size() != 0 && *path.rbegin() != ptr) {
            path.pop_back();
        }
        if(path.size() == 0) continue;
        set<array<int, 3>> vs;
        for(int x : path) {
            isloop[x] = true;
            int xr = x / m, xc = x % m;
            for(int j = 0; j < 4; j++){
                int nr = xr + dr[j], nc = xc + dc[j];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(g[nr][nc] != '#') continue;
                if(v[nr][nc]) continue;
                v[nr][nc] = true;
                vs.insert({nr, nc, -1});
            }
        }
        ans = max(ans, (int) vs.size());
        for(int x : path) {
            for(int nx : c[x]) {
                if(isloop[nx]) continue;
                ans = max(ans, dfs(nx, g, vs, v, c));
            }
        }
        for(int x : path) {
            int xr = x / m, xc = x % m;
            for(int j = 0; j < 4; j++){
                int nr = xr + dr[j], nc = xc + dc[j];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(g[nr][nc] != '#') continue;
                v[nr][nc] = false;
            }
        }
    }
    cout << ans << "\n";

    return 0;
}