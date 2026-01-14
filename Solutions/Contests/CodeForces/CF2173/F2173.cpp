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
const int SN = 400;

/*
just did the most obvious q sqrtn logn approach that i thought up of in 10 mint

there are some constant factors to make this faster. 

what is more interesting is sqrt n per query approach which i would try to do if this tled / i would optimize constant more. 
*/

void solve() {
    
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] + a[i];
    }

    //given that we start at index l, checks to make sure that the memory is reset for the first time directly after acquiring memory at index r
    auto check = [&](int l, int r, ll x) -> bool {
        ll sum = p[r] - p[l];
        return sum < x && sum + a[r] >= x;
    };

    for(int qq = 0; qq < q; qq++) {
        ll l, r, x; cin >> l >> r >> x;
        l--; r--;

        ll res = 0, partial = 0;

        int prev_len = 0;
        while(l <= r) {
            int rem_len = r - l + 1;

            //we will not be able to form another segment because the remaining length is too small
            if(rem_len <= prev_len) {
                partial = p[r+1] - p[l];
                break;
            }

            int len_lo = prev_len + 1, len_hi = rem_len + 1;
            while(len_lo != len_hi) {
                int m = (len_lo + len_hi) / 2;
                int test_r = l + m - 1;
                ll sum = p[test_r + 1] - p[l];
                if(sum >= x) {
                    len_hi = m;
                } else {
                    len_lo = m + 1;
                }
            }

            //complete segment is still not possible. 
            if(len_lo == rem_len + 1) {
                partial = p[r+1] - p[l];
                break;
            }

            prev_len = len_lo;
            int cnt_lo = 1, cnt_hi = rem_len / prev_len;

            while(cnt_lo != cnt_hi) {
                int m = (cnt_lo + cnt_hi + 1) / 2;
                int test_l = l + prev_len * (m - 1);
                if(check(test_l, test_l + prev_len - 1, x)) {
                    cnt_lo = m;
                } else {
                    cnt_hi = m - 1;
                }
            }

            res += cnt_lo;
            l += prev_len * cnt_lo;
        }

        cout << res << " " << partial << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}