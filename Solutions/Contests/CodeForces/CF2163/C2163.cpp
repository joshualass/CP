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
    vector<vector<int>> a(2, vector<int>(n));
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<int> pmin(n), pmax(n), smin(n), smax(n);
    for(int i = 0; i < n; i++) {
        if(i) {
            pmin[i] = min(pmin[i - 1], a[0][i]);
            pmax[i] = max(pmax[i - 1], a[0][i]);
        } else {
            pmin[i] = a[0][i];
            pmax[i] = a[0][i];
        }
    }

    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1) {
            smin[i] = a[1][i];
            smax[i] = a[1][i];
        } else {
            smin[i] = min(smin[i + 1], a[1][i]);
            smax[i] = max(smax[i + 1], a[1][i]);
        }
    }

    int r = 0;
    ll res = 0;

    auto check = [&](int l, int r) -> bool {
        // cout << "check l : " << l << " r : " << r << endl;
        int l1 = -1, r1 = n - 1;
        while(l1 != r1) {
            int m = (l1 + r1 + 1) / 2;
            int lo = pmin[m], hi = pmax[m];
            if(lo < l || hi > r) { //no good
                r1 = m - 1;
            } else {
                l1 = m;
            }
        }
        // cout << "done check 0" << endl;
        int l2 = 0, r2 = n;
        while(l2 != r2) {
            int m = (l2 + r2) / 2;
            int lo = smin[m], hi = smax[m];
            if(lo < l || hi > r) {
                l2 = m + 1;
            } else {
                r2 = m;
            }
        }
        // cout << "done check!" << endl;
        // cout << "l1 : " << l1 << " r2 : " << r2 << endl;
        return l1 >= l2;
    };

    for(int l = 1; l <= n * 2; l++) {
        while(r <= n * 2 && check(l, r) == 0) r++;
        // cout << "l : " << l << " r : " << r << endl;
        res += n * 2 + 1 - r;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}