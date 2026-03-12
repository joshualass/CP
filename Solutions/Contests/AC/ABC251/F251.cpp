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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n);
    vector<array<int,2>> res;

    auto dfs = [&](auto self, int i) -> void {
        vis[i] = 1;
        for(int c : adj[i]) {
            if(vis[c] == 0) {
                res.push_back({i, c});
                self(self, c);
            }
        }
    };

    dfs(dfs, 0);

    queue<int> q;
    vis.assign(n, 0);
    q.push(0);
    vis[0] = 1;
    while(q.size()) {
        int x = q.front();
        q.pop();
        for(int c : adj[x]) {
            if(vis[c] == 0) {
                q.push(c);
                vis[c] = 1;
                res.push_back({x, c});
            }
        }
    }

    for(auto x : res) {
        cout << x[0] + 1 << " " << x[1] + 1 << '\n';
    }

    return 0;
}
