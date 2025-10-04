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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> p1(n + 1), p2(n + 1);
    for(int i = 1; i <= n; i++) {
        p1[i] += (32 - __builtin_clz(a[i - 1] - 1)) + p1[i - 1];
        p2[i] += p2[i - 1];
        if(__builtin_popcount(a[i-1]) == 2 && __builtin_popcount(a[i - 1] - 1) == 1) {
            p2[i]++;
        }
    }

    // cout << "a : " << a << '\n';
    // cout << "p1 : " << p1 << '\n';
    // cout << "p2 : " << p2 << '\n';

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        ll ops = p1[r] - p1[l];
        ll extra = p2[r] - p2[l];
        cout << ops - (extra + 1) / 2 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}