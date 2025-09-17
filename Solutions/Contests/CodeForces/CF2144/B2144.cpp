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

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), vis(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        if(x != -1) vis[x] = 1;
    }
    vector<int> unvis;
    for(int i = 0; i < n; i++) if(vis[i] == 0) unvis.push_back(i);
    int lo = n, hi = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == -1) {
            a[i] = unvis.back();
            unvis.pop_back();
        }
        if(a[i] != i) {
            lo = min(lo, i);
            hi = max(hi, i);
        }
    }

    cout << max(0, hi - lo + 1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}