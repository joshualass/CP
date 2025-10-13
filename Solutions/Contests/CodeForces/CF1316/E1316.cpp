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

    int n, p, K; cin >> n >> p >> K;

    vector<pair<int,vector<int>>> a(n, {0, vector<int>(p)});
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            cin >> a[i].second[j];
        }
    }

    sort(a.rbegin(), a.rend());

    vector<vector<ll>> dp(n + 1, vector<ll>(1 << p, -1e18));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < 1 << p; j++) {
            for(int k = 0; k < p; k++) {
                if(((j >> k) & 1) == 0) {
                    dp[i + 1][j + (1 << k)] = max(dp[i + 1][j + (1 << k)], dp[i][j] + a[i].second[k]);
                }
            }
            if(i - __builtin_popcount(j) < K) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + a[i].first);
            } else {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            }
        }
    }

    cout << dp[n][(1 << p) - 1] << '\n';

    return 0;
}
