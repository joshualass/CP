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
    vector<int> a(n);
    for(int &x : a) cin >> x;

    auto _solve = [](vector<int> a, int &res) {

        vector<int> smax(a.size()), smin(a.size());
        for(int i = a.size() - 1; i >= 0; i--) {
            if(i == a.size() - 1) {
                smax[i] = a[i];
                smin[i] = a[i];
            } else {
                smax[i] = max(smax[i+1],a[i]);
                smin[i] = min(smin[i+1],a[i]);
            }
        }
        int cmin = INT_MAX, cmax = INT_MIN;
        for(int i = 0; i + 1 < a.size(); i++) {
            cmax = max(cmax, a[i]);
            cmin = min(cmin, a[i]);
            res = max(res, cmax - cmin + smax[i+1] - smin[i+1]);
        }
    };
    int res = 0;

    int m = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] < a[m]) m = i;
    }
    rotate(a.begin(), a.begin() + m, a.end());
    // cout << "a : " << a << '\n';
    
    _solve(a, res);

    reverse(a.begin() + 1, a.end());
    _solve(a, res);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}