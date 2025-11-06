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

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n), c(n);
    for(ll &x : a) cin >> x;
    for(ll &x : c) cin >> x;

    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;

    //let dp[i] store the minimum cost so that the prefix up to 
    //i does not contain drops and element a[i] is not changed. 
    a.insert(a.begin(), 0);
    c.insert(c.begin(), 0);

    for(int i = 1; i <= n; i++) {
        ll best = 1e18;
        ll cur = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(a[j] <= a[i]) {
                best = min(best, dp[j] + cur);
            }
            cur += c[j];
        }
        dp[i] = best;
    }

    // cout << "dp : " << dp << '\n';

    ll res = LLONG_MAX, cur = 0;
    for(int j = n; j >= 0; j--) {
        res = min(res, dp[j] + cur);
        cur += c[j];
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