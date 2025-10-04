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
try to not guess here

at each index i, we need to find the minimum of sum 1 - a[j] for j = i + 1 to k for all i + 1 <= k <= n. 




*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t, e, g; cin >> t >> e >> g;
    vector<ll> a(t);
    for(ll &x : a) cin >> x;
    vector<ll> b(t);

    ll cur = 0, maxs = 0;
    for(int i = t - 1; i >= 0; i--) {
        b[i] = cur - maxs;
        cur = cur + 1 - a[i];
        maxs = max(maxs, cur);
    }

    // cout << "b : " << b << '\n';

    int ok = 0;
    cur = e;
    for(int i = 0; i < t; i++) {
        cur -= a[i];
        if(cur - g + b[i] >= 0) ok = 1;
        cur = min(cur + 1, e);
    }

    cout << (ok ? "YES" : "NO") << '\n';

    return 0;
}
