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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    auto solve = [](vector<int> a, int mod) -> array<map<int,ll>, 2> {

        map<int,ll> in, next;
        in[0] = 1;
        for(int i = 0; i < a.size(); i++) {
            map<int,ll> true_next;
            for(auto [k, v] : in) {
                true_next[(a[i] + k) % mod] += v;
            }
            for(auto [k, v] : next) {
                in[k] += v;
            }
            swap(next, true_next);
        }
        for(auto [k, v] : next) in[k] += v;
        return {in, next};
    };

    int mid = n / 2;
    vector<int> lhs(a.begin(), a.begin() + mid), rhs(a.begin() + mid, a.end());
    auto [lm, lml]= solve(lhs, m);
    reverse(rhs.begin(), rhs.end());
    auto [rm, rmr] = solve(rhs, m);

    ll res = 0;
    for(auto [k, v] : lm) {
        int targ = (m - k) % m;
        res += v * rm[targ];
    }
    for(auto [k, v] : lml) {
        int targ = (m - k) % m;
        res -= v * rmr[targ];
    }

    cout << res << '\n';

    return 0;
}
