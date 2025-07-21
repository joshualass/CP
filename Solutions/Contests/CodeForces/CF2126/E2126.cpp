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

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

void solve() {
    
    int n; cin >> n;
    vector<ll> p(n), s(n);
    for(ll &x : p) cin >> x;
    for(ll &x : s) cin >> x;
    vector<ll> a(n);
    // cout << "a\n";
    for(int i = 0; i < n; i++) {
        a[i] = lcm(p[i], s[i]);
        // cout << a[i] << " \n"[i == n - 1];
    }

    int ok = 1;

    ll g = 0;
    for(int i = 0; i < n; i++) {
        g = gcd(a[i], g);
        if(p[i] != g) ok = 0;
    }

    g = 0;
    for(int i = n - 1; i >= 0; i--) {
        g = gcd(a[i], g);
        if(s[i] != g) ok = 0;
    }

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}