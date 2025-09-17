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
const int MAXN = 200000;

void solve() {
    
    ll n, y; cin >> n >> y;
    vector<int> a(MAXN + 1), p(MAXN + 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x]++;
    }
    for(int i = 1; i <= MAXN; i++) {
        p[i] = p[i-1] + a[i];
    }

    ll res = LLONG_MIN;
    for(int x = 2; x <= MAXN; x++) {
        ll cur = -n * y;
        for(int z = 1; x * (z - 1) + 1 <= MAXN; z++) {
            int lo = x * (z - 1) + 1, hi = x * z;
            int cnt = p[min(MAXN,hi)] - p[lo-1];
            cur += 1LL * z * cnt;
            cur += min(a[z], cnt) * y;
        }
        // cout << "x : " << x << " cur : " << cur << '\n';
        res = max(res, cur);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}