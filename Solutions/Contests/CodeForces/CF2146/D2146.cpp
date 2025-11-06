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
interesting intuition for this problem. 

we want to partition over a pair of elements with maximum bitwise xor. 
there are some other problems where we want to analyze the largest bitwise xor between adjacent elements. 

also, discovered that for a contiguous array, the largest power of 2 is unique, although i wasn't able to apply this. 
*/

void solve() {
    
    ll l, r; cin >> l >> r;
    map<ll,ll> res;

    while(l <= r) {
        // cout << "l : " << l << " r : " << r << endl;
        if(l == r) {
            res[l] = r;
            r--;
        } else {
            ll mx = 0, p = -1;
            for(ll i = l + 1; i <= r; i++) {
                if(((i - 1) ^ i) >= mx) {
                    mx = ((i - 1) ^ i);
                    p = i;
                }
            }
            ll hi = p, lo = p - 1;

            // cout << "lo start : " << lo << " hi start : " << hi << "\n";

            while(hi <= r && lo >= l) {
                res[lo] = hi;
                res[hi] = lo;
                hi++;
                lo--;
            }
            // cout << "lo end : " << lo << " hi end : " << hi << '\n';
            if(lo < l) {
                l = hi;
            }
            if(hi > r) {
                r = lo;
            }
        }
    }

    ll s = 0;
    for(auto [k, v] : res) s += k | v;

    cout << s << '\n';
    for(auto [k, v] : res) cout << v << " ";
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}