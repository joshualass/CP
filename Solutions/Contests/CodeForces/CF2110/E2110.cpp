#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
start anywhere with an odd count
do this greedily until there does not exist an odd dep, they should end up at the same, then do eulerian path

this algorithm works to find euler path or uses H algorithm

idea is to start on odd parity vertices if they exist. then just do euler tour strats once starting point is located. 
solvable with a dfs after determining the starting point. 
*/

/*
tc
3
6
0 0
1 0
2 0
3 0
0 1
1 1
9
0 0
1 0
0 1
1 1
2 2
3 2
2 3
3 3
0 3
8
0 0 
1 0
0 1
1 1
2 1
2 2
3 1
3 2

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;

    array<map<int, set<int>>,2> m;
    array<map<int, int>,2> cnts;
    map<array<int,2>, int> edge_idx;

    for(int i = 0; i < n; i++) {
        int v, p; cin >> v >> p;
        m[0][v].insert(p);
        m[1][p].insert(v);
        cnts[0][v]++;
        cnts[1][p]++;
        edge_idx[{v, p}] = i;
    }

    vector<array<int,2>> odds;
    for(int i = 0; i < 2; i++) {
        for(auto [k, v] : cnts[i]) {
            if(v & 1) {
                odds.push_back({i, k});
            }
        }
    }

    // cout << "odds : " << odds << '\n';
    
    vector<int> se_edges;
    vector<array<int,2>> se_nodes;

    if(odds.size() == 0) {
        se_nodes.push_back({0, m[0].begin()->first});
    } else if(odds.size() == 2) {
        array<int,2> st = odds[0];
        array<int,2> end = odds[1];        

        auto dfs = [&](auto self, int i, int s) -> int {
            se_nodes.push_back({i, s});
            if(i == end[0] && s == end[1]) {
                return 1;
            }
            if(m[i][s].empty()) return 0;
            int t = *m[i][s].begin();
            m[i][s].erase(t);
            m[i ^ 1][t].erase(s);

            if(i == 0) {
                se_edges.push_back(edge_idx[{s, t}]);
            } else {
                se_edges.push_back(edge_idx[{t, s}]);
            }
            return self(self, i ^ 1, t);
        };

        if(!dfs(dfs, st[0], st[1])) {
            cout << "NO\n";
            return;
        }

    } else {
        cout << "NO\n";
        return;
    }

    // cout << "se_edges : " << se_edges << '\n';
    // cout << "se_nodes : " << se_nodes << '\n';

    vector<int> res;

    for(int i = 0; i < se_nodes.size(); i++) {

        vector<int> rev_res;
        
        auto dfs = [&](auto self, int i, int s) -> void {
            // cout << "dfs i : " << i << " s : " << s << '\n';
            if(m[i][s].empty()) return;
            while(m[i][s].size()) {
                int t = *m[i][s].begin();
                m[i][s].erase(t);
                m[i ^ 1][t].erase(s);
                self(self, i ^ 1, t);
                if(i == 0) {
                    rev_res.push_back(edge_idx[{s, t}]);
                } else {
                    rev_res.push_back(edge_idx[{t, s}]);
                }
            }
        };

        dfs(dfs, se_nodes[i][0], se_nodes[i][1]);

        reverse(rev_res.begin(), rev_res.end());
        for(int x : rev_res) res.push_back(x);

        if(i < se_edges.size()) res.push_back(se_edges[i]);
    }
    
    // cout << "res : " << res << '\n';
    // cout << "se_nodes : " << se_nodes << '\n';

    if(res.size() == n) {
        cout << "YES\n";
        for(int i = 0; i < n; i++) cout << res[i] + 1 << " \n"[i == n - 1];
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// 2
// 6
// 0 0
// 1 0
// 2 0
// 3 0
// 0 1
// 1 1
// 9
// 0 0
// 1 0
// 0 1
// 1 1
// 2 2
// 3 2
// 2 3
// 3 3
// 0 3
// */

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
    
//     int n; cin >> n;
//     vector<array<int,3>> a(n);
    
//     array<map<int, set<array<int,3>>>, 2> m;
//     array<int,3> st = {};
//     int dir = 0;

//     for(int i = 0; i < n; i++) {
//         int x, y; cin >> x >> y;
//         array<int,3> v = {x, y, i};
//         m[0][x].insert(v);
//         m[1][y].insert(v);
//         st = v;
//         a[i] = {x, y, i};
//     }

//     for(int i = 0; i < n; i++) {
//         if((m[0][a[i][0]].size() % 2 == 1) && (m[1][a[i][1]].size() % 2 == 0)) {
//             st = a[i];
//             dir = 1;
//         }
//         if((m[0][a[i][0]].size() % 2 == 0) && (m[1][a[i][1]].size() % 2 == 1)) {
//             st = a[i];
//             dir = 0;
//         }
//     }

//     cout << "st : " << st << " dir : " << dir << '\n';

//     vector<int> c(n, -1);

//     auto dfs = [&](auto self, array<int,3> cur, int dir) -> pair<array<int,3>, int> {
//         m[0][cur[0]].erase(cur);
//         m[1][cur[1]].erase(cur);

//         if(m[dir][cur[dir]].empty()) return {cur, dir};

//         array<int,3> nx = *m[dir][cur[dir]].begin();
//         c[cur[2]] = nx[2];

//         auto [res, fdir] = self(self, nx, dir ^ 1);

//         if(m[dir][cur[dir]].size()) {
//             array<int,3> nx1 = *m[dir][cur[dir]].begin();
//             auto [nx2, nxdir] = self(self, nx1, dir ^ 1);

//             if(cur[dir] == nx2[dir] && dir == nxdir) {
//                 // cout << "hit!\n";
//                 c[cur[2]] = nx1[2];
//                 c[nx2[2]] = nx[2];
//             }

//         }
//         return {res, fdir};
//     };

//     // st = {2, 1, 4};
//     // dir = 1;

//     dfs(dfs, st, dir); 

//     vector<int> res;
//     int p = st[2];
//     while(c[p] != -1) {
//         res.push_back(p);
//         p = c[p];
//     }
//     res.push_back(p);

//     // cout << "c : " << c << '\n';
//     // cout << "res : " << res << '\n';

//     if(res.size() == n) {
//         cout << "YES\n";
//         for(int i = 0; i < n; i++) {
//             cout << res[i] + 1 << " \n"[i == n - 1];
//         }
//     } else {
//         cout << "NO\n";
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }