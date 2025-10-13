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

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> vis(n, vector<int>(n));
    vector<array<int,2>> ops;

    auto add = [&](int u, int v) -> bool {
        if(u > v) swap(u, v);
        if(vis[u][v] == 0) {
            vis[u][v] = 1;
            ops.push_back({u, v});
            return 1;
        }
        return 0;
    };

    for(int m = 2; ; m *= 2) {
        int f = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i % m != j % m) {
                    f |= add(i, j);
                }
            }
        }
        if(!f) break;
    }

    reverse(ops.begin(), ops.end());
    for(auto op : ops) {
        cout << op[0] + 1 << " " << op[1] + 1 << endl;
        int res; cin >> res;
        if(res) break;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}