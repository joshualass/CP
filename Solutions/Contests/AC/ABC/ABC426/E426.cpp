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

void solve() {
    int tsx, tsy, tgx, tgy, asx, asy, agx, agy; cin>> tsx >> tsy >> tgx >> tgy >> asx >> asy >> agx >> agy;


    
    auto dist = [&](ld x1, ld y1, ld x2, ld y2) -> ld {
        return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    auto get_pos = [&](ld sx, ld sy, ld gx, ld gy, ld t) -> array<ld,2> {
        ld d = dist(sx, sy, gx, gy);
        // cout << "t : " << t << " pos d : " << d << '\n';
        if(t < d) {
            ld dx = gx - sx, dy = gy - sy;
            ld c = sqrtl(dx * dx + dy * dy);

            dx /= c, dy /= c;

            assert(abs(dx*dx+dy*dy)-1<1e-10);

            // cout << "get pos 0 called\n";

            // cout << "d < t\n";

            return {sx + dx * t, sy + dy * t};
        } else {
            // cout << "done, go to end\n";
            return {gx, gy};
        }
    };

    auto calc = [&](ld t) -> ld {
        auto [tx, ty] = get_pos(tsx, tsy, tgx, tgy, t);
        auto [gx, gy] = get_pos(asx, asy, agx, agy, t);
        // cout << "t : " << t << " calc tx : " << tx << " ty : " << ty << " gx : " << gx << " gy : " << gy << '\n';
        return dist(tx, ty, gx, gy);
    };

    ld t_time = dist(tsx, tsy, tgx, tgy);
    ld a_time = dist(asx, asy, agx, agy);

    // cout << "t_time : " << t_time << '\n';
    // cout << "a_time : " << a_time << '\n';

    auto search = [&](ld lo, ld hi) -> ld {
        while(hi - lo > 1e-10) {
            ld m1 = lo + (hi - lo) / 3, m2 = lo + (hi - lo) * 2 / 3;

            ld d1 = calc(m1);
            ld d2 = calc(m2);


            // cout << "lo : " << lo << " hi : " << hi << '\n';
            // cout << "m1 : " << m1 << " m2 : " << m2 << '\n';
            // cout << "d1 : " << d1 << " d2 : " << d2 << '\n';

            if(d1 < d2) {
                hi = m2;
            } else {
                lo = m1;
            }
        }
        // cout << "lo : " << lo << '\n';
        return calc((lo + hi) / 2);
    };

    cout << fixed << setprecision(10) << min(search(0, min(t_time, a_time)), search(min(t_time, a_time), max(t_time, a_time))) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
