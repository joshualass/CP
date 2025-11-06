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

void solve_first() {
    
    int n; cin >> n;
    int lo, hi;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x == 1) {
            lo = i;
        } else if(x == n) {
            hi = i;
        }
    }
    cout << (lo < hi) << '\n';

}

void solve_second() {
    int n, x; cin >> n >> x;
    auto ask = [&](int l, int r) -> int {
        cout << "? " << l + 1 << " " << r + 1 << endl;
        int res; cin >> res;
        return res;
    };

    if(x == 1) {
        int l = 1, r = n - 1;
        while(l != r) {
            int m = (l + r) / 2;
            int res = ask(0, m);
            if(res == n - 1) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        cout << "! " << l + 1 << endl;
    } else {
        int l = 0, r = n - 2;
        while(l != r) {
            int m = (l + r + 1) / 2;
            int res = ask(m, n - 1);
            if(res == n - 1) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        cout << "! " << l + 1 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string type; cin >> type;

    int casi; cin >> casi;
    while(casi-->0) {
        if(type == "first") {
            solve_first();
        } else {
            solve_second();
        }
    }

    return 0;
}