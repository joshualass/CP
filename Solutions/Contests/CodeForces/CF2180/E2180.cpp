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

/*
spent some time on this problem, ig. 

maybe a lot of the time, i didn't have the best mindset / thinking space. 

When I attempted this problem a week later, I used the observation that the answer was one less than a power 2 (excluding 0). 
The first thought that comes to mind, later, is that we want to partition the groups about the highest power of 2 in the interval [l, r]. 

We can look at the partitions where that permute the elements within their respective halfs, and the number of ways to be able to do this is just the minimum of the largest power of 2
of these 2 halves. Additionally, we can repeat the above if they are the same size and multiply by 2.
*/

void solve() {
    
    // ll l, r; cin >> l >> r;
    // for(int bit = 63; bit >= 0; bit--) {
    //     if(((l >> bit) & 1) == ((r >> bit) & 1)) {
    //         if((l >> bit) & 1) {
    //             l -= 1LL << bit;
    //             r -= 1LL << bit;
    //         }
    //     } else {
    //         break;
    //     }
    // }



    // ll s = l + r + 1;

    // bitset<64> a(l), b(r), c(s);

    // cout << "s : " << s << '\n';
    // cout << "z : " << r - l << '\n';

    // cout << "l : " << a << " r : " << b << " s : " << c << '\n';

    ll l, r; cin >> l >> r;

    for(int bit = 60; bit >= 0; bit--) {
        if(((l >> bit) & 1) != ((r >> bit) & 1)) {
            break;
        }
        l &= ~(1LL << bit);
        r &= ~(1LL << bit);
    }

    if(r == 0) {
        cout << "0\n";
    } else {
        ll part = 1LL << (63 - __builtin_clzll(r));
        ll lhs = part - l, rhs = r - part + 1;

        int test = min(__builtin_ctzll(lhs), __builtin_ctzll(rhs));
        if(lhs == rhs) test++;

        cout << ((1LL << test) - 1) << '\n';
    }
}

ll solve_fast(ll l, ll r) {
    // for(int bit = 60; bit >= 0; bit--) {
    //     if(((l >> bit) & 1) == ((r >> bit) & 1)) {
    //         if((l >> bit) & 1) {
    //             l -= 1LL << bit;
    //             r -= 1LL << bit;
    //         }
    //     } else {
    //         break;
    //     }
    // }

    // ll cnt = r - l + 1;
    // // cout << "cnt : " << cnt << " cnt/2 : " << cnt/2 << endl;
    // if(cnt & 1) return 0;

    // int f = 0;

    // auto cnt_leq = [&](ll num, int bit) -> ll {
    //     if(num == -1) return 0;
    //     ll bm = (1LL << (bit + 1)) - 1;
    //     ll lower = num & bm;
    //     ll upper = num & (bm ^ ((ll) -1));
    //     return upper / 2 + (lower & (1LL << bit) ? 1 + lower - (1LL << bit) : 0LL);
    // };

    // for(int bit = 60; bit >= 0; bit--) {
    //     ll c = cnt_leq(r, bit) - cnt_leq(l - 1, bit);
    //     // cout << "c : " << c << endl;
    //     if(c == (cnt / 2)) f = 1;
    // }
    // cout << "ok : " << f << endl;
    // return f ? (1LL << __builtin_ctzll(cnt)) - 1 : 0LL;

    //extremely guessforces ... maybe a little intuition this time around ...

    // ll l, r; cin >> l >> r;

    for(int bit = 60; bit >= 0; bit--) {
        if(((l >> bit) & 1) != ((r >> bit) & 1)) {
            break;
        }
        l &= ~(1LL << bit);
        r &= ~(1LL << bit);
    }

    if(r == 0) {
        cout << "0\n";
    } else {
        int part = 1LL << (63 - __builtin_clzll(r));
        ll lhs = part - l, rhs = r - part + 1;

        int test = min(__builtin_ctzll(lhs), __builtin_ctzll(rhs));
        if(lhs == rhs) test++;

        cout << ((1LL << test) - 1) << '\n';
    }

}

int solve_slow(ll l, ll r) {
    int res = 0;
    for(int x = 1; x <= r * 2; x++) {
        int ok = 1;
        for(int i = l; i <= r; i++) if((i ^ x) < l || (i ^ x) > r) ok = 0;
        if(ok) res++;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << bitset<64>(2199023255551LL) << '\n';

    // while(1) {
    //     int l, r; cin >> l >> r;
    //     cout << '\n';
    //     cout << "binary l : " << bitset<8>(l) << " r : " << bitset<8>(r) << endl;
    //     cout << "soln : " << solve_slow(l, r) << '\n';
    //     cout << "diff : " << r - l + 1 << endl;
    // }

    // for(int L = 1; L <= 200; L++) {
    //     for(int R = L; R <= 200; R++) {
    //         // cout << "L : " << L << " R : " << R << endl;
    //         if(L == R) continue;
    //         int l = L, r = R;
    //         int val = solve_slow(l, r);

    //         //normalize
    //         for(int bit = 30; bit >= 0; bit--) {
    //             if(((l >> bit) & 1) != ((r >> bit) & 1)) {
    //                 break;
    //             }
    //             l &= ~(1 << bit);
    //             r &= ~(1 << bit);
    //         }

    //         int part = 1 << (31 - __builtin_clz(r));
    //         int lhs = part - l, rhs = r - part + 1;

    //         int test = min(__builtin_ctz(lhs), __builtin_ctz(rhs));
    //         if(lhs == rhs) test++;
    //         int comp_lhs = val + 1;
    //         int comp_rhs = 1 << (test);

    //         if(comp_lhs != comp_rhs) {
    //             cout << "L : " << L << " R : " << R << " l : " << l << " r : " << r << " val : " << val << " test : " << test << " part : " << part << " lhs : " << lhs << " rhs : " << rhs << endl;
    //             cout << "comp lhs : " << comp_lhs << " comp rhs : " << comp_rhs << endl;
    //             return 0;
    //         }

    //         // if(__builtin_popcount(val + 1) != 1) {
    //         //     cout << "not one less than a power of 2 for l : " << l << " r : " << r << endl;
    //         //     return 0;
    //         // }
    //         // int len = r - l + 1;
    //         // int tval = val + 1;
    //         // if(val) {
    //         //     while(1) {
    //         //         if((tval & 1) != (len & 1)) {
    //         //             cout << "l : " << l << " r : " << r << " val : " << val << endl;
    //         //             return 0;
    //         //         }
    //         //         if(len & 1) break;
    //         //         tval /= 2;
    //         //         len /= 2;
    //         //     }
    //         // }
    //     }
    // }

    // cout << "all testcases are good!" << endl;

    int casi; cin >> casi;
    while(casi-->0) {
        // ll l, r; cin >> l >> r;
        // cout << solve_fast(l, r) << '\n';
        solve();
    }

    return 0;
}