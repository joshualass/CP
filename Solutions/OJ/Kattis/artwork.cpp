#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e6;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;

    vector<vector<array<int,2>>> paints(q);
    vector<vector<int>> vis(n, vector<int>(m, -1));

    for(int i = 0; i < q; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        if(x1 == x2) {
            for(int j = min(y1, y2); j <= max(y1, y2); j++) {
                if(vis[x1][j] == -1) {
                    vis[x1][j] = i;
                    paints[i].push_back({x1,j});
                }
            }
        } else {
            for(int j = min(x1, x2); j <= max(x1, x2); j++) {
                if(vis[j][y1] == -1) {
                    vis[j][y1] = i;
                    paints[i].push_back({j, y1});
                }
            }
        }
    }

    vector<int> res(q);

    dsubuild(n * m);

    int wt = 0, merges = 0;

    auto get_id = [&](int x, int y) -> int {
        return x * m + y;
    };

    auto get_coord = [&](int id) -> array<int,2> {
        return {id / m, id % m};
    };

    auto add = [&](int x, int y) -> void {
        wt++;
        int id = get_id(x, y);
        vector<int> dx = {-1,1,0,0}, dy = {0,0,-1,1};
        vis[x][y] = -1;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && vis[nx][ny] == -1) {
                int nid = get_id(nx, ny);
                if(find(id) != find(nid)) {
                    merges++;
                    merge(id, nid);
                }
            }
        }

    };

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vis[i][j] == -1) {
                add(i,j);
            }
        }
    }

    for(int i = q - 1; i >= 0; i--) {
        res[i] = wt - merges;
        for(auto [x, y] : paints[i]) {
            add(x,y);
        }
    }

    for(int x : res) cout << x << '\n';

    return 0;
}
