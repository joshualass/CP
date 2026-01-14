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
    
    int n, k; cin >> n >> k;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }

    set<int> unvis;
    for(int i = 1; i <= n * 4; i++) unvis.insert(i);

    int res = 0;

    for(auto it = m.rbegin(); it != m.rend(); it++) {
        auto [start, v] = *it;
        while(v) {
            int x = *unvis.lower_bound(start);
            unvis.erase(x);
            // cout << "start : " << start << " v : " << v << " x : " << x << '\n';
            if(v == k) {
                res = max(res, x - start);
            }
            v--;
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