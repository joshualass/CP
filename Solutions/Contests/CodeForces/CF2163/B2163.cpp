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

void ttfang() {
    //yikes. this guy used the editorial for problem B!
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    string s; cin >> s;
    int lo_idx = -1, hi_idx = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1' && (i == 0 || i == n - 1 || a[i] == 1 || a[i] == n)) {
            cout << "-1\n";
            return;
        }
        if(a[i] == 1) lo_idx = i;
        if(a[i] == n) hi_idx = i;
    }

    cout << "5\n";
    cout << "1 " << lo_idx + 1 << '\n';
    cout << "1 " << hi_idx + 1 << '\n';
    cout << min(lo_idx, hi_idx) + 1 << " " << max(lo_idx, hi_idx) + 1 << '\n';
    cout << lo_idx + 1 << " " << n << '\n';
    cout << hi_idx + 1 << " " << n << '\n';

}

//this approach does not work because we don't know when each element should be removed. we should try to do it with observations ... 
void solve(int tc) {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    string s,t; cin >> t;

    // if(tc == 939) {
    //     cout << "n" << n;
    //     // cout << "a";
    //     // for(int i = 9; i < 29; i++) cout << a[i] << ',';
    //     cout << "s:" << t << '\n';
    //     return;
    // }

    auto _solve = [&](int bm) -> vector<array<int,2>> {
        vector<array<int,2>> ops;
        cout << "s start : " << s << endl;
        for(int i = 0; i < 5; i++) {
            int f = -1;
            for(int i = 0; i < n; i++) {
                if(s[i] == '1') {
                    f = i;
                    break;
                }
            }
            cout << "i : " << i << " f : " << f << endl;
            if(f <= 0) break;
            int lo_idx = f - 1;
            if((bm >> i) & 1) { //here, we find the lowest value prior. 
                for(int i = lo_idx; i >= 0; i--) {
                    if(a[i] < a[lo_idx]) lo_idx = i;
                }
            } else {
                for(int i = lo_idx; i >= 0; i--) {
                    if(a[i] > a[lo_idx]) lo_idx = i;
                }
            }
            int r = lo_idx;
            if((bm >> i) & 1) {
                int mx = -1;
                for(int i = lo_idx; i < n; i++) {
                    if(a[i] > mx) r = i;
                    if(s[i] == '1') mx = max(mx, a[i]);
                }
            } else {
                int mn = n + 1;
                for(int i = lo_idx; i < n; i++) {
                    if(a[i] < mn) r = i;
                    if(s[i] == '1') mn = min(mn, a[i]);
                }
            }
            ops.push_back({lo_idx, r});
            cout << "i : " << i << " bit : " << ((bm >> i) & 1) << endl;
            cout << "l : " << lo_idx << " r : " << r << endl;
            cout << "lval : " << a[lo_idx] << " rval : " << a[r] << endl;

            int lo = min(a[lo_idx], a[r]), hi = max(a[lo_idx], a[r]);
            for(int i = lo_idx; i <= r; i++) {
                if(lo < a[i] && a[i] < hi) s[i] = '0';
            }
            cout << "s after : " << s << endl;
        }
        if(count(s.begin(), s.end(), '1') == 0) return ops;
        return vector<array<int,2>>(6, {-1,-1});
    };

    //01110
    s = t;
    _solve((1 << 1) + (1 << 2) + (1 << 3));

    // for(int i = 0; i < 1 << 5; i++) {
    //     s = t;
    //     vector<array<int,2>> ops = _solve(i);
    //     if(ops.size() <= 5) {
    //         cout << ops.size() << '\n';
    //         for(auto op : ops) cout << op[0] + 1 << " " << op[1] + 1 << '\n';
    //         return;
    //     }
    // }
    cout << "-1\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int casi; cin >> casi;
    // while(casi-->0) solve();
    // int casi; cin >> casi;
    // for(int i = 1; i <= casi; i++) solve(i);
    int casi; cin >> casi;
    while(casi-->0) ttfang();

    return 0;
}