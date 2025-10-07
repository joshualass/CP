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
    string s; cin >> s;
    int res = INT_MAX;

    auto _solve = [&](char targ) -> void {

        vector<int> p(n + 1);
        for(int i = 1; i <= n; i++) {
            if(s[i - 1] == targ) {
                p[i] += 2;
            } else {
                p[i] += 1;
            }
            p[i] += p[i-1];
        }

        // cout << "targ : " << targ << " p : " << p << "\n";

        int lo = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] != targ) {
                int hi = i;
                res = min(res, p[lo] + p[n] - p[hi]);
                lo = i + 1;
            }
        }

        res = min(res, p[lo]);

    };

    _solve('0');
    _solve('1');

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}