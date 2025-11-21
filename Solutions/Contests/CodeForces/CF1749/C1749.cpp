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
    
    int n; cin >> n;
    multiset<int> ms;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ms.insert(x);
    }

    auto check = [](multiset<int> ms, int k) -> int {
        for(int i = k; i >= 1; i--) {
            if(ms.upper_bound(i) == ms.begin()) return 0;
            int x = *--ms.upper_bound(i);
            ms.erase(ms.find(x));
            if(ms.size()) {
                int b = *ms.begin();
                ms.erase(ms.begin());
                ms.insert(i + b);
            }
        }
        return 1;
    };

    int l = 0, r = n;
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(check(ms, m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}