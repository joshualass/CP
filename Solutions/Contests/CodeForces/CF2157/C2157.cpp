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
    
    int n, k, q; cin >> n >> k >> q;
    vector<int> res(n);
    vector<int> p(n + 1), p2(n + 1);
    for(int i = 0; i < q; i++) {
        int c, l, r; cin >> c >> l >> r;
        if(c ==1) {
            p[l-1]++;
            p[r]--;
        } else {
            p2[l-1]++;
            p2[r]--;
        }
    }

    int cur = 0;
    for(int i = 0; i < n; i++) {
        cur += p[i];
        if(cur) res[i] = k;
    }

    cur = 0;

    for(int i = 0; i < n; i++) {
        cur += p2[i];
        if(cur && res[i] == k) res[i] = k + 1;
    }
    
    cur = 0;
    for(int i = 0; i < n; i++) {
        if(res[i] == 0) {
            res[i] = cur++ % k;
        }
        cout << res[i] << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}