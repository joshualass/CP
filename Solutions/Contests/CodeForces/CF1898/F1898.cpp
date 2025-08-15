#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

    int n, m; cin >> n >> m;
    vector<string> a(n);

    for(auto &x : a) cin >> x;

    int si = -1, sj = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == 'V') {
                si = i, sj = j;
            }
        }
    }

    vector v_dis(n, vector<int>(m, -1));

    queue<array<int, 3>> q;
    q.push({si, sj, 0});

    while(q.size()) {
        auto [i, j, step] = q.front();
        q.pop();
        if(v_dis[i][j] != -1) continue;
        v_dis[i][j] = step;
        for(int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] != '#') {
                q.push({ni, nj, step + 1});
            }
        }
    }

    int exit_cnt = 0;
    int min_dist = INT_MAX;

    queue<pair<array<int,3>, array<int,2>>> q2;

    auto acknowledge_exit = [&](int i, int j) -> void {
        if(a[i][j] != '#') {
            q2.push({{i, j, 0}, {i, j}});
        }
        if(v_dis[i][j] != -1) {
            exit_cnt++;
            min_dist = min(min_dist, v_dis[i][j]);
        }
    };

    for(int i = 1; i + 1 < n; i++) {
        acknowledge_exit(i, 0);
        acknowledge_exit(i, m - 1);
    }

    for(int j = 1; j + 1 < m; j++) {
        acknowledge_exit(0, j);
        acknowledge_exit(n - 1, j);
    }

    int ec_cnt = 0;
    for(auto x : a) ec_cnt += count(x.begin(), x.end(), '.');

    if(exit_cnt == 0) {
        cout << ec_cnt << '\n';
    } else if(exit_cnt == 1) {
        cout << ec_cnt - min_dist << '\n';
    } else {

        vector<vector<vector<pair<array<int,2>, int>>>> exit_vis(n, vector<vector<pair<array<int,2>, int>>>(m));

        while(q2.size()) {
            auto [info, parent] = q2.front();
            q2.pop();
            auto [i, j, step] = info;
            if(exit_vis[i][j].size() == 2) continue;
            if(exit_vis[i][j].size() == 1 && exit_vis[i][j][0].first == parent) continue;
            exit_vis[i][j].push_back({parent, step});
            for(int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if(ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] != '#') {
                    q2.push({{ni, nj, step + 1}, parent});
                }
            }
        }

        int res = INT_MAX;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(v_dis[i][j] != -1 && exit_vis[i][j].size() == 2) {
                    res = min(res, v_dis[i][j] + exit_vis[i][j][0].second + exit_vis[i][j][1].second);
                }
            }
        }

        cout << ec_cnt - res << '\n';

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}