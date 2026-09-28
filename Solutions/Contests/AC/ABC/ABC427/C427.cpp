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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }


    int res = INT_MAX;
    for(int lhs = 0; lhs < 1 << n; lhs++) {
        vector<int> g(n);
        for(int i = 0; i < n; i++) {
            g[i] = ((lhs >> i) & 1);
        }
        // cout << "lhs : " << lhs << " n : " << n << " g : " << g << '\n';
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            // cout << "i : " << i << '\n';
            for(int to : adj[i]) {
                // cout << "to : " << to << '\n';
                if(g[i] == g[to]) cnt++;
            }
        }
        // cout << "lhs : " << lhs << " cnt : " << cnt << '\n';
        res = min(res, cnt);
    }

    cout << res << '\n';

    return 0;
}
