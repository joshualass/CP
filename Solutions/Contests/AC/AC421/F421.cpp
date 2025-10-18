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

    int q; cin >> q;
    vector<vector<int>> queries;
    vector<vector<int>> g(q + 1);
    for(int i = 1; i <= q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x; cin >> x;
            g[x].push_back(i);
            queries.push_back({type, x});
        } else {
            int x, y; cin >> x >> y;
            queries.push_back({type, x, y});
        }
    }    

    vector<int> pos(q + 1, -1);
    int p = 0;

    auto dfs = [&](auto self, int i) -> void {
        pos[i] = p++;
        if(g[i].size()) {
            for(int j = g[i].size() - 1; j >= 0; j--) {
                self(self, g[i][j]);
            }
        }
    };

    dfs(dfs, 0);

    map<int,int> m;

    for(int i = 1; i <= q; i++) {
        auto query = queries[i - 1];
        if(query[0] == 1) {
            m[pos[i]] = i;
        } else {
            int x = query[1], y = query[2];
            int lo = pos[x], hi = pos[y];
            if(lo > hi) swap(lo, hi);
            ll res = 0;
            while(m.upper_bound(lo) != m.end() && m.upper_bound(lo)->first < hi) {
                auto [x, y] = *m.upper_bound(lo);
                m.erase(x);
                res += y;
            }
            cout << res << '\n';
        }
    }

    return 0;
}
