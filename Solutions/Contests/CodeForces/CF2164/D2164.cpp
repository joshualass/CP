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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    string a, b; cin >> a >> b;
    vector<int> c(n);
    iota(c.begin(), c.end(), 0);

    int p = n - 1;
    int mx_dist = 0;
    int ok = 1;

    for(int i = n - 1; i >= 0; i--) {
        p = min(p, i);
        while(p >= 0 && a[p] != b[i]) {
            p--;
        }
        if(p < 0) {
            ok = 0;
            break;
        }
        c[p] = max(c[p], i);
        mx_dist = max(mx_dist, i - p);
    }

    if(!ok || mx_dist > k) {
        cout << "-1\n";
        return;
    }

    // cout << c << '\n';

    cout << mx_dist << '\n';
    for(int i = 0; i < mx_dist; i++) {
        for(int j = n - 1; j >= 0; j--) {
            if(j > 0 && c[j-1] >= j) {
                a[j] = a[j-1];
                c[j] = c[j-1];
            }
        }
        cout << a << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}