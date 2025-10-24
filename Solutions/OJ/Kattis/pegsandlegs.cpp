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

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int l, p; cin >> l >> p;
    vector<array<ld,2>> c(l + p, {-1,-1}); //{constant, probability of rerolling up to x}
    for(int i = 0; i < l; i++) {
        int x; cin >> x;
        c[i] = array<ld,2>{(ld) x, 0};
    }

    vector<vector<pair<ld,int>>> ch(l + p);
    vector<int> deps(l + p);

    for(int i = 0; i < p; i++) {
        ld left, right; cin >> left >> right;
        int lc, rc; cin >> lc >> rc;
        lc--; rc--;
        int idx = i + l;
        ch[idx].push_back({left, lc});
        ch[idx].push_back({right, rc});
        deps[lc]++;
        deps[rc]++;
    }

    // cout << "init c : " << c << '\n';

    ld res = 0;

    for(int i = 0; i < p; i++) {
        int idx = i + l;

        auto [b1, a1] = c[ch[idx][0].second];
        auto [b2, a2] = c[ch[idx][1].second];

        ld L = ch[idx][0].first, R = ch[idx][1].first;
        ld S = 1 - (L + R);

        c[idx] = {b1 * L + b2 * R, S + L * a1 + R * a2};

        if(deps[idx] == 0) {
            ld calc = c[idx][0] / (1 - c[idx][1]);
            // cout << "idx : " << idx << " calc : " << calc << '\n';
            res = max(res, calc);
        }
    }

    for(int i = 0; i < l; i++) {
        if(deps[i] == 0) res = max(res, c[i][0]);
    }

    // cout << "final c : " << c << '\n';

    cout << fixed << setprecision(10) << res << '\n';

    return 0;
}
