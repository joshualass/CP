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
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto get_farthest_node = [&](auto self, int i, int p, int d) -> array<int,2> {
        array<int,2> res = {i, d};
        for(int c : adj[i]) {
            if(c != p) {
                auto [ci, cd] = self(self, c, i, d + 1);
                if(cd > res[1]) {
                    res = {ci, cd};
                }
            }
        }
        return res;
    };

    auto [f1, d1] = get_farthest_node(get_farthest_node, 0, -1, 0);
    auto [f2, d2] = get_farthest_node(get_farthest_node, f1, -1, 0);

    vector<int> path;
    vector<int> in_path(n);
    
    auto dfs2 = [&](auto self, int i, int p) -> int {
        int f = (i == f2);
        for(int c : adj[i]) {
            if(c != p) {
                if(self(self, c, i)) {
                    f = 1;
                }
            }
        }
        if(f) {
            path.push_back(i);
            in_path[i] = 1;
        }
        return f;
    };

    dfs2(dfs2, f1, -1);

    array<int,3> res = {-1,-1,-1};

    for(int i = 0; i < n; i++) {
        if(in_path[i]) {
            int in = -1, out = -1;
            for(int c : adj[i]) {
                if(in_path[c]) in = c;
                if(!in_path[c]) out = c;
            }
            if(in != -1 && out != -1) {
                res = {in, i, out};
            }
        }
    }

    if(res[0] == -1) {
        cout << "-1\n";
    } else {
        cout << res[0] + 1 << " " << res[1] + 1 << " " << res[2] + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}