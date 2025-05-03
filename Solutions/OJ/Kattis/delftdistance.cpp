#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ld pi = acos(-1);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<array<ld,4>>> vis(n, vector<array<ld,4>>(m, array<ld,4>{-1,-1,-1,-1}));
    priority_queue<pair<ld,array<int,3>>, vector<pair<ld,array<int,3>>>, greater<pair<ld,array<int,3>>>> pq;

    pq.push({0, {0,0,0}});
    pq.push({0, {0,0,3}});

    ld sqdist = 10;
    ld cdist = 10 * pi / 4;

    while(pq.size()) {
        auto [dist, info] = pq.top();
        pq.pop();
        auto [x, y, pos] = info;


        if(vis[x][y][pos] != -1) continue;
        vis[x][y][pos] = dist;

        // cout << "pq size : " << pq.size() << '\n';
        // cout << "x : " << x << " y : " << y << " p : " << pos << " dist : " << dist << endl;

        ld used = (a[x][y] == 'O' ? cdist : sqdist);

        if(pos == 0) {
            // cout << "push pos 0\n";
            if(x) {
                // cout << "push0\n";
                pq.push({dist, {x - 1, y, 2}});
            }
            pq.push({dist + used, {x, y, 1}});
            pq.push({dist + used, {x, y, 3}});
            if(y) {
                pq.push({dist + 10, {x, y - 1, pos}});
            }
            if(y + 1 < m) {
                pq.push({dist + 10, {x, y + 1, pos}});
            }
        } else if(pos == 1) {
            // cout << "push pos 1\n";
            if(y + 1 < m) {
                pq.push({dist, {x, y + 1, 3}});
            }
            if(x) {
                pq.push({dist + 10, {x - 1, y, pos}});
            }
            if(x + 1 < n) {
                pq.push({dist + 10, {x + 1, y, pos}});
            }
            pq.push({dist + used, {x, y, 0}});
            pq.push({dist + used, {x, y, 2}});
        } else if(pos == 2) {
            // cout << "push pos 1\n";
            if(x + 1 < n) {
                pq.push({dist, {x + 1, y, 0}});
            }
            if(y) {
                pq.push({dist + 10, {x, y - 1, pos}});
            }
            if(y + 1 < m) {
                pq.push({dist + 10, {x, y + 1, pos}});
            }
            pq.push({dist + used, {x, y, 1}});
            pq.push({dist + used, {x, y, 3}});
        } else if(pos == 3) {
            // cout << "push pos 3\n";
            if(y) {
                pq.push({dist, {x, y - 1, 1}});
            }
            if(x) {
                pq.push({dist + 10, {x - 1, y, pos}});
            }
            if(x + 1 < n) {
                pq.push({dist + 10, {x + 1, y, pos}});
            }
            pq.push({dist + used, {x, y, 0}});
            pq.push({dist + used, {x, y, 2}});
        }
    }

    cout << fixed << setprecision(10) << 10 + min(vis[n - 1][m - 1][1], vis[n - 1][m - 1][2]) << '\n';

    return 0;
}
