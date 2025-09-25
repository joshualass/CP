/*
this problem took time. 



*/


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
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<ll> v(n), a(n), b(n);
    vector<int> rb(n);
    for(ll &x : v) cin >> x;
    for(ll &x : a) {
        cin >> x;
        x--;
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        b[i] = x;
        rb[x] = i;
    }

    map<ll,ll> deltas;
    ll res = 0;

    auto add_seg = [&](ll add, int r) -> void {
        //we are adding add to indices before it
        add *= -1;
        if(add > 0) {
            deltas[r] = add;
            res -= add;
        } else {
            res -= add;
            while(add < 0 && deltas.upper_bound(r) != deltas.end()) {
                auto [lb, val] = *deltas.upper_bound(r);
                ll sub = min(val, -add);
                val -= sub;
                add += sub;
                if(val) deltas[lb] = val;
                else deltas.erase(lb);
                r = lb;
            }
        }
    };

    for(int i = 0; i < n; i++) {
        // cout << "i : " << i << " object : " << a[i] << '\n';
        add_seg(v[a[i]], rb[a[i]]);
        // cout << "i : " << i << " deltas : " << deltas << "\nres : " << res << '\n';
    }
    for(auto [k, v] : deltas) res += v;
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}