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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll rt, ct, ra, ca; cin >> rt >> ct >> ra >> ca;
    ll n, m, l; cin >> n >> m >> l;

    vector<pair<string, ll>> a, b;
    for(int i = 0; i < m; i++) {
        string s; cin >> s;
        ll x; cin >> x;
        a.push_back({s, x});
    }
    for(int i = 0; i < l; i++) {
        string s; cin >> s;
        ll x; cin >> x;
        b.push_back({s, x});
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    ll r = ra - rt, c = ca - ct;
    r *= -1;
    c *= -1;
    ll res = 0;

    auto sim = [&](string x, string y, ll move_cnt) -> void {
        // cout << "r : " << r << " c : " << c << '\n';
        // cout << "x : " << x << " y : " << y << " move_cnt : " << move_cnt << endl;
        array<int,2> delta = {};
        if(x == "U") {
            delta[0]--;
        } else if(x == "D") {
            delta[0]++;
        } else if(x == "R") {
            delta[1]++;
        } else if(x == "L") {
            delta[1]--;
        } else {
            assert(0);
        }

        if(y == "U") {
            delta[0]++;
        } else if(y == "D") {
            delta[0]--;
        } else if(y == "R") {
            delta[1]--;
        } else if(y == "L") {
            delta[1]++;
        } else {
            assert(0);
        }

        // cout << "delta : " << delta << '\n';

        if(delta == array<int,2>{0,0}) {
            if(r == 0 && c == 0) {
                res += move_cnt;
            }
        } else {
            ll nr = r + delta[0] * move_cnt;
            ll nc = c + delta[1] * move_cnt;
            //case get 1 from going upper-left. 
            if(delta == array<int,2>{1,1} && r == c && r < 0 && move_cnt >= abs(r)) {
                res++;
            }
            //case get 1 from going upper-right
            if(delta == array<int,2>{1,-1} && r == -c && r < 0 && move_cnt >= abs(r)) {
                res++;
            }
            //case get 1 from going lower-left
            if(delta == array<int,2>{-1,-1} && r == c && r > 0 && move_cnt >= abs(r)) {
                res++;
            }
            //case get 1 from going lower-right
            if(delta == array<int,2>{-1,1} && r == -c && r > 0 && move_cnt >= abs(r)) {
                res++;
            }
            //case double double
            if(delta == array<int,2>{2,0} && c == 0 && r % 2 == 0 && r < 0 && move_cnt >= abs(r) / 2) {
                res++;
            }
            if(delta == array<int,2>{0,2} && r == 0 && c % 2 == 0 && c < 0 && move_cnt >= abs(c) / 2) {
                res++;
            }
            if(delta == array<int,2>{-2,0} && c == 0 && r % 2 == 0 && r > 0 && move_cnt >= r / 2) {
                res++;
            }
            if(delta == array<int,2>{0,-2} && r == 0 && c % 2 == 0 && c > 0 && move_cnt >= c / 2) {
                res++;
            }
            r = nr;
            c = nc;
        }

    };

    while(a.size() || b.size()) {
        if(a.size() && a.back().second == 0) {
            a.pop_back();
            continue;
        }
        if(b.size() && b.back().second == 0) {
            b.pop_back();
            continue;
        }

        ll step = min(a.back().second, b.back().second);

        sim(a.back().first, b.back().first, step);

        a.back().second -= step;
        b.back().second -= step;

    }

    cout << res << '\n';

    return 0;
}
