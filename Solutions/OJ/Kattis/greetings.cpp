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

    // clock_t tStart = clock();

    ll n, k; cin >> n >> k;
    vector<array<ll,3>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<ll> pc(1 << n);
    for(ll i = 1; i < 1 << n; i++) {
        ll w = 0, h = 0;
        for(ll j = 0; j < n; j++) {
            if((i >> j) & 1) {
                w = max(w, a[j][0]);
                h = max(h, a[j][1]);
            }
        }
        ll cnt = 0;
        for(ll j = 0; j < n; j++) {
            if((i >> j) & 1) {
                cnt += a[j][2] * w * h;
                cnt -= a[j][0] * a[j][1] * a[j][2];
            }
        }
        // cout << "i : " << i << " cnt : " << cnt << '\n';
        pc[i] = cnt;
    }

    // cout << "pc : " << pc << '\n';

    vector<vector<ll>> dp(k + 1, vector<ll>(1 << n, 1e18));
    dp[0][0] = 0;

    for(int i = 1; i <= k; i++) {
        for(int j = 0; j < 1 << n; j++) {
            for(int ss = j; ; ss = (ss - 1) & j) {
                dp[i][j] = min(dp[i][j], dp[i-1][j ^ ss] + pc[ss]);
                if(!ss) break;
            }
        }
    }

    cout << dp[k][(1 << n) - 1] << '\n';

    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
