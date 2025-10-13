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
    vector<vector<int>> a(n, vector<int>(n));
    int on = 0;
    for(auto &x : a) for(auto &y : x) {
        cin >> y;
        on += y;
    }

    vector<int> dx = {0, 0, 0, 1, -1}, dy = {0, 1, -1, 0, 0};
    vector<int> vis(1 << (n * n));

    auto flip = [&](int b) -> void {
        int i = b / n, j = b % n;
        for(int k = 0; k < 5; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < n && nj >= 0 && nj < n) {
                on -= a[ni][nj];
                a[ni][nj] ^= 1;
                on += a[ni][nj];
            }
        }
    };

    int res = INT_MAX;

    auto dfs = [&](auto self, int cur, int z) -> void {
        // int hash = 0;
        // for(int i = 0; i < n * n; i++) {
        //     int row = i / n, col = i % n;
        //     if(a[row][col]) hash += 1 << i;
        // }
        // vis[hash] = 1;
        if(on == 0) {
            cout << "cur : " << cur << '\n';
            if(__builtin_popcount(cur) < __builtin_popcount(res)) {
                res = cur;
            }
            return;
        }
        for(int i = 0; i < z; i++) {
            flip(i);
            self(self, cur + (1 << i), i);
            flip(i);
        }
    };

    dfs(dfs, 0, n * n);

    cout << "Res : " << res << '\n';
    cout << "on : " << on << '\n';

    for(int b = 0; b < n * n; b++) {
        cout << ((res >> b) & 1) << " \n"[b % n == n - 1];
    }

    cout << "reachable count : " << accumulate(vis.begin(), vis.end(), 0) << " total : " << (1 << (n * n)) << '\n';

    return 0;
}


/*
no solution for a single corner ...

1 0 1 1 0
#########
1 0 0 0 0

1 0 0 0 1
#########
0 0 0 1 1

0 1 0 1 0 
#########
1 1 1 0 0

PATTERN
0 1 0 0 0
0 0 0 0 0
SOLUTION
0 1 0 1 0

0 1 0 1 0
0 0 0 0 0
NONE

1 0 0 0 1
0 0 0 0 0
NONE

PATTERN
0 0 1 0 1
0 0 0 0 0
SOLUTION
0 0 1 0 0

PATTERN
0 0 1 0 0
0 0 0 0 0
0 0 0 0 0
SOLUTION
1 1 0 0 0

PATTERN
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
SOLUTION/
1 1 0 0 0
*/