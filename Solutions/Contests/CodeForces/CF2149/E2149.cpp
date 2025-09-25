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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k, l, r; cin >> n >> k >> l >> r;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    //compute the minimum length prefixes 
    vector<int> min_r(n);
    map<int,int> m;

    for(int lo = 0, hi = 0; lo < n; lo++) {
        while(hi < n && m.size() < k) {
            m[a[hi++]]++;
        }
        if(m.size() == k) {
            min_r[lo] = hi - 1;
        } else {
            min_r[lo] = n;
        }
        m[a[lo]]--;
        if(m[a[lo]] == 0) m.erase(a[lo]);
    }

    vector<int> max_r(n);
    assert(m.empty());
    ll res = 0;
    for(int lo = 0, hi = 0; lo < n; lo++) {
        while(hi < n && (m.size() < k || m.size() == k && m.count(a[hi]))) {
            m[a[hi++]]++;
        }
        if(m.size() == k) {
            max_r[lo] = hi - 1;
        } else {
            max_r[lo] = n;
        }
        m[a[lo]]--;
        if(m[a[lo]] == 0) m.erase(a[lo]);
        if(min_r[lo] != n) {
            int curl = min_r[lo] - lo + 1, curr = max_r[lo] - lo + 1;
            curl = max(curl, l), curr = min(curr, r);
            int add = max(0, curr - curl + 1);
            // cout << "lo : " << lo << " add : " << add << '\n';
            res += add;
        }
    }

    // cout << "min r : " << min_r << '\n';
    // cout << "max r : " << max_r << '\n';

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}