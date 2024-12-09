#include <iostream>
#include <vector>
#include <string>
using namespace std;
int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

bool can_swap_cycle(vector<string>& grid, int r1x, int r1y, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int ok = 0;
    auto dfs = [&](auto self, int i, int j, int pi, int pj) -> void {
        if(grid[i][j] == '#') return;
        if(visited[i][j]) { //found backedge; cycle detected
            ok = 1;
            return;
        }
        visited[i][j] = true;
        for(int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < n && nj >= 0 && nj < m && (ni != pi || nj != pj)) {
                self(self, ni, nj, i, j);
            }
        }
    };

    dfs(dfs, r1x, r1y, -1, -1);
    return ok;
}

bool can_swap_intersection(vector<string> &grid, int n, int m) {
    int ok = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] != '#') {
                int c = 0;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] != '#') {
                        c++;
                    }
                }
                if(c >= 3) ok = 1; //has 3 neighbors; possible here
            }
        }
    }
    return ok;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for(auto &x : grid) cin >> x;

    int r1x, r1y, r2x, r2y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '1') {
                r1x = i;
                r1y = j;
            } else if (grid[i][j] == '2') {
                r2x = i;
                r2y = j;
            }
        }
    }

    cout << (can_swap_cycle(grid, r1x, r1y, n, m) || can_swap_intersection(grid, n, m) ? "YES" : "NO") << '\n';

    return 0;
}