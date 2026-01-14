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
    vector<int> a(n, -1);
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        a[l] = max(a[l], r);
    }

    vector<array<int,2>> queries;
    int prev = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] > prev) {
            queries.push_back({i, a[i]});
            prev = a[i];
        }
    }

    auto ask = [&](int l, int r) -> int {
        cout << "? " << l + 1 << " " << r + 1 << endl;
        int res; cin >> res;
        return res;
    };

    int l = 0, r = queries.size() - 1;
    while(l != r) {
        int m = (l + r) / 2;
        int lhs = ask(queries[l][0], queries[m][1]);
        int rhs = ask(queries[m+1][0], queries[r][1]);
        if(lhs >= rhs) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    int res = ask(queries[l][0], queries[l][1]);
    
    cout << "! " << res << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}