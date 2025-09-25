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

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    ll res = LLONG_MAX;
    
    auto _solve = [&](char t) {
        int g = count(s.begin(), s.end(), t);
        if(g == 0 || g == n) {
            res = 0;
            return;
        }

        vector<int> a;
        for(int i = 0; i < n; i++) {
            if(s[i] == t) {
                a.push_back(i);
            }
        }

        int mid = a[(g - 1) / 2];
        int l = mid - (g - 1) / 2;
        ll ops = 0;
        for(int i = 0; i < g; i++) {
            ops += abs(a[i] - (l + i));
        }
        res = min(res, ops);
    };

    _solve('a');
    _solve('b');
    
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}