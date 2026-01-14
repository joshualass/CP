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
    
    auto ask = [&](int l, int r) -> ll {
        cout << "? " << l + 1 << " " << r + 1 << endl;
        ll res; cin >> res;
        return res;
    };

    int l = 0, r = n - 1;
    ll sum = ask(0, n - 1);
    while(l != r) {
        int lp = l, rp = r;
        while(lp != rp) {
            int m = (lp + rp) / 2;
            ll res = ask(l, m);
            if(res < sum / 2) {
                lp = m + 1;
            } else if(res == sum / 2) {
                lp = m;
                rp = m;
            } else {
                rp = m - 1;
            }
        }
        int lf = lp - l + 1, ls = r - lp;
        if(lf < ls) {
            r = lp;
        } else {
            l = lp + 1;
        }
        sum /= 2;
    }

    ll res = ask(l, l);

    cout << "! " << res << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}