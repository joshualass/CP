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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    ll ma = 0;
    set<array<ll,2>> lo, hi;
    ll hi_score = 0;

    auto balance = [&]() -> void {
        assert((lo.size() + hi.size()) % 2 == 0);
        while(lo.size() > hi.size()) {
            auto last = *--lo.end();
            lo.erase(last);
            hi.insert(last);
            hi_score += last[0];
        }
        while(hi.size() > lo.size()) {
            auto first = *hi.begin();
            hi.erase(first);
            hi_score -= first[0];
            lo.insert(first);
        }
        if(lo.size()) {
            while((*--lo.end())[0] > (*hi.begin())[0]) {
                auto last = *--lo.end();
                auto first = *hi.begin();
                lo.erase(last);
                hi.erase(first);
                hi_score -= first[0];
                lo.insert(first);
                hi.insert(last);
                hi_score += last[0];
            }
        }
    };

    ll l_score = 0;
    for(int i = 0; i < n; i++) l_score += a[i][0];

    if(n & 1) {
        for(int i = 1; i < n; i++) {
            lo.insert({a[i][0] + a[i][1], i});
        }
        for(int i = 0; i < n; i++) {
            balance();
            ll score_here = hi_score - (l_score - a[i][0]);
            ma = max(ma, score_here);
            
            // cout << "i : " << i << '\n';
            // cout << "lo : " << lo << '\n';
            // cout << "hi : " << hi << '\n';
            // cout << "sh : " << score_here << '\n';

            lo.insert({a[i][0] + a[i][1], i});
            if(i + 1 < n) {
                lo.erase({a[i+1][0] + a[i+1][1], i + 1});
                if(hi.count({a[i+1][0] + a[i+1][1], i + 1})) hi_score -= a[i+1][0] + a[i+1][1];
                hi.erase({a[i+1][0] + a[i+1][1], i + 1});
            }
        }
    } else {
        for(int i = 0; i < n; i++) lo.insert({a[i][0] + a[i][1], i});
        balance();
        ma = hi_score - l_score;
    }

    ll init_seg_length = 0;
    for(int i = 0; i < n; i++) init_seg_length += a[i][1] - a[i][0];
    cout << init_seg_length + ma << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}