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

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll res = 0, cur = 0;
    for(ll x : a) {
        res += cur * x;
        cur += x;
    }

    // cout << res << '\n';

    ll sum = accumulate(a.begin(), a.end(), 0LL);
    ll sub = 0;

    auto dfs = [&](auto self, int i, int p) -> ll {
        ll s = a[i];
        for(int c : adj[i]) {
            if(c != p) {
                s += self(self, c, i);
            }
        }
        sub = min(sub, -1 * s * (sum - s));
        return s;
    };

    dfs(dfs, 0, -1);

    cout << res + sub << '\n';

    return 0;
}
