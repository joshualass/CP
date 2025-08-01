#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
    cout << (n + 1) / 3 << endl;

    array<vector<array<int,2>>, 2> res;
    array<vector<array<int,2>>, 2> ex;

    int p = 0;

    auto ask = [&](int u, int v) -> int {
        cout << "? " << u + 1 << " " << v + 1 << endl;
        int res; cin >> res;
        return res;
    };

    auto add_edge = [&]() -> int {
        if(p + 2 > n) return -1;
        int u = p, v = p + 1;
        p += 2;

        int res = ask(u, v);
        ex[res].push_back({u, v});
        return res;
    };

    int type = add_edge();
    array<int,2> cur = ex[type].back();
    ex[type].pop_back();

    while(1) {
        while(ex[type ^ 1].empty()) {
            int ok = add_edge();
            if(ok == -1) goto done;
        }
        
        if(p >= n) goto done;

        auto cur2 = ex[type ^ 1].back();
        ex[type ^ 1].pop_back();

        int nx = p++;
        int val = ask(cur[0], cur2[0]);
        int nx2;

        if(val == type) {
            nx2 = cur[1];
            res[type ^ 1].push_back(cur2);
        } else {
            nx2 = cur2[1];
            res[type].push_back(cur);
        }

        res[val].push_back({cur[0], cur2[0]});
        int nxval = ask(nx2, nx);

        type = nxval;
        cur = {nx2, nx};
    }

done: 

    res[type].push_back(cur);
    for(int i = 0; i < 2; i++) for(auto x : ex[i]) res[i].push_back(x);
    int idx = (res[0].size() > res[1].size() ? 0 : 1);

    // cout << "res[0] : " << res[0] << '\n';
    // cout << "res[1] : " << res[1] << '\n';

    assert(res[idx].size() >= (n + 1) / 3);

    cout << "!";
    for(int i = 0; i < (n + 1) / 3; i++) cout << " " << res[idx][i][0] + 1 << " " << res[idx][i][1] + 1;
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

/*
bro was lost!
*/

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

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

// struct pent {
//     array<int,5> nodes, edges;

//     pent(array<int,5> n, array<int,5> e) {
//         nodes = n;
//         edges = e;
//     }

//     vector<array<int,2>> get_type_edges(int type) {
//         auto start_idx = [&](int os) -> vector<array<int,2>> {
//             vector<array<int,2>> res;
//             set<int> vis;
//             for(int i = 0; i < 5; i++) {
//                 if(edges[(i + os) % 5] == type && vis.count((i+os)%5) == 0 && vis.count((i+os+1)%5)==0) {
//                     res.push_back({nodes[(i+os)%5], nodes[(i+os+1)%5]});
//                     vis.insert((i+os)%5);
//                     vis.insert((i+os+1)%5);
//                 }
//             }
//             // cout << "res : " << res << '\n';
//             return res;
//         };
//         vector<array<int,2>> res = start_idx(0);
//         for(int i = 0; i < 5; i++) {
//             if(start_idx(i).size() > res.size()) res = start_idx(i);
//         }
//         return res;
//     }

//     int type_cnt(int type) {
//         return get_type_edges(type).size();
//     }
// };

// void solve() {
    
//     int n; cin >> n;

//     int k = INT_MAX;
//     for(int p = 0; p * 5 <= n; p++) {
//         int left = n - p * 5;
//         int bars = left / 2;
//         if(left & 1) {
//             if(p >= bars) {
//                 cout << "p0 : " << p << " c : " << (p * 3 + bars + 1) / 2 << '\n';
//                 k = min(k, (p * 3 + bars + 1) / 2);
//             } else {
//                 cout << "p0 : " << p << " c : " << p + bars << '\n';
//                 k = min(k, p + bars);
//             }
//         } else {
//             int t = 0;
//             if(bars >= 2) {
//                 t++;
//                 bars -= 2;
//             }
//             if(p >= bars) {
//                 cout << "p0 : " << p << " c : " << t + (p * 3 + bars + 1) / 2 << '\n';
//                 k = min(k, t + (p * 3 + bars + 1) / 2);
//             } else {
//                 cout << "p0 : " << p << " c : " << t + p + bars << '\n';
//                 k = min(k, t + p + bars);
//             }
//         }
//     }

//     cout << k << endl;

//     // cout << "p : " << p << " bars : " << bars << '\n';

//     auto query = [&](int i, int j) -> int {
//         cout << "? " << i + 1 << " " << j + 1 << endl;
//         int t; cin >> t;
//         return t;
//     };

//     array<vector<array<int,2>>,2> pairings = {};
//     vector<pent> pents;
//     array<int,2> type_cnts = {0,0};
//     int r = n -1;

//     for(int i = 0; i + 1 <= r; i += 2) {
//         pairings[query(i,i+1)].push_back({i,i+1});
//         if(pairings[0].size() && pairings[1].size() && i + 2 <= r) {
//             array<int,5> b = {pairings[0].back()[0], pairings[0].back()[1], pairings[1].back()[0], pairings[1].back()[1], r};
//             // cout << "b : " << b << '\n';
//             int c = query(b[1],b[2]);
//             int d = query(b[3], b[4]);
//             int e = query(b[4], b[0]);
//             pents.push_back(pent(b, {0,c,1,d,e}));
//             for(int j = 0; j < 2; j++) {
//                 type_cnts[j] += pents.back().type_cnt(j);
//                 // cout << "add to j : " << j << " add : " << pents.back().type_cnt(j) << '\n';    
//             }
//             pairings[0].pop_back();
//             pairings[1].pop_back();
//             r--;
//         }
//     }

//     for(int j = 0; j < 2; j++) {
//         if(type_cnts[j] + pairings[j].size() >= k) {
//             cout << "! ";
//             vector<array<int,2>> res;
//             for(pent p : pents) {
//                 vector<array<int,2>> toadd = p.get_type_edges(j);
//                 for(auto edge : toadd) res.push_back(edge);
//             }
//             for(auto edge : pairings[j]) res.push_back(edge);
//             for(int l = 0; l < k; l++) {
//                 cout << res[l][0] + 1 << " " << res[l][1] + 1 << " ";
//             }
//             cout << endl;
//             return;
//         }    
//     }
//     // assert(0);
//     cout << "n:"<<n<<"k:" << k << "tc0:" << type_cnts[0] << "tc1:" << type_cnts[1] << "p0:"<<pairings[0].size()<<"p1:"<<pairings[1].size()<<endl;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }