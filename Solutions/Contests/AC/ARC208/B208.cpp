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
    
    ll n, k; cin >> n >> k;
    ll l = 2, r = 1e10;
    vector<ll> a(n);
    while(r - l) {
        ll m = (l + r) / 2;
        a[0] = m;
        ll cur = 0;
        for(ll i = 1; i < n; i++) {
            ll next = min(a[i - 1] * 2 - 1, (k - cur) + a[i - 1]);
            a[i] = next;
            cur += a[i] - a[i - 1];
        }
        if(cur == k) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    a[0] = l;
    ll cur = 0;
    for(ll i = 1; i < n; i++) {
        ll next = min(a[i - 1] * 2 - 1, (k - cur) + a[i - 1]);
        a[i] = next;
        cur += a[i] - a[i - 1];
    }   
    
    for(ll i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}