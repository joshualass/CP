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

    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<array<int,2>> q;
    vector<int> vis(n,-1);
    vector<int> res(k);
    q.push({0, 0});
    vis[0] = 0;
    while(q.size()) {
        auto [node, dist] = q.front();
        q.pop();
        res[a[node]] = max(res[a[node]], dist);
        for(int to : adj[node]) {
            if(vis[to] == -1) {
                vis[to] = dist + 1;
                q.push({to, dist + 1});
            }
        }
    }

    for(int i = 0; i < k; i++) cout << res[i] << " \n"[i == k - 1];

    return 0;
}
