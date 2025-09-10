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
typedef long long ll;
typedef long double ld;
using namespace std;

/*

1
6 1
3 1 2 5 6 4
1 6

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n), ra(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        ra[x] = i;
    }

    set<int> s;
    vector<int> nr(n, n), nl(n, -1);
    for(int i = 0; i < n; i++) {
        int idx = ra[i];
        if(s.upper_bound(idx) != s.end()) {
            auto it = s.upper_bound(idx);
            nr[idx] = *it;
        }
        s.insert(idx);
    }

    s.clear();

    for(int i = n - 1; i >= 0; i--) {
        int idx = ra[i];
        if(s.upper_bound(idx) != s.begin()) {
            auto it = --s.upper_bound(idx);
            nl[idx] = *it;
        }
        s.insert(idx);
    }

    vector<int> rr(n, n);
    for(int i = 0; i < n; i++) {
        if(nl[i] != -1) {
            rr[nl[i]] = min(rr[nl[i]], nr[i]);
        }
    }

    int mr = n;
    for(int i = n - 1; i >= 0; i--) {
        mr = min(mr, rr[i]);
        rr[i] = mr;
    }

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        // cout << "l : " << l << " r : " << r << '\n';
        if(rr[l] <= r) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    // cout << "nr : " << nr << '\n';
    // cout << "nl : " << nl << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}