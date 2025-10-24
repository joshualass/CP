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
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> path;
    vector<int> in_path(n);

    auto dfs_path = [&](auto self, int i, int p) -> int {
        if(i == n - 1) {
            path.push_back(i);
            in_path[i] = 1;
            return 1;
        }
        int sub_path = 0;
        for(int c : adj[i]) {
            if(c != p) {
                sub_path |= self(self, c, i);
            }
        }
        if(sub_path) {
            path.push_back(i);
            in_path[i] = 1;
        }
        return sub_path;
    };

    dfs_path(dfs_path, 0, -1);

    vector<int> color(n);
    auto dfs2 = [&](auto self, int i, int p, int cur_color) -> void {
        color[i] = cur_color;
        if(!in_path[i]) {
            path.push_back(i);
        }
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, cur_color ^ 1);
            }
        }
    };

    dfs2(dfs2, 0, -1, 0);

    vector<vector<int>> ops;
    int p = 0;
    while(path.size() > 1) {
        int nx = path.back();
        if((color[nx] & 1) == p) {
            ops.push_back({1});
            p ^= 1;
        } else {
            ops.push_back({2, nx + 1});
            ops.push_back({1});
            p ^= 1;
            path.pop_back();
        }
    }

    cout << ops.size() << '\n';
    for(int i = 0; i < ops.size(); i++) {
        for(int j = 0; j < ops[i].size(); j++) {
            cout << ops[i][j] << " \n"[j == ops[i].size() - 1];
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}