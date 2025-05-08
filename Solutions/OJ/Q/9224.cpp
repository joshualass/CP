#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 1e5;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

int solve(vector<string> &a, int n, int m) {

    auto get_adj = [&](int x, int y) -> vector<array<int,2>> {
        assert(x >= 0 && x <= n && y >= 0 && y <= m);
        vector<array<int,2>> res;
        if(x < n && y < m) res.push_back({x, y});
        if(x && y < m) res.push_back({x - 1, y});
        if(x < n && y) res.push_back({x, y - 1});
        if(x && y) res.push_back({x - 1, y - 1});
        return res;
    };

    //1 if there exists path with no hosues
    vector pc(n + 1, vector(m + 1, vector(n + 1, vector<int>(m + 1))));
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            queue<array<int,2>> q;
            q.push({i, j});
            while(q.size()) {
                auto [x, y] = q.front();
                q.pop();
                if(pc[i][j][x][y]) continue;
                vector<array<int,2>> adj = get_adj(x, y);
                int ok = 1;
                for(auto [tx, ty] : adj) if(a[tx][ty] == '#') ok = 0;
                if(!ok) continue;
                pc[i][j][x][y] = 1;
                for(int k = 0; k < 4; k++) {
                    int tx = x + dx[k], ty = y + dy[k];
                    if(tx >= 0 && tx <= n && ty >= 0 && ty <= m) q.push({tx, ty});
                }
            }
        }
    }

    //1 if they share a corner and there exists a path 
    vector pc1(n + 1, vector(m + 1, vector(n + 1, vector<int>(m + 1))));

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            //catty corner + 1 + 1
            int ni = i + 1, nj = j + 1;
            if(ni <= n && nj <= m) {
                vector<array<int,2>> s = {{i - 1, j}, {i, j - 1}};
                vector<array<int,2>> t = {{ni + 1, nj}, {ni, nj + 1}};
                for(auto [sx, sy] : s) {
                    for(auto [tx, ty] : t) {
                        if(sx >= 0 && sy >= 0 && sx <= n && sy <= m && tx >= 0 && ty >= 0 && tx <= n && ty <= m) {
                            if(pc[sx][sy][tx][ty]) {
                                // if(i == 2 && j == 3) {
                                //     cout << "sx : " << sx << " sy : " << sy << '\n';
                                //     cout << "tx : " << tx << " ty : " << ty << '\n';
                                // }
                                pc1[i][j][ni][nj] = 1;
                                pc1[ni][nj][i][j] = 1;
                            }
                        }
                    }
                }
            }
            ni = i - 1, nj = j + 1;
            if(ni >= 0 && nj <= m) {
                vector<array<int,2>> s = {{i + 1, j}, {i, j - 1}};
                vector<array<int,2>> t = {{ni - 1, nj}, {ni, nj + 1}};
                for(auto [sx, sy] : s) {
                    for(auto [tx, ty] : t) {
                        if(sx >= 0 && sy >= 0 && sx <= n && sy <= m && tx >= 0 && ty >= 0 && tx <= n && ty <= m) {
                            if(pc[sx][sy][tx][ty]) {
                                pc1[i][j][ni][nj] = 1;
                                pc1[ni][nj][i][j] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    vector vis(n + 1, vector<int>(m + 1, -1));
    priority_queue<array<int,5>, vector<array<int,5>>, greater<array<int,5>>> pq;
    pq.push({a[0][0] == '#', 0, 0, -1, -1});

    while(pq.size()) {
        auto [d, x, y, px, py] = pq.top();
        pq.pop();
        if(vis[x][y] != -1) continue;
        // cout << "x : " << x << " y : " << y << " px : " << px << " py : " << py << " d : " << d << endl;
        vis[x][y] = d;

        //try all directions
        for(int k = 0; k < 4; k++) {
            int tx = x + dx[k], ty = y + dy[k];
            if(tx >= 0 && tx <= n && ty >= 0 && ty <= m) {
                // cout << "tx : " << tx << " ty : " << ty << endl;
                vector<array<int,2>> nx_path = get_adj(tx, ty);
                set<array<int,2>> snx_path(nx_path.begin(), nx_path.end());
                vector<array<int,2>> cadj = get_adj(x, y);
                for(auto c : cadj) snx_path.erase(c);
                int add = 0;
                for(auto [nxx, nxy] : snx_path) {
                    // cout << "nxx : " << nxx << " nxy : " << nxy << endl;
                    add += a[nxx][nxy] == '#';
                }
                if(x == 2 && y == 4 && tx == 3 && y == 4) {
                    // cout << " add : " << add << endl;
                }
                pq.push({d + add, tx, ty, x, y});
            }
        }

        // cout << "here" << endl;

        for(int tx = 0; tx <= n; tx++) {
            for(int ty = 0; ty <= m; ty++) {
                // cout << " tx : " << tx << " ty : " << ty << endl;
                if(pc1[x][y][tx][ty]) {
                    pq.push({d + 1, tx, ty, x, y});
                }
            }
        }
    }

    // for(int i = 0; i <= n; i++) {
    //     for(int j = 0; j <= m; j++) {
    //         cout << vis[i][j] << " \n"[j == m];
    //     }
    // }

    // cout << vis[n][m] << '\n';

    return vis[n][m];


    // auto relax = [&]() -> void {
    //     //relax 0 eviction paths
    //     vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
    //     for(int i = 0; i <= n; i++) {
    //         for(int j = 0; j <= m; j++) {
    //             vector<array<int,2>> in;
    //             queue<array<int,2>> q;
    //             q.push({i, j});
    //             int lo = inf;
    //             while(q.size()) {
    //                 auto [nx, ny] = q.front();
    //                 q.pop();

    //                 vector<array<int,2>> adj = get_adj(nx, ny);
    //                 int ok = 1;
    //                 for(auto [tx, ty] : adj) if(a[tx][ty] == '#') ok = 0;
    //                 if(vis[nx][ny] || ok == 0) continue;

    //                 vis[nx][ny] = 1;
    //                 in.push_back({nx, ny});
    //                 lo = min(lo, dp[nx][ny]);
    //                 for(int k = 0; k < 4; k++) {
    //                     int tx = nx + dx[k], ty = ny + dy[k];
    //                     if(tx >= 0 && tx <= n && ty >= 0 && ty <= m) q.push({tx, ty});
    //                 }
    //             }
    //             for(auto [nx, ny] : in) dp[nx][ny] = lo;
    //         }
    //     }
    //     //relax adj paths
    //     for(int i = 0; i <= n; i++) {
    //         for(int j = 0; j <= m; j++) {
    //             for(int k = 0; k < 4; k++) {
    //                 int tx = i + dx[k], ty = j + dy[k];
    //                 if(tx >= 0 && tx <= n && ty >= 0 && ty <= m) {
    //                     vector<array<int,2>> ij_adj = get_adj(i, j);
    //                     set<array<int,2>> sij_adj(ij_adj.begin(), ij_adj.end());
    //                     vector<array<int,2>> tadj = get_adj(tx, ty);
    //                     for(auto tadje : tadj) sij_adj.erase(tadje);
    //                     int add = 0;
    //                     for(auto [ijx, ijy] : sij_adj) {
    //                         add += a[ijx][ijy] == '#';
    //                     }
    //                     dp[i][j] = min(dp[i][j], dp[tx][ty] + add);
    //                 }
    //             }
    //         }
    //     }
    // };

    // dp[0][0] = a[0][0] == '#';
    // for(int i = 0; i < (n + 1) * (m + 1) * 2; i++) relax();
    // cout << dp[n][m] << '\n';
}

int solveslow(vector<string> &a, int n, int m) {

    vector<array<int,2>> b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '#') b.push_back({i, j});
        }
    }

    // cout << "a\n";
    // for(auto x : a) cout << x << '\n';

    auto get_adj = [&](int x, int y) -> vector<array<int,2>> {
        assert(x >= 0 && x <= n && y >= 0 && y <= m);
        vector<array<int,2>> res;
        if(x < n && y < m) res.push_back({x, y});
        if(x && y < m) res.push_back({x - 1, y});
        if(x < n && y) res.push_back({x, y - 1});
        if(x && y) res.push_back({x - 1, y - 1});
        return res;
    };

    int res = n * m;
    for(int i = 0; i < 1 << b.size(); i++) {
        auto c = a;
        for(int j = 0; j < b.size(); j++) {
            if((i >> j) & 1) c[b[j][0]][b[j][1]] = '.';
        }
        // cout << "c\n";
        // for(auto x : c) cout << x << '\n';

        vector vis(n + 1, vector<int>(m + 1));
        queue<array<int,2>> q;
        q.push({0, 0});
        while(q.size()) {
            auto [x, y] = q.front();
            q.pop();
            if(vis[x][y]) continue;
            vis[x][y] = 1;
            vector<array<int,2>> adj = get_adj(x, y);
            int ok = 1;
            for(auto [tx, ty] : adj) if(c[tx][ty] == '#') ok = 0;
            if(!ok) continue;
            // cout << "x : " << x << " y : " << y << " try nx\n";
            for(int k = 0; k < 4; k++) {
                int tx = x + dx[k], ty = y + dy[k];
                if(tx >= 0 && tx <= n && ty >= 0 && ty <= m) {
                    q.push({tx, ty});
                }
            }
        }
        if(vis[n][m]) res = min(res, __builtin_popcount(i));
        // for(auto x : vis) {
        //     for(auto y : x) cout << y << " ";
        //     cout << '\n';
        // }
        // cout << '\n';
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    cout << solve(a, n, m) << '\n';

    // cout << "slow : " << solveslow(a, n, m) << '\n';

    // int n = 6, m = 6;

    // for(int i = 0; i < 1000; i++) {
    //     if(i % 10 == 0) {
    //         cout << "i : " << i << endl;
    //     }
    //     ll p = rng() % (1LL << (n * m));
    //     while(__builtin_popcountll(p) > 20) p = rng() % (1LL << (n * m));

    //     vector<string> a(n, string(m, '.'));
    //     for(int j = 0; j < n * m; j++) {
    //         if((p >> j) & 1) {
    //             a[j / m][j % m] = '#';
    //         }
    //     }

    //     int fast = solve(a, n, m);
    //     int slow = solveslow(a, n, m);
    //     if(fast != slow) {
    //         cout << "fast : " << fast << " slow : " << slow << '\n';
    //         for(auto x : a) cout << x << '\n';
    //         return 0;
    //     }
    // }

    // cout << "All clear!\n";


    return 0;
}
