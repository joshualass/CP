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
typedef __int128_t lll;
typedef long double ld;
using namespace std;

lll euclid(lll a, lll b, lll &x, lll &y) {
    if(!b) return x = 1, y = 0, a;
    lll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto _solve = [&](lll b, lll rem, lll mod) -> lll {
        if(rem % gcd(b, mod)) return -1;
        lll g = gcd((ll)b, gcd((ll)rem, (ll)mod));
        b /= g;
        rem /= g;
        mod /= g;
        assert(gcd(b, mod) == 1);
        lll x, y;
        euclid(b, mod, x, y);
        lll inv = (x < 0 ? -x : x);
        lll res = rem * inv % mod;
        return res;
    };

    auto solve = [&](lll a, lll b, lll ca, lll cb, lll n) -> lll {
        lll rem = n % a;
        lll x = _solve(b, rem, a);
        if(x == -1) return LLONG_MAX;
        lll start = x * b;
        if(start > n) return LLONG_MAX;

        n -= start;
        return n / a * ca + x * cb;
    };

    ll a, b, n; cin >> a >> b >> n;

    lll res = min(solve(a, b, 1, 3, n), solve(b, a, 3, 1, n));

    cout << (res == LLONG_MAX ? -1 : (ll) res) << '\n';

    return 0;
}
