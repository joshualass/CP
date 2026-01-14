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
    
    ll n, x, y; cin >> n >> x >> y;
    string s; cin >> s;
    vector<ll> p(n);
    for(ll &x : p) cin >> x;

    ll tx = x, ty = y;
    
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            x -= 1 + p[i] / 2;
        } else {
            y -= 1 + p[i] / 2;
        }
    }

    int ok = x >= 0 && y >= 0;

    if(count(s.begin(), s.end(), '0') == n && !(tx >= ty + n)) ok = 0;
    if(count(s.begin(), s.end(), '1') == n && !(tx + n <= ty)) ok = 0;
    if(accumulate(p.begin(), p.end(), 0LL) > tx + ty) ok = 0;

    cout << (ok ? "YES" : "NO") << "\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}