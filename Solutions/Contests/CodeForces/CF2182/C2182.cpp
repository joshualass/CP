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
    
    ll n; cin >> n;
    vector<ll> a(n), b(n), c(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    for(ll &x : c) cin >> x;

    auto get_cnt = [](vector<ll> &a, vector<ll> &b) -> ll {

        ll res = 0;
        for(ll s = 0; s < a.size(); s++) {
            ll ok = 1;
            for(ll i = 0; i < a.size(); i++) {
                if(a[(s+i)%a.size()] >= b[i]) ok = 0;
            }
            res += ok;
        }
        return res;
    };

    cout << get_cnt(a, b) * get_cnt(b, c) * n << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}