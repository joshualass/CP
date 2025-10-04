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

ll euclid(ll a, ll b, ll &x, ll &y) {
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto _solve = [&](ll b, ll rem, ll mod) -> ll {
        if(rem % gcd(b, mod)) return -1;
        ll g = gcd(b, gcd(rem, mod));
        b /= g;
        rem /= g;
        mod /= g;
        assert(gcd(b, mod) == 1);
        ll x, y;
        euclid(b, mod, x, y);
        ll inv = abs(x);
        ll res = ((lll) rem) % mod * ((lll) inv) % mod;
        return res;
    };

    auto solve = [&](ll a, ll b, ll ca, ll cb, ll n) -> ll {
        ll rem = n % a;
        ll x = _solve(b, rem, a);
        if(x == -1) return LLONG_MAX;
        ll start = x * b;
        if(start > n) return LLONG_MAX;

        n -= start;
        return n / a * ca + x * cb;
    };

    ll a, b, n; cin >> a >> b >> n;

    ll res = min(solve(a, b, 1, 3, n), solve(b, a, 3, 1, n));

    cout << (res == LLONG_MAX ? -1 : res) << '\n';

    return 0;
}