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
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    auto test = [&](int i, int j) -> array<ll,3> {
        if(i == j) return {LLONG_MAX};
        auto [x1, y1] = a[i];
        auto [x2, y2] = a[j];
        ll dx = x2 - x1, dy = y2 - y1;
        ll A = dy, B = -dx;
        ll C = x1 * A + y1 * B;
        int cnt = 0;
        for(int k = 0; k < n; k++) if(a[k][0] * A + a[k][1] * B == C) cnt++;
        if(cnt > n / 2) return {A, B, C};
        return {LLONG_MAX};
    };

    for(int i = 0; i < 200; i++) {
        auto res = test(rng() % n, rng() % n);
        if(res[0] != LLONG_MAX) {
            cout << "Yes" << '\n';
            cout << res[0] << " " << res[1] << " " << -res[2] << '\n';
            return 0;
        }
    }

    cout << "No" << '\n';

    return 0;
}
