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

int a[16][16];
ll pc[1 << 16];
ll dp[1 << 16];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i < 1 << n; i++) {
        ll cost = 0;
        for(int j = 0; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                if(((i >> j) & 1) && ((i >> k) & 1)) {
                    cost += a[j][k];
                }
            }
        }
        pc[i] = cost;
    }

    fill(begin(dp), end(dp), -1e18);
    dp[0] = 0;

    for(int i = 1; i < 1 << n; i++) {
        for(int j = i; j; j = (j - 1) & i) {
            dp[i] = max(dp[i], dp[i ^ j] + pc[j]);
        }
    }

    cout << dp[(1 << n) - 1] << '\n';

    return 0;
}
