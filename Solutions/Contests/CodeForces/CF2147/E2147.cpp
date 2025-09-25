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

//guess forces ._.

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

/*
observations

we should try to make the popcount 1's starting with the least significant bit
we do this because if we were to try and fill up a higher bit, we would add to the lower bit in the process. 

*/

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<array<int,2>> b;

    vector<int> unsat;
    int o = 0;
    for(int x : a) o |= x;

    for(int i = 0; i <= 30; i++) {
        if(((o >> i) & 1) == 0) unsat.push_back(i);
    }

    vector<int> c(n);
    int spc = __builtin_popcount(o);

    b.push_back({spc, 0});
    for(int i = 0; i < unsat.size(); i++) {
        c = a;
        int ops = 0;
        for(int bit = unsat[i]; bit >= 0; bit--) {
            int cur = 0;
            for(int x : c) cur |= x;
            if(((cur >> bit) & 1) == 0) {
                array<int,2> best = {-1, INT_MAX};
                for(int j = 0; j < n; j++) {
                    int rem = c[j] & ((1 << bit) - 1);
                    int add = (1 << bit) - rem;
                    if(add < best[1]) {
                        best = {j, add};
                    }
                }
                ops += best[1];
                c[best[0]] += best[1];
            }
        }
        b.push_back({spc + i + 1, ops});
        // cout << "i : " << i << " c : " << c << '\n';
    }

    // b : [2, 0] [3, 1] [4, 4] [5, 15] [6, 42] [7, 102] [8, 230] [9, 486] [10, 998] [11, 2022] [12, 4070] [13, 8166] [14, 16358] [15, 32742] [16, 65510] [17, 131046] [18, 262118] [19, 524262] [20, 1048550] [21, 2097126] [22, 4194278] [23, 8388582] [24, 16777190] [25, 33554406] [26, 67108838] [27, 134217702] [28, 268435430] [29, 536870886] [30, 1073741798] [31, 2147483622] 


    // int cur = 0;
    // int ops = 0;

    // auto upd_cur = [&]() -> void {
    //     for(int x : a) cur |= x;
    //     b.push_back({__builtin_popcount(cur), ops});
    // };

    // upd_cur();

    // while(__builtin_popcount(cur) != 31) {
    //     int one = 0, two = 0;
    //     for(int x : a) {
    //         two |= one & x;
    //         one |= x;
    //     }
    //     array<int,2> best = {-1, INT_MAX};
    //     for(int i = 0; i < n; i++) {
    //         for(int bit = 0; bit <= 30; bit++) {
    //             if(((one >> bit) & 1) == 0) {
    //                 int rem = a[i] & two & ((1 << bit) - 1);
    //                 int add = (1 << bit) - rem;
    //                 if(add < best[1]) {
    //                     best = {i, add};
    //                 }
    //             }
    //         }
    //     }
    //     ops += best[1];
    //     a[best[0]] += best[1];
    //     upd_cur();
    // }

    // cout << "b : " << b << '\n';

    for(int qq = 0; qq < q; qq++) {
        int x; cin >> x;
        int res = 0;
        for(auto [pc, op] : b) {
            if(x >= op) res = pc;
        }
        cout << res << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}