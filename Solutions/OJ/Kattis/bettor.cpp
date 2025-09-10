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

ld binexp(ld x, int pow) {
    assert(pow >= 0);
    ld res = 1;
    while(pow) {
        if(pow & 1) res *= x;
        x *= x;
        pow /= 2;
    }
    return res;
}

ld pc[30000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ld x, p; cin >> x >> p;
    p /= 100, x /= 100;
    ld q = 1 - p;

    pc[0] = 1;
    for(int i = 1; i < 30000; i++) {
        pc[i] = pc[i-1] * p/q;
    }

    ld res = 0;

    for(int i = 0; i < 26000; i++) {
        for(int j = 0; j < 2600; j++) {
            int n = i + j;
            ld plose = (1 - pc[j]) / (1 - pc[i + j]);
            ld pwin = 1 - plose;
            res = max(res, pwin * j + plose * -i * (1 - x));
        }
    }

    cout << fixed << setprecision(10) << res << '\n';

    // cout << "p : " << p << " q : " << q << '\n';

    // auto solve = [&](int stop_loss, int stop_win) -> ld {
    //     int n = stop_win - stop_loss;
    //     // ld pwin = (1 - binexp(q/p, -stop_loss)) / (1 - binexp(q/p, n));
    //     // ld plose = 1 - pwin;
    //     ld plose = (1 - binexp(p/q, stop_win)) / (1 - binexp(p/q, n));
    //     ld pwin = 1 - plose;
    //     cout << "pwin : " << pwin << " plose : " << plose << '\n';
    //     return pwin * stop_win + plose * stop_loss * (1 - x);
    // };

    // for(int i = -4; i <= 0; i++) {
    //     cout << "i : " << i << " solve : " << solve(i, 5) << '\n';
    // }

    // auto solve_fixed_sl = [&](int stop_loss) -> ld {
    //     cout << "stop_loss : " << stop_loss << '\n';
    //     int sw_lo = 0, sw_hi = 1e9;
    //     while(sw_hi - sw_lo > 4) {
    //         int m1 = sw_lo + (sw_hi - sw_lo) / 3;
    //         int m2 = sw_lo + 2 * (sw_hi - sw_lo) / 3;
    //         ld solve_m1 = solve(stop_loss, m1);
    //         ld solve_m2 = solve(stop_loss, m2);
    //         cout << "solve m1 : " << solve_m1 << " solve m2 : " << solve_m2 << '\n';
    //         if(solve_m1 >= solve_m2) {
    //             sw_hi = m2;
    //         } else {
    //             sw_lo = m1;
    //         }
    //     }
    //     ld best_ev = -1e18;
    //     cout << "sw_lo : " << sw_lo << " sw_hi : " << sw_hi << '\n';
    //     for(int i = sw_lo; i <= sw_hi; i++) {
    //         best_ev = max(best_ev, solve(stop_loss, i));
    //     }
    //     cout << "best_ev : " << best_ev << '\n';
    //     return best_ev;
    // };

    // int sl_lo = -1e9, sl_hi = 0;
    // while(sl_hi - sl_lo > 4) {
    //     int m1 = sl_lo + (sl_hi - sl_lo) / 3;
    //     int m2 = sl_lo + 2 * (sl_hi - sl_lo) / 3;
    //     if(solve_fixed_sl(m1) >= solve_fixed_sl(m2)) {
    //         sl_hi = m2;
    //     } else {
    //         sl_lo = m1;
    //     }
    // }

    // cout << "sl_lo : " << sl_lo << " sl_hi : " << sl_hi << '\n';

    // ld best_ev = -1e18;
    // for(int i = sl_lo; i <= sl_hi; i++) {
    //     best_ev = max(best_ev, solve_fixed_sl(i));
    // }
    // cout << best_ev << '\n';

    return 0;
}
