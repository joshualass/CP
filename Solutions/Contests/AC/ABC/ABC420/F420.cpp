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
typedef long long ll;
typedef long double ld;
using namespace std;

/*
now, how do we modify this code to account for the k constraint

be careful and use some prefix sums. 

add and subtract. 

given width, [low  , and the current idx
We need to calculate the impact on 
 - cur
 - delta
 - updates to p. 

*/

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

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << "\n";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    vector<vector<int>> b(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = m - 1; j >= 0; j--) {
            b[i][j] = j == m - 1 ? m : b[i][j+1];
            if(a[i][j] == '#') {
                b[i][j] = j;
            }
        }
    }

    vector<vector<int>> cnts(n + 2, vector<int>(m + 2));
    /*
    length must be in interval [len_lo, len_hi]
    height must be 
    */

    auto add_p = [&](int x, int y1, int y2) -> void {
        // cout << "x : " << x << " y1 : " << y1 << " y2 : " << y2 << '\n';
        cnts[x][y1]++;
        cnts[x][y2+1]--;
    };

    for(int j = 0; j < m; j++) {
        //stack {length, lo}
        stack<array<int,2>> st;
        st.push({0, -1});
        for(int i = 0; i < n; i++) {
            int len = b[i][j] - j;
            int idx = i;
            while(st.top()[0] > len) {
                auto [width, lo] = st.top();
                st.pop();
                int pv_width = max(len, st.top()[0]);
                int height = i - lo;
                add_p(height, pv_width + 1, width);
                // cout << "i : " << i << " pv_width : " << pv_width << " width : " << width << " height : " << height << '\n';
                idx = lo;
            }
            st.push({len, idx});
        }
        while(st.top()[0]) {
            auto [width, lo] = st.top();
            st.pop();
            auto pv_width = st.top()[0];
            int height = n - lo;
            // cout << "pv_width : " << pv_width << " width : " << width << " height : " << height << '\n';
            add_p(height, pv_width + 1, width);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cnts[i][j] += cnts[i][j-1];
        }
    }

    for(int j = 1; j <= m; j++) {
        int cur = 0, above = 0;
        for(int i = n; i >= 1; i--) {
            above += cnts[i][j];
            cur += above;
            cnts[i][j] = cur;
        }
    }

    // cout << "cnts\n" << cnts << '\n';
    ll res = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(i * j <= k) {
                res += cnts[i][j];
            }
        }
    }

    cout << res << '\n';

    // cout << "b\n" << b << '\n';

    // ll res = 0;

    // for(int j = 0; j < 1; j++) {
        // stack<array<ll,2>> st; // {length, count}
        // ll s = 0;
        // // cout << "j : " << j << '\n';
        // for(int i = 0; i < n; i++) {
        //     ll nx = b[i][j] - j;
        //     ll idx = i;
        //     while(st.size() && st.top()[0] > nx) {
        //         auto [len, pos] = st.top();
        //         st.pop();
        //         s -= len * (idx - pos);
        //         idx = pos;
        //     }
        //     s += nx * (i - idx + 1);
        //     st.push({nx, idx});
        //     // cout << "i : " << i << " s : " << s << '\n';
        //     res += s;
        // }

    //     vector<ll> p(n + 1);
    //     ll delta = 0, cur = 0;

    //     auto update = [&](int lo, int hi, int idx, int width, int mult) -> void {
    //         int ml = k / width;

    //         int cur_lo = max(idx - ml + 1, lo);
    //         int cur_hi = min(hi, idx);

    //         ll cur_impact = max(0, cur_hi - cur_lo + 1) * width;
    //         ll delta_impact = 0;
    //         if(lo <= idx && idx <= lo + ml - 1) {
    //             delta_impact = width;
    //         } else if(lo + ml <= idx && idx <= lo * ml * 2 - 1) {
    //             delta_impact = -width;
    //         }

    //         cur += cur_impact * mult;
    //         delta += delta_impact * mult;

    //         if(0 <= lo && lo <= n) {
    //             p[lo] += width * mult;
    //         }
    //         if(0 <= lo + ml && lo + ml <= n) {
    //             p[lo+ml] -= width * 2 * mult;
    //         }
    //         if(0 <= lo + ml * 2 && lo + ml * 2 <= n) {
    //             p[lo + ml * 2] += width * mult;
    //         }

    //     };

    //     auto add = [&](int lo, int hi, int idx, int width) -> void {
    //         update(lo, hi, idx, width, 1);
    //     };

    //     auto remove = [&](int lo, int hi, int idx, int width) -> void {
    //         update(lo, hi, idx, width, -1);
    //     };

    //     //{length, lo, hi}
    //     stack<array<ll,3>> st;
    //     for(int i = 0; i < n; i++) {
    //         ll nx = b[i][j] - j;
    //         int idx = i;

    //         while(st.size() && st.top()[0] > nx) {
    //             auto [len, lo, hi] = st.top();
    //             st.pop();
    //             idx = lo;
    //             remove(lo, hi, i - 1, len);
    //         }
            
    //         delta += p[i];
    //         cur += delta;
    //         add(idx, i, i, nx);
    //         st.push({nx, idx, i});
    //         cout << "i : " << i << " delta : " << delta << " cur : " << cur << '\n';
    //         cout << "st : ";
    //         printS(st);
    //         res += cur;
    //     }
    // }

    // cout << res << '\n';

    return 0;
}
