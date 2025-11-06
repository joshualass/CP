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
    ll len = 0;
    int cnt = 0;
    set<ll> s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(s.count(x)) {
            len += x * 2;
            s.erase(x);
            cnt += 2;
        } else {
            s.insert(x);
        }
    }

    s.insert(0);
    vector<ll> a(s.begin(), s.end());

    if(len == 0) {
        cout << "0\n";
        return;
    }

    for(int i = a.size() - 1; i > 0; i--) {
        if(abs(a[i] - a[i - 1]) < len) {
            cnt++;
            len += a[i] + a[i - 1];
            break;
        }
    }

    cout << (cnt >= 3 ? len : 0) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}