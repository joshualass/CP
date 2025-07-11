#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
mysteriously TLE/MLE/RE for the second variation

todo - figure out why this happens ... ?
*/
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, k; cin >> h >> w >> k;

    queue<array<int,3>> q;
    vector vis(h, vector<int>(w));

    ll res = 0;

    for(int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        r--; c--;
        q.push({r, c, 0});
    }

    vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};
    
    while(q.size()) {
        auto [x, y, d] = q.front();
        q.pop();

        if(vis[x][y]) continue;
        vis[x][y] = 1;
        res += d;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < h && ny >= 0 && ny < w && vis[nx][ny] == 0) {
                int adjwin = 0;
                for(int j = 0; j < 4; j++) {
                    int nnx = nx + dx[j], nny = ny + dy[j];
                    if(nnx >= 0 && nnx < h && nny >= 0 && nny < w && vis[nnx][nny]) adjwin++;
                }
                if(adjwin >= 2) {
                    q.push({nx, ny, d + 1});
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int h, w, k; cin >> h >> w >> k;

//     vector win(h, vector<int>(w)), dist(h, vector<int>(w));

//     ll res = 0;

//     vector<queue<array<int,2>>> q(h * w * 2);
//     vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};

//     int cnt = 0;

//     auto add_to_check = [&](int x, int y, int d) -> void {
//         cnt++;
//         assert(cnt < h * w * 10);
//         for(int i = 0; i < 4; i++) {
//             int nx = x + dx[i], ny = y + dy[i];
//             if(nx >= 0 && nx < h && ny >= 0 && ny < w && win[nx][ny] == 0) {
//                 q[d].push({nx, ny});
//             }
//         }
//     };

//     for(int i = 0; i < k; i++) {
//         int r, c; cin >> r >> c;
//         r--; c--;
//         win[r][c] = 1;
//         add_to_check(r, c, 1);
//     }

//     for(int tr = 0; tr < h * w * 2; tr++) {
//         if(q[tr].size() && tr > h * w + 3) assert(0);
//         while(q[tr].size()) {

//             auto [x, y] = q[tr].front();
//             q[tr].pop();

//             assert(x >= 0 && x < h && y >= 0 && y < w);

//             // cout << "x : " << x << " y : " << y << endl;

//             if(win[x][y]) continue;

//             int adjwin = 0;
//             for(int i = 0; i < 4; i++) {
//                 int nx = x + dx[i], ny = y + dy[i];
//                 if(nx >= 0 && nx < h && ny >= 0 && ny < w && win[nx][ny] && dist[nx][ny] < tr) {
//                     adjwin++;
//                 }
//             }

//             if(adjwin >= 2) {
//                 win[x][y] = 1;
//                 dist[x][y] = tr;
//                 res += tr;
//                 add_to_check(x, y, tr + 1);
//             }

//         }
//     }

//     cout << res << '\n';

//     return 0;
// }
