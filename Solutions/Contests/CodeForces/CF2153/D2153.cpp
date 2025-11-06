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

/*
observe that between every 3 pairs of cells, there must be a chop
*/

void solve() {

    int n; cin >> n;
    vector<int> a(n);    
    for(int &x : a) cin >> x;

    ll res = LLONG_MAX;
    auto _solve = [&]() {
        auto get_ops = [&](int l, int r) -> ll { // get # ops to make [l, r] equal
            vector<int> b;
            for(int i = l; i <= r; i++) b.push_back(a[i]);
            sort(b.begin(), b.end());
            ll ops = 0;
            int mid = b[b.size() / 2];
            for(int x : b) ops += abs(mid - x);
            return ops;
        };
        vector<ll> dp(n + 1, 1e18);
        dp[0] = 0;
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 2] + get_ops(i - 2, i - 1);
            if(i >= 3) {
                dp[i] = min(dp[i], dp[i - 3] + get_ops(i - 3, i - 1));
            }
        }
        res = min(res, dp[n]);
    };

    for(int i = 0; i < 3; i++) {
        _solve();
        rotate(a.begin(), a.begin() + 1, a.end());
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}