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

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    //returns the interval that is possible contains median <= m if it exists, else {-1, -1}
    auto get_range = [](vector<int> a, int k, int m) -> array<int,2> {
        // map<int,int> ms;

        // auto add_ms = [&](int l, int cnt) -> void {
        //     auto it = ms.lower_bound(cnt);
        //     if(it != ms.end() && it->second <= l) return;
        //     ms[cnt] = l;
        //     it = ms.find(cnt);
        //     while(it != ms.begin()) {
        //         it--;
        //         if(it->second >= l) {
        //             it = ms.erase(it);
        //         } else {
        //             break;
        //         }
        //     }
        // };

        vector<int> p;
        auto add_ms = [&](int l, int cnt) -> void {
            if(cnt >= 0) {
                if(cnt == p.size()) {
                    p.push_back(l);
                }
            }
        };

        array<int,2> f = {-1,-1};
        int cur = 0;
        for(int i = 0; i < a.size(); i++) {
            add_ms(i, cur);
            if(a[i] <= m) {
                cur--;
            } else {
                cur++;
            }

            int test = max(0, cur);
            // cout << "i : " << i << " k : " << k << " m : " << m << " cur : " << cur << " test : " << test << '\n';
            if(p.size() > test && i - p[test] + 1 >= k) {
                f = {p[test], i};
            }

            // auto it = ms.lower_bound(cur);
            // if(it != ms.end() && it->second <= i - k + 1) {
            //     f = {it->second, i};
            // }
        }

        // cout << "p : " << p << '\n';

        return f;
    };

    int lmin = 1, rmin = n;
    while(lmin != rmin) {
        int m = (lmin + rmin) / 2;
        auto f = get_range(a, k, m);
        if(f[0] != -1) {
            rmin = m;
        } else {
            lmin = m + 1;
        }
    }

    auto min_int = get_range(a, k, lmin);

    for(int &x : a) x *= -1;
    int lmax = 1, rmax = n;
    while(lmax != rmax) {
        int m = (lmax + rmax + 1) / 2;
        auto f = get_range(a, k, -m);
        if(f[0] != -1) {\
            lmax = m;
        } else {
            rmax = m - 1;
        }
    }

    auto max_int = get_range(a, k, -lmax);
    for(int &x : a) x *= -1;

    // cout << "min : " << lmin << " int : " << min_int << " max : " << lmax << " max_int : " << max_int << endl;

    set<int> unvis;
    for(int i = lmin; i <= lmax; i++) unvis.insert(i);

    map<int, array<int,2>> res;

    int l = min_int[0], r = min_int[0] - 1;

    multiset<int> left, right;
    auto balance = [&]() -> void {
        while(right.size() > left.size()) {
            int move = *right.begin();
            left.insert(move);
            right.erase(right.find(move));
        }
        while(left.size() > right.size()) {
            int move = *--left.end();
            left.erase(left.find(move));
            right.insert(move);
        }
    };

    auto insert = [&](int val) -> void {
        if(left.empty()) {
            right.insert(val);
        } else {
            if(val <= *--left.end()) {
                left.insert(val);
            } else {
                right.insert(val);
            }
        }
        balance();
    };

    auto erase = [&](int val) -> void {
        if(left.count(val)) {
            left.erase(left.find(val));
        } else {
            right.erase(right.find(val));
        }
        balance();
    };

    auto filler = [&]() -> void {
        int lo, hi;
        if(right.size() > left.size()) {
            lo = *right.begin(), hi = *right.begin();
        } else {
            lo = *--left.end();
            hi = *right.begin();
        }
        while(1) {
            auto it = unvis.lower_bound(lo);
            if(it != unvis.end() && *it <= hi) {
                res[*it] = {l, r};
                unvis.erase(it);
            } else {
                break;
            }
        }
    };

    while(r < min_int[1]) {
        insert(a[++r]);
    }

    filler();
    while(r < max_int[1]) {
        insert(a[++r]);
        filler();
    }

    while(l > max_int[0]) {
        insert(a[--l]);
        filler();
    }

    while(l < max_int[0]) {
        erase(a[l++]);
        filler();
    }

    while(r > max_int[1]) {
        erase(a[r--]);
        filler();
    }

    // cout << res.size() << '\n';
    // for(auto [k, v] : res) {
    //     cout << k << " " << v[0] + 1 << " " << v[1] + 1 << '\n';
    // }

    cout << lmax << " " << max_int[0] + 1 << " " << max_int[1] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}// #include <bits/stdc++.h>


// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, multiset<T> s) {
//     for(auto &x: s) os << x << " ";
//     return os;
// }

// void solve() {
    
//     int n, k; cin >> n >> k;
//     vector<int> a(n);
//     for(int &x : a) {
//         cin >> x;
//         x--;    
//     }

//     set<int> uv;
//     for(int i = 0; i < n; i++) {
//         uv.insert(i);
//     }
//     vector<array<int,3>> res;

//     for(int d = k; d <= min(n, k + 21); d++) {
//         multiset<int> mn, mx;

//         auto balance = [&]() -> void {
//             while(mn.size() > mx.size()) {
//                 int val = *--mn.end();
//                 mn.erase(mn.find(val));
//                 mx.insert(val);
//             }
//             while(mx.size() > mn.size()) {
//                 int val = *mx.begin();
//                 mx.erase(mx.find(val));
//                 mn.insert(val);
//             }
//             while(mn.size() && mx.size() && *--mn.end() > *mx.begin()) {
//                 int lomv = *--mn.end(), himv = *mx.begin();
//                 mn.erase(mn.find(lomv));
//                 mx.erase(mx.find(himv));
//                 mn.insert(himv);
//                 mx.insert(lomv);
//             }
//         };

//         for(int i = 0; i + 1 < d; i++) {
//             mn.insert(a[i]);
//         }
//         for(int i = d - 1; i < n; i++) {
//             mn.insert(a[i]);
//             balance();
//             // cout << "d : " << d << " i : " << i << " mn : " << mn << " mx : " << mx << '\n';
//             if(d & 1) {
//                 int val = *--mn.end();
//                 if(uv.count(val)) {
//                     uv.erase(val);
//                     res.push_back({val, i - d + 1, i});
//                 }
//             } else {
//                 int lo = *--mn.end(), hi = *mx.begin();
//                 while(uv.lower_bound(lo) != uv.end() && *uv.lower_bound(lo) <= hi) {
//                     int val = *uv.lower_bound(lo);
//                     uv.erase(val);
//                     res.push_back({val, i - d + 1, i});
//                 }
//             }
//             int erase = a[i - d + 1];
//             if(mn.count(erase)) {
//                 mn.erase(mn.find(erase));
//             } else {
//                 mx.erase(mx.find(erase));
//             }
//         }
//     }

//     cout << res.size() << '\n';

//     for(auto [v, l, r] : res) {
//         cout << v + 1 << " " << l + 1 << " " << r + 1 << '\n';
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }