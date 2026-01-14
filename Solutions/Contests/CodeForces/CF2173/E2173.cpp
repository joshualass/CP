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
    vector<int> a(n), ra(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        ra[x] = i;
    }

    auto ask_and_update = [&](int u, int v) -> void {
        cout << "? " << u + 1 << " " << v + 1 << endl;
        int x, y; cin >> x >> y;
        x--; y--;
        swap(a[x], a[y]);
        swap(ra[a[x]], ra[a[y]]);
    };

    for(int i = 0; i < n / 2; i++) {
        //make a[i] = i
        while(a[i] != i) {
            int u = i, v = ra[i];
            ask_and_update(u, v);
        }
        int u = n - i - 1, v = ra[n - i - 1];
        while(a[i] != i || a[n-i-1] != n - i - 1) {
            ask_and_update(u, v);
        }
    }

    cout << "!" << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}