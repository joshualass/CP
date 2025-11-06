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
    
    int n, m; cin >> n >> m;
    multiset<int> ms;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ms.insert(x);
    }

    vector<array<int,2>> big, small, zero;  
    vector<int> b(m);
    for(int &x : b) cin >> x;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        if(x == 0) zero.push_back({b[i], 0});
        else if(x <= b[i]) {
            small.push_back({b[i], x});
        } else {
            big.push_back({b[i], x});
        }
    }

    sort(big.begin(), big.end());
    int res = 0;
    for(auto [hp, c] : big) {
        if(ms.lower_bound(hp) != ms.end()) {
            int x = *ms.lower_bound(hp);
            ms.erase(ms.lower_bound(hp));
            ms.insert(max(x, c));
            res++;
        }
    }
    int mx = *--ms.end();
    for(auto [hp, c] : small) {
        if(hp <= mx) res++;
    }
    for(auto [hp, c] : zero) {
        if(ms.lower_bound(hp) != ms.end()) {
            ms.erase(ms.lower_bound(hp));
            res++;
        }
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