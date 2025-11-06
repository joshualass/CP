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
gg, too much guessforces. 

lower ego. get stuff done. 
*/

// much guess, maybe a good break was needed. 
// void solve() {
    
//     ll n, k; cin >> n >> k;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     sort(a.begin(), a.end());

//     vector<ll> p(n + 1);
//     for(ll i = 1; i <= n; i++) {
//         p[i] = p[i - 1] + a[i - 1];
//     }

//     //given x, what is our score, 
//     auto work = [&](ll x, ll r) -> ll {
//         if(r - x < -1) return -1;
//         ll nums = (r + 1 - (r - x / 2)) + min((x / 2) * k, r - x / 2);
//         ll sub = p[min((x / 2) * k, r - x / 2)] + p[r + 1] - p[r - x / 2];
//         ll med = a[r - x / 2];
//         return p[n] - sub + med * nums;
//     };
//     ll res = p[n];
//     ll r = n - 1;
//     for(ll x = (n - 1) / 2 * 2 + 1; x >= 3; x -= 2) {
//     // for(ll x = 3; x <= n; x += 2) {
//         ll cur = work(x, r);
//         while(1) {
//             ll nx = work(x, r - 1);
//             if(nx < 0 && cur < 0) break;
//             if(nx >= cur) {
//                 cur = nx;
//                 r--;
//             } else {
//                 break;
//             }
//         }
//         // cout << "x : " << x << " r : " << r << " cur : " << cur << '\n';
//         res = max(res, cur);
//     }

//     cout << res << '\n';

// }

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll res = accumulate(a.begin(), a.end(), 0LL);
    ll start = res;

    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i + 1] += a[i] + p[i];
    }

    //given x, what is our score, 
    auto work = [&](ll x, ll r) -> ll {
        if(r - x < -1) return -1;
        ll nums = (r + 1 - (r - x / 2)) + min((x / 2) * k, r - x / 2);
        ll sub = p[min((x / 2) * k, r - x / 2)] + p[r + 1] - p[r - x / 2];
        ll med = a[r - x / 2];
        return p[n] - sub + med * nums;
    };

    for(int i = 0; i < n; i++) {
        int l = i, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            int extra = m - i;

            ll loss = a[m] - a[i];
            ll prev_stop = min((ll) i, 1LL * k * (extra - 1));
            ll next_stop = min((ll) i, prev_stop + k);

            ll gain = (next_stop - prev_stop) * a[i] - (p[next_stop] - p[prev_stop]);
            if(gain >= loss) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        ll x = (l - i) * 2 + 1;
        res = max(res, work(x, l));

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}