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

ll test(ll c, ll x, ll n) {
    if(n == 0) return 0;
    return ((n ^ c) % n) == x;
}

ll solve_slow(ll c, ll x) {
    for(ll n = 1; n <= 100000; n++) {
        if(test(c, x, n)) return n;
    }
    return -1;
}



ll solve(ll c, ll x) {

    ll res = -1;
    ll cand = c ^ x;
    if(test(c, x, cand)) res = cand;
    ll num = 1;
    while(num < (c + x) * 2) num *= 2;

    ll cur = 0;

    for(int bit = 29; bit >= 0; bit--) {
        if((c >> bit) & 1) {
            if(cur < x) {
                cur += 1 << bit;
            } else {
                cur -= 1 << bit;
                num += 1 << bit;
            }
        }
    }

    if(test(c, x, num)) res = num;

    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int c = 1; c <= 200; c++) {
    //     for(int x = 1; x <= 200; x++) {
    //         ll res_slow = solve_slow(c, x);
    //         ll res = solve(c, x);
    //         if(res_slow != -1 && res == -1) {
    //             cout << "c : " << c << " x : " << x << " slow found : " << res_slow << " fast did not find\n";
    //         } else if(res_slow == -1 && res != -1) {
    //             cout << "c : " << c << " x : " << x << " slow did not find, fast found : " << res << '\n';
    //         }
            // ll res = solve_slow(c, x);
            // if(c == x) {
            //     assert(res != -1);
            // }
            // if(c != x) {
            //     cout << "c : " << c << " x : " << x << " solve : " << res << '\n';    
            //     cout << "c : " << bitset<8>(c) << " x : " << bitset<8>(x) << " solve : " << bitset<8>(res) << '\n';
                // if(res != -1) {
                //     if(res != (c ^ x)) {
                //         if(test(c, x, c ^ x)) {

                //         } else {
                //             cout << "this works but c ^ x does not work for c : " << c << " x : " << x << " res : " << res << '\n';
                //             cout << "working are\n";
                //             for(int i = 1; i <= 100; i++) {
                //                 if(test(c, x, i)) cout << "i : " << i << '\n';
                //             }
                //         }
                //         // cout << "does not follow pattern c : " << c << " x : " << x << " res : " << res << '\n';
                //     }
                // }
            // }
    //     }
    // }

    // cout << "all ok!\n";

    int casi; cin >> casi;
    while(casi-->0) {
        ll c, x; cin >> c >> x;
        cout << solve(c, x) << '\n';
    }



    return 0;
}