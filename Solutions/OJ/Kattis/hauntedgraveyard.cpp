#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool vis[30][30];
int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT
// int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h; cin >> w >> h;
    while(w != 0) {
        int g; cin >> g;
        vector<vector<bool>> gy(h,vector<bool>(w));
        for(int i = 0; i < g; i++) {
            int x, y; cin >> x >> y;
            gy[y][x] = 1;
        }
        vector<vector<array<int,3>>> hh(h,vector<array<int,3>>(w,{-1,-1,-1}));
        int e; cin >> e;
        for(int i = 0; i < e; i++) {
            int x1, y1, x2, y2, t; cin >> x1 >> y1 >> x2 >> y2 >> t;
            hh[y1][x1] = {y2, x2, t};
        }

        vector<vector<pair<int,int>>> adj(w * h);
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if((i != h - 1 || j != w - 1) && gy[i][j] == 0) { //no outgoing edges from the exit
                    if(hh[i][j][0] == -1) {
                        for(int k = 0; k < 4; k++) {
                            int newi = i + dx[k];
                            int newj = j + dy[k];
                            if(newi >= 0 && newi < h && newj >= 0 && newj < w && gy[newi][newj] == 0) {
                                adj[i * w + j].push_back({newi * w + newj, 1});
                            }
                        }
                    } else {
                        int newi = hh[i][j][0];
                        int newj = hh[i][j][1];
                        adj[i * w + j].push_back({newi * w + newj,  hh[i][j][2]});
                    }

                }
            }
        }
        vector<int> d(w * h, 1e9);
        d[0] = 0;
        for(int i = 0; i < w * h - 1; i++) {
            for(int j = 0; j < w * h; j++) {
                if(d[j] != 1e9) {
                    for(auto p : adj[j]) {
                        if(d[p.first] > d[j] + p.second) {
                            d[p.first] = d[j] + p.second;
                        }
                    }
                }
            }
        }

        bool c = 0;
        for(int j = 0; j < w * h; j++) {
            for(auto p : adj[j]) {
                if(d[j] != 1e9) {
                    for(auto p : adj[j]) {
                        if(d[p.first] > d[j] + p.second) {
                            c = 1;
                        }
                    }
                }
            }
        }
        // cout << "d : " << d << '\n';
        if(c) {
            cout << "Never\n";
        } else if(d.back() == 1e9) {
            cout << "Impossible\n";
        } else {
            cout << d.back() << '\n';
        }
        cin >> w >> h;
    }

    return 0;
}