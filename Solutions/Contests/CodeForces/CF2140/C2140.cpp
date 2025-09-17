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

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll cur = 0;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            cur += a[i];
        } else {
            cur -= a[i];
        }
    }
    ll res = cur;
    ll best_diff = (n - 1) / 2 * 2;
    ll best_e = -1e18, best_o = -1e18;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            best_diff = max(best_diff, i - a[i] * 2 + best_e);
            best_o = max(best_o, -i - a[i] * 2);
        } else {
            best_diff = max(best_diff, i + a[i] * 2 + best_o);
            best_e = max(best_e, -i + a[i] * 2);
        }
    }
    cout << res + best_diff << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}