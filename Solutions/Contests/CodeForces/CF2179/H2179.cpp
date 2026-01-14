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
    
    int n, q; cin >> n >> q;

    int ln = 32 - __builtin_clz(n);

    vector p(ln, vector<ll>(n * 2)), pd(ln, vector<ll>(n * 2));

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--; r--;
        for(int i = 1; i <= ln; i++) {
            ll mult = (i == 1 ? 1 : 1 << (i - 2));
            mult *= 1 << (i - 1);
            int cnt = (r - l + 1) >> (i - 1);
            
            pd[i-1][l + (1 << (i - 1)) - 1] += mult;
            pd[i-1][l + (1 << (i - 1)) - 1 + cnt * (1 << (i - 1))] -= mult;
            p[i-1][l + (1 << (i - 1)) - 1 + cnt * (1 << (i - 1))] -= mult * cnt;
        }
    }

    vector cur(ln, vector<ll>(n)), curd(ln, vector<ll>(n));
    for(int i = 0; i < n; i++) {
        ll res = 0;
        for(int j = 1; j <= ln; j++) {
            int idx = i & ((1 << (j - 1)) - 1);
            cur[j-1][idx] += p[j-1][i];
            curd[j-1][idx] += pd[j-1][i];
            cur[j-1][idx] += curd[j-1][idx];
            res += cur[j-1][idx];
        }
        cout << res << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}