#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e18;
const ld pi = acos(-1);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n; cin >> m >> n;
    ld r; cin >> r;

    vector<vector<ld>> dist(m + 1, vector<ld>(n + 1, inf));
    vector<vector<int>> vis(m + 1, vector<int>(n + 1));

    priority_queue<pair<ld, array<int,2>>, vector<pair<ld, array<int,2>>>, greater<pair<ld, array<int,2>>>> pq;

    int ax, ay, bx, by; cin >> ax >> ay >> bx >> by;

    auto pushq = [&](int x, int y, ld d) -> void {
        if(d < dist[x][y]) {
            dist[x][y] = d;
            pq.push({d, {x, y}});
        }
    };

    pushq(ax, ay, 0);

    while(sz(pq)) {
        auto [d, info] = pq.top();
        pq.pop();
        auto [x, y] = info;
        if(vis[x][y]) continue;
        vis[x][y] = 1;
        
        ld rad = r / n * y;
        ld frac = 1.0 / 2.0 / m;
        ld rad_dist = rad * 2 * pi * frac;

        ld vert_dist = r / n;

        if(x > 0) {
            pushq(x - 1, y, d + rad_dist);
        }
        if(x + 1 <= m) {
            pushq(x + 1, y, d + rad_dist);
        }

        if(y + 1 <= n) {
            pushq(x, y + 1, d + vert_dist);
        }
        if(y) {
            pushq(x, y - 1, d + vert_dist);
        }
    }

    cout << fixed << setprecision(10) << dist[bx][by] << '\n';

    return 0;
}
