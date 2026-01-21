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
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> one_p(n), zero_s(n);
    for(int i = 0; i < n; i++) {
        if(i) one_p[i] += one_p[i-1];
        one_p[i] += a[i] == 1;
    }
    for(int i = n - 1; i >= 0; i--) {
        if(i != n - 1) zero_s[i] += zero_s[i+1];
        zero_s[i] += a[i] == 0;
    }

    int res = INT_MAX;
    for(int i = 0; i < n; i++) {
        int one_before = (i ? one_p[i-1] : 0);
        int zero_after = zero_s[i];
        res = min(res, one_before + max(0, zero_after - one_before));
    }

    if(count(a.begin(), a.end(), 0) == n) res = 0;

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}