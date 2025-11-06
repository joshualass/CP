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
    vector<vector<int>> a(2, vector<int>(n));
    for(auto &b : a) {
        for(auto &x : b) cin >> x;
    }

    vector<array<array<int,2>, 2>> dp(n + 1);

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 2; j++) {
            array<int,2> best = {INT_MIN, INT_MIN};
            int cur = 0;
            for(int take = 1; i - take >= 0 && take <= 4; take++) {
                cur += a[j][i - take];
                array<int,2> option = dp[i - take][j ^ 1];
                option[j] += cur;
                if(option[j] > best[j] || option[j] == best[j] && option[j ^ 1] < best[j ^ 1]) {
                    best = option;
                }
            }
            dp[i][j] = best;
        }
    }

    auto [near, mello] = dp[n][0];
    cout << near << " " << mello << '\n';

    return 0;
}
