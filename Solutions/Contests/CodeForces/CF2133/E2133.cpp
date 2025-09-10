#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
1
11
1 2
2 3
2 4
4 6
6 5
6 7
6 8
8 10
10 9
10 11
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<set<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<array<int,2>> ops;

    //0 - not chopped, 1 - chopped, 2 - must chop
    auto dfs = [&](auto self, int i, int p) -> int {
        int adj_cnt = i != 0;
        int must_chop = 0;
        for(int c : adj[i]) {
            if(c != p) {
                int val = self(self, c, i);
                if(val == 0) {
                    adj_cnt++;
                } else if(val == 2) {
                    must_chop = 1;
                }
            }
        }
        if(must_chop || adj_cnt >= 4 || adj_cnt == 3 && i == 0) {
            ops.push_back({2, i});

            return 1;
        } else if(adj_cnt == 3) {
            return 2;
        } else {
            return 0;
        }
    };

    dfs(dfs, 0, -1);

    for(auto [_, i] : ops) {
        for(int c : adj[i]) {
            adj[c].erase(i);
        }
        adj[i].clear();
    }

    for(int i = 0; i < n; i++) assert(adj[i].size() <= 2);

    vector<int> vis(n);

    auto dfs2 = [&](auto self, int i, int c) -> void {
        ops.push_back({1, i});
        vis[i] = 1;
        for(int ch : adj[i]) {
            if(ch != c) self(self, ch, i);
        }
    };

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0 && adj[i].size() <= 1) {
            dfs2(dfs2, i, -1);
        }
    }

    assert(ops.size() <= n * 5 / 4);

    cout << ops.size() << '\n';
    for(auto op : ops) {
        cout << op[0] << " " << op[1] + 1 << '\n';
    }

}

// void solve() {
    
//     int n; cin >> n;
//     vector<set<int>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int u, v; cin >> u >> v;
//         u--; v--;
//         adj[u].insert(v);
//         adj[v].insert(u);
//     }

//     priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
//     vector<int> adj3(n);
//     for(int i = 0; i < n; i++) {
//         if(adj[i].size() >= 3) pq.push({(int) adj[i].size(), i});
//         if(adj[i].size() == 3) {
//             for(int c : adj[i]) adj3[c]++;
//         }
//     }

//     // cout << "adj3 : " << adj3 << '\n';
//     vector<array<int,2>> ops;

//     auto chop = [&](int idx) -> void {
//         // cout << "idx : " << idx << endl;
//         for(int c : adj[idx]) {
//             if(adj[c].size() == 3) {
//                 for(int ch : adj[c]) {
//                     adj3[ch]--;
//                 }
//             }
//             adj[c].erase(idx);
//             if(adj[c].size() == 3) {
//                 for(int ch : adj[c]) {
//                     adj3[ch]++;
//                 }
//             }
//             if(adj[c].size() >= 3) pq.push({(int) adj[c].size(), c});
//         }
//         adj[idx].clear();
//         ops.push_back({2, idx});
//     };

//     while(pq.size()) {
//         auto [sz, i] = pq.top();
//         pq.pop();
//         // cout << "vis i : " << i << " with sz : " << sz << endl;
//         if(adj[i].size() != sz) continue;
//         if(sz == 3) {
//             int best = -1;
//             for(int c : adj[i]) {
//                 if(best == -1 || adj[c].size() > adj[best].size()) best = c;
//             }
//             chop(best);
//         } else {
//             chop(i);
//         }
//     }

//     for(int i = 0; i < n; i++) assert(adj[i].size() <= 2);

//     vector<int> vis(n);

//     auto dfs = [&](auto self, int i, int c) -> void {
//         ops.push_back({1, i});
//         vis[i] = 1;
//         for(int ch : adj[i]) {
//             if(ch != c) self(self, ch, i);
//         }
//     };

//     for(int i = 0; i < n; i++) {
//         if(vis[i] == 0 && adj[i].size() <= 1) {
//             dfs(dfs, i, -1);
//         }
//     }

//     assert(ops.size() <= n * 5 / 4);

//     cout << ops.size() << '\n';
//     for(auto op : ops) {
//         cout << op[0] << " " << op[1] + 1 << '\n';
//     }

// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}