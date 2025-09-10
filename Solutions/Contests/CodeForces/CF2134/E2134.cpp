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

void solve(int debug, vector<int> solution) {

    vector<int> state = solution;
    int n;
    int qc = 0;
    if(debug) {
        n = state.size();
    } else {
        cin >> n;
    }

    //res stores {1, 2} whether there is a 1 or 2 in this box. d stores the number of ops starting here to jump out
    vector<int> res(n), d(n + 2, -1);
    d[n] = 0;
    d[n+1] = 0;
    int p = n;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    auto upd_dist = [&](int idx) -> void {
        assert(1 <= res[idx] && res[idx] <= 2);
        d[idx] = 1 + d[idx + res[idx]];
    };

    auto s = [&](int idx) -> void {
        cout << "swap " << idx + 1 << endl;
        qc++;\
        swap(perm[idx], perm[idx+1]);
        swap(res[idx], res[idx+1]);
        assert(0 <= idx && idx + 1 < n);

        if(debug) {
            swap(state[idx], state[idx+1]);
        }
    };
    auto t = [&](int idx) -> int {
        cout << "throw " << idx + 1 << endl;
        qc++;
        int dist;
        if(debug) {
            dist = 0;
            int cur = idx;
            while(cur < n) {
                dist++;
                cur += state[cur];
            }
        } else {
            cin >> dist;
        }
        return dist;
    };

    while(p >= 1) {
        if(debug) cout << "p : " << p << " d : " << d << endl;
        if(d[p] == d[p+1]) {
            if(p == 1) {
                s(0);
                int dist = t(1);
                if(dist == 1 + d[2]) {
                    res[1] = 1;
                } else {
                    res[1] = 2;
                }
                p--;
            } else {
                int dist = t(p - 2);
                if(dist == d[p] + 1) {
                    res[p - 2] = 2;
                } else {
                    res[p - 2] = 1;
                }
                s(p - 2);
                dist = t(p - 2);
                if(dist == d[p] + 1) {
                    res[p - 2] = 2;
                } else {
                    res[p - 2] = 1;
                }
                upd_dist(p - 1);
                upd_dist(p - 2);
            }
            p -= 2;
        } else {
            int dist = t(p - 1);
            d[p - 1] = dist;
            if(dist == 1 + d[p]) {
                res[p - 1] = 1;
            } else {
                res[p - 1] = 2;
            }
            upd_dist(p - 1);
            p--;
        }
    }

    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        ans[perm[i]] = res[i];
    }

    cout << "!";
    for(int i = 0; i < n; i++) cout << " " << ans[i];
    cout << endl;

    if(debug) {
        cout << "s " << solution << '\n';
        cout << "queries : " << qc << '\n';
    }

    assert(qc <= (3 * n + 1) / 2);
    if(debug) assert(ans == solution);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve(0, {});
    // vector<vector<int>> test;
    // solve(1, {1, 1, 1});
    // for(int i = 0; i < 32; i++) {
    //     vector<int> t;
    //     for(int j = 0; j < 5; j++) {
    //         if(((i >> j) & 1)) {
    //             t.push_back(1);
    //         } else {
    //             t.push_back(2);
    //         }
    //     }
    //     solve(1, t);
    // }

    return 0;
}