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
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = p[i-1] + a[i-1];
    }

    vector<int> alt(n);
    for(int i = 1; i < n; i++) {
        if(a[i] != a[i-1]) alt[i] = 1;
    }

    for(int i = 1; i < n; i++) {
        alt[i] += alt[i-1];
    }

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        int sum = p[r] - p[l];
        int oc = sum, zc = (r - l) - sum;
        if(oc % 3 || zc % 3) {
            cout << "-1\n";
            continue;
        }
        int ops = (r - l) / 3;
        if(r - l - 1 == alt[r - 1] - alt[l]) ops++;
        cout << ops << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}