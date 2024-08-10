#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;



void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<vector<array<int,3>>> row(n-1), col(m - 1);

    for(int i = 0; i < k; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;

        if(y2 > y1) {
            row[x1].push_back({x1,y1,0});
            col[y1].push_back({x1,y1,0});
        } else {
            row[x1].push_back({x1,y2,1});
            col[y2].push_back({x1,y2,1});
        }
    }

    vector<int> sr(n-1,-1), sc(m-1,-1);

    bool ok = 1;

    for(int i = 0; i < n - 1; i++) {
        if(sr[i] == -1 && row[i].size()) {
            queue<array<int,3>> q; // {row,col,p}
            q.push(row[i][0]);
            while(q.size()) {
                auto [x, y, p] = q.front();
                q.pop();

                if(sr[x] != -1 && sc[y] != -1) {
                    if(p != (sr[x] ^ sc[y])) {
                        ok = 0;
                    }
                    continue;
                }
                if(sr[x] == -1 && sc[y] == -1) {
                    sr[x] = 0;
                    sc[y] = p;
                    for(array<int,3> c : row[x]) {
                        q.push(c);
                    }
                    for(array<int,3> c : col[y]) {
                        q.push(c);
                    }
                } else if(sr[x] == -1) {
                    sr[x] = p ^ sc[y];
                    for(array<int,3> c : row[x]) {
                        q.push(c);
                    }
                } else {
                    sc[y] = p ^ sr[x];
                    for(array<int,3> c : col[y]) {
                        q.push(c);
                    }
                }
            }
        }
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// Need to read better --- solution should work w/o condition 3
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto x : adj) {
//         for(auto y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

// void solve() {
//     int n, m, k; cin >> n >> m >> k;
//     vector<vector<vector<array<int,2>>>> adj(n,vector<vector<array<int,2>>>(m));
//     vector<vector<int>> vis(n,vector<int>(m,-1));

//     for(int i = 0; i < k; i++) {
//         int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
//         x1--; y1--; x2--; y2--;
//         adj[x1][y1].push_back({x2,y2});
//         adj[x2][y2].push_back({x1,y1});
//     }

//     int id = 0;
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             queue<array<int,2>> q;
//             bool found = 0;
//             q.push({i,j});
//             while(q.size()) {
//                 auto [x, y] = q.front();
//                 q.pop();

//                 if(vis[x][y] != -1) continue;
//                 vis[x][y] = id;
//                 found = 1;
                
//                 for(array<int,2> c : adj[x][y]) {
//                     if(vis[c[0]][c[1]] == -1) {
//                         q.push({c[0],c[1]});
//                     }
//                 }

//             }

//             if(found) id++;
//         }
//     }


//     // cout << "vis \n" << vis;

//     bool ok = 1;
//     for(int i = 0; i < n - 1; i++) {
//         for(int j = 0; j < m - 1; j++) {
//             if(vis[i][j] == vis[i+1][j+1] && vis[i+1][j] == vis[i][j+1]) {
//                 ok = 0;
//             }
//         }
//     }

//     cout << (ok ? "Yes" : "No") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string s = "2132132313213212321321312132132332132131";

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }